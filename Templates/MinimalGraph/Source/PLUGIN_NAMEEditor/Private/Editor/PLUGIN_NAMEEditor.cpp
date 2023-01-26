// Copyright Epic Games, Inc. All Rights Reserved.

#include "PLUGIN_NAMEEditor.h"
#include "Misc/CoreMisc.h"
#include "HAL/PlatformApplicationMisc.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"
#include "Framework/Commands/GenericCommands.h"
#include "GraphEditorActions.h"
#include "PLUGIN_NAME.h"
#include "PLUGIN_NAMEEditorCommands.h"
#include "Editor/PLUGIN_NAMEEditorModes.h"
#include "Editor/PLUGIN_NAMEEditorTabs.h"
#include "Editor/PLUGIN_NAMEEditorTabFactories.h"
#include "PLUGIN_NAMEGraph.h"
#include "PLUGIN_NAMEGraphSchema.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "EdGraphUtilities.h"

#define LOCTEXT_NAMESPACE "FPLUGIN_NAMEEditor"

//////////////////////////////////////////////////////////////////////////

const FName PLUGIN_NAMEEditorAppName = FName(TEXT("PLUGIN_NAMEEditorApp"));

//////////////////////////////////////////////////////////////////////////
// PLUGIN_NAMEEditor

void FPLUGIN_NAMEEditor::InitPLUGIN_NAMEEditor(
    const EToolkitMode::Type        Mode,
    const TSharedPtr<IToolkitHost>& InitToolkitHost,
    UPLUGIN_NAME*                   InitAsset)
{
	AssetEdited = InitAsset;

	BindCommands();

#if 1
	TSharedPtr<FPLUGIN_NAMEEditor> ThisPtr(SharedThis(this));
	if ( !DocumentManager.IsValid() )
	{
		DocumentManager = MakeShareable(new FDocumentTracker);
		DocumentManager->Initialize(ThisPtr);

		// Register the document factories
		{
			TSharedRef<FDocumentTabFactory> GraphEditorFactory =
			    MakeShareable(new FPLUGIN_NAMEGraphEditorSummoner(
			        ThisPtr,
			        FPLUGIN_NAMEGraphEditorSummoner::FOnCreateGraphEditorWidget::
			            CreateSP(this,
			                     &FPLUGIN_NAMEEditor::CreateGraphEditorWidget)));

			// Also store off a reference to the grapheditor factory so we can find all the tabs spawned by it later.
			GraphEditorTabFactoryPtr = GraphEditorFactory;
			DocumentManager->RegisterDocumentFactory(GraphEditorFactory);
		}
	}
#endif

	// Initialize the asset editor and spawn nothing (dummy layout)
	InitAssetEditor(Mode,
	                InitToolkitHost,
	                PLUGIN_NAMEEditorAppName,
	                FTabManager::FLayout::NullLayout,
	                /*bCreateDefaultStandaloneMenu=*/true,
	                /*bCreateDefaultToolbar=*/true,
	                InitAsset);

	//
	AddApplicationMode(FPLUGIN_NAMEEditorTabs::PLUGIN_NAMEMode,
	                   MakeShareable(new FPLUGIN_NAMEEditorModes(SharedThis(this))));

	SetCurrentMode(FPLUGIN_NAMEEditorTabs::PLUGIN_NAMEMode);
}

FPLUGIN_NAMEEditor::FPLUGIN_NAMEEditor()
{
	UEditorEngine* Editor = (UEditorEngine*)GEngine;
	if ( Editor != NULL )
	{
		Editor->RegisterForUndo(this);
	}
}

FPLUGIN_NAMEEditor ::~FPLUGIN_NAMEEditor()
{
	UEditorEngine* Editor = (UEditorEngine*)GEngine;
	if ( Editor )
	{
		Editor->UnregisterForUndo(this);
	}
}

// IToolkit interface
void FPLUGIN_NAMEEditor::RegisterTabSpawners(
    const TSharedRef<FTabManager>& InTabManager)
{
	DocumentManager->SetTabManager(InTabManager);

	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);
}
void FPLUGIN_NAMEEditor::UnregisterTabSpawners(
    const TSharedRef<FTabManager>& InTabManager)
{
	FWorkflowCentricApplication::UnregisterTabSpawners(InTabManager);
}
// End of IToolkit interface

// FAssetEditorToolkit
FName FPLUGIN_NAMEEditor::GetToolkitFName() const
{
	return FName("PLUGIN_NAMEEditor");
}

FText FPLUGIN_NAMEEditor::GetBaseToolkitName() const
{
	return LOCTEXT("FPLUGIN_NAMEEditorAppLabel", "PLUGIN_NAME Editor");
}

FText FPLUGIN_NAMEEditor::GetToolkitName() const
{
	return FText::FromString(AssetEdited->GetName());
}

FText FPLUGIN_NAMEEditor::GetToolkitToolTipText() const
{
	return FAssetEditorToolkit::GetToolTipTextForObject(AssetEdited);
}

FLinearColor FPLUGIN_NAMEEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}

FString FPLUGIN_NAMEEditor::GetWorldCentricTabPrefix() const
{
	return TEXT("PLUGIN_NAMEEditor");
}

// End of FAssetEditorToolkit

//~ Begin FEditorUndoClient Interface

void FPLUGIN_NAMEEditor::PostUndo(bool bSuccess)
{
	if ( bSuccess )
	{
		// Clear selection, to avoid holding refs to nodes that go away
		if ( TSharedPtr<SGraphEditor> CurrentGraphEditor = UpdateGraphEdPtr.Pin() )
		{
			CurrentGraphEditor->ClearSelectionSet();
			CurrentGraphEditor->NotifyGraphChanged();
		}
		FSlateApplication::Get().DismissAllMenus();
	}
}

void FPLUGIN_NAMEEditor::PostRedo(bool bSuccess)
{
	if ( bSuccess )
	{
		// Clear selection, to avoid holding refs to nodes that go away
		if ( TSharedPtr<SGraphEditor> CurrentGraphEditor = UpdateGraphEdPtr.Pin() )
		{
			CurrentGraphEditor->ClearSelectionSet();
			CurrentGraphEditor->NotifyGraphChanged();
		}
		FSlateApplication::Get().DismissAllMenus();
	}
}

// End of FEditorUndoClient

// FGCObject interface
void FPLUGIN_NAMEEditor::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(AssetEdited);
}

FString FPLUGIN_NAMEEditor::GetReferencerName() const
{
	return TEXT("FPLUGIN_NAMEEditor");
}

// End of FGCObject interface

FGraphAppearanceInfo FPLUGIN_NAMEEditor::GetGraphAppearance() const
{
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = LOCTEXT("AppearanceCornerText", "PLUGIN_NAME");

	return AppearanceInfo;
}

TSharedRef<SGraphEditor> FPLUGIN_NAMEEditor::CreateGraphEditorWidget(
    UEdGraph* InGraph)
{
	check(InGraph != nullptr);

	SGraphEditor::FGraphEditorEvents InEvents;
#if 0
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(
	    this, &FPLUGIN_NAMEEditor::OnSelectedNodesChanged);
	InEvents.OnNodeDoubleClicked =
	    FSingleNodeEvent::CreateSP(this, &FPLUGIN_NAMEEditor::OnNodeDoubleClicked);
	InEvents.OnTextCommitted =
	    FOnNodeTextCommitted::CreateSP(this, &FPLUGIN_NAMEEditor::OnNodeTitleCommitted);
#endif

	// clang-format off

	// Make title bar
	TSharedRef<SWidget> TitleBarWidget =
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush(TEXT("Graph.TitleBackground")))
		.HAlign(HAlign_Fill)
		[
			SNew(SHorizontalBox) 
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			.FillWidth(1.f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("PLUGIN_NAMEGraphLabel", "PLUGIN_NAME"))
				.TextStyle(FAppStyle::Get(), TEXT("GraphBreadcrumbButtonText"))
			]
		];



	const bool bGraphIsEditable = InGraph->bEditable;
	return SNew(SGraphEditor)
		.AdditionalCommands(GraphEditorCommands)
		.IsEditable(bGraphIsEditable)
		.Appearance(this, &FPLUGIN_NAMEEditor::GetGraphAppearance)
		.TitleBar(TitleBarWidget)
		.GraphToEdit(InGraph)
		.GraphEvents(InEvents);

	// clang-format on
}

void FPLUGIN_NAMEEditor::RestoreGraphAsset()
{
	// Update PLUGIN_NAME asset data based on saved graph to have correct data in editor
	UPLUGIN_NAMEGraph* MyGraph =
	    Cast<UPLUGIN_NAMEGraph>(AssetEdited->PLUGIN_NAMEGraph);
	const bool bNewGraph = MyGraph == nullptr;
	if ( MyGraph == NULL )
	{
		AssetEdited->PLUGIN_NAMEGraph = FBlueprintEditorUtils::CreateNewGraph(
		    AssetEdited,
		    TEXT("PLUGIN_NAME"),
		    UPLUGIN_NAMEGraph::StaticClass(),
		    UPLUGIN_NAMEGraphSchema::StaticClass());
		MyGraph = Cast<UPLUGIN_NAMEGraph>(AssetEdited->PLUGIN_NAMEGraph);

		// Initialize the PLUGIN_NAME graph
		const UEdGraphSchema* Schema = MyGraph->GetSchema();
		Schema->CreateDefaultNodesForGraph(*MyGraph);

		AssetEdited->Modify();

		MyGraph->OnCreated();
	}
	else
	{
		MyGraph->OnLoaded();
	}

	MyGraph->Initialize();

	TSharedRef<FTabPayload_UObject> Payload     = FTabPayload_UObject::Make(MyGraph);
	TSharedPtr<SDockTab>            DocumentTab = DocumentManager->OpenDocument(
        Payload,
        bNewGraph ? FDocumentTracker::OpenNewDocument
	                         : FDocumentTracker::RestorePreviousDocument);
}

void FPLUGIN_NAMEEditor::OnGraphEditorFocused(
    const TSharedRef<SGraphEditor>& InGraphEditor)
{
	UpdateGraphEdPtr = InGraphEditor;

	FGraphPanelSelectionSet CurrentSelection;
	CurrentSelection = InGraphEditor->GetSelectedNodes();
	//OnSelectedNodesChanged(CurrentSelection);
}

FGraphPanelSelectionSet FPLUGIN_NAMEEditor::GetSelectedNodes() const
{
	FGraphPanelSelectionSet CurrentSelection;
	if ( TSharedPtr<SGraphEditor> FocusedGraphEd = UpdateGraphEdPtr.Pin() )
	{
		CurrentSelection = FocusedGraphEd->GetSelectedNodes();
	}

	return CurrentSelection;
}

void FPLUGIN_NAMEEditor::OnSelectedNodesChanged(
    const TSet<class UObject*>& NewSelection)
{
	// todo
}

void FPLUGIN_NAMEEditor::BindCommands()
{
	FGraphEditorCommands::Register();
	FPLUGIN_NAMEEditorCommands::Register();

	if ( GraphEditorCommands.IsValid() )
	{
		return;
	}

	GraphEditorCommands = MakeShareable(new FUICommandList);

	GraphEditorCommands->MapAction(
	    FGenericCommands::Get().SelectAll,
	    FExecuteAction::CreateRaw(this, &FPLUGIN_NAMEEditor::SelectAllNodes),
	    FCanExecuteAction::CreateRaw(this, &FPLUGIN_NAMEEditor::CanSelectAllNodes));

	GraphEditorCommands->MapAction(
	    FGenericCommands::Get().Delete,
	    FExecuteAction::CreateRaw(this, &FPLUGIN_NAMEEditor::DeleteSelectedNodes),
	    FCanExecuteAction::CreateRaw(this, &FPLUGIN_NAMEEditor::CanDeleteNodes));

	GraphEditorCommands->MapAction(
	    FGenericCommands::Get().Copy,
	    FExecuteAction::CreateRaw(this, &FPLUGIN_NAMEEditor::CopySelectedNodes),
	    FCanExecuteAction::CreateRaw(this, &FPLUGIN_NAMEEditor::CanCopyNodes));

	GraphEditorCommands->MapAction(
	    FGenericCommands::Get().Cut,
	    FExecuteAction::CreateRaw(this, &FPLUGIN_NAMEEditor::CutSelectedNodes),
	    FCanExecuteAction::CreateRaw(this, &FPLUGIN_NAMEEditor::CanCutNodes));

	GraphEditorCommands->MapAction(
	    FGenericCommands::Get().Paste,
	    FExecuteAction::CreateRaw(this, &FPLUGIN_NAMEEditor::PasteNodes),
	    FCanExecuteAction::CreateRaw(this, &FPLUGIN_NAMEEditor::CanPasteNodes));

	GraphEditorCommands->MapAction(
	    FGenericCommands::Get().Duplicate,
	    FExecuteAction::CreateRaw(this, &FPLUGIN_NAMEEditor::DuplicateNodes),
	    FCanExecuteAction::CreateRaw(this, &FPLUGIN_NAMEEditor::CanDuplicateNodes));

	GraphEditorCommands->MapAction(
	    FGraphEditorCommands::Get().CreateComment,
	    FExecuteAction::CreateRaw(this, &FPLUGIN_NAMEEditor::OnCreateComment),
	    FCanExecuteAction::CreateRaw(this, &FPLUGIN_NAMEEditor::CanCreateComment));
}

// Delegates for graph editor commands
void FPLUGIN_NAMEEditor::SelectAllNodes()
{
	if ( TSharedPtr<SGraphEditor> CurrentGraphEditor = UpdateGraphEdPtr.Pin() )
	{
		CurrentGraphEditor->SelectAllNodes();
	}
}

bool FPLUGIN_NAMEEditor::CanSelectAllNodes() const
{
	return true;
}

void FPLUGIN_NAMEEditor::DeleteSelectedNodes()
{
	TSharedPtr<SGraphEditor> CurrentGraphEditor = UpdateGraphEdPtr.Pin();
	if ( !CurrentGraphEditor.IsValid() )
	{
		return;
	}

	const FScopedTransaction Transaction(
	    FGenericCommands::Get().Delete->GetDescription());
	CurrentGraphEditor->GetCurrentGraph()->Modify();

	const FGraphPanelSelectionSet SelectedNodes =
	    CurrentGraphEditor->GetSelectedNodes();
	CurrentGraphEditor->ClearSelectionSet();

	for ( UObject* SelectNode : SelectedNodes )
	{
		if ( UEdGraphNode* Node = Cast<UEdGraphNode>(SelectNode) )
		{
			if ( Node->CanUserDeleteNode() )
			{
				Node->Modify();
				Node->DestroyNode();
			}
		}
	}
}

bool FPLUGIN_NAMEEditor::CanDeleteNodes() const
{
	// If any of the nodes can be deleted then we should allow deleting
	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	for ( const UObject* SelectNode : SelectedNodes )
	{
		const UEdGraphNode* Node = Cast<UEdGraphNode>(SelectNode);
		if ( Node && Node->CanUserDeleteNode() )
		{
			return true;
		}
	}
	return false;
}

void FPLUGIN_NAMEEditor::DeleteSelectedDuplicatableNodes()
{
	TSharedPtr<SGraphEditor> CurrentGraphEditor = UpdateGraphEdPtr.Pin();
	if ( !CurrentGraphEditor.IsValid() )
	{
		return;
	}

	const FGraphPanelSelectionSet OldSelectedNodes =
	    CurrentGraphEditor->GetSelectedNodes();
	CurrentGraphEditor->ClearSelectionSet();

	for ( UObject* SelectNode : OldSelectedNodes )
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(SelectNode);
		if ( Node && Node->CanDuplicateNode() )
		{
			CurrentGraphEditor->SetNodeSelection(Node, true);
		}
	}

	// Delete the duplicatable nodes
	DeleteSelectedNodes();

	CurrentGraphEditor->ClearSelectionSet();

	for ( UObject* SelectNode : OldSelectedNodes )
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(SelectNode);
		{
			CurrentGraphEditor->SetNodeSelection(Node, true);
		}
	}
}

void FPLUGIN_NAMEEditor::CutSelectedNodes()
{
	CopySelectedNodes();
	DeleteSelectedDuplicatableNodes();
}

bool FPLUGIN_NAMEEditor::CanCutNodes() const
{
	return CanCopyNodes() && CanDeleteNodes();
}

void FPLUGIN_NAMEEditor::CopySelectedNodes()
{
	// Export the selected nodes and place the text on the clipboard
	FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();

	FString ExportedText;

	for ( FGraphPanelSelectionSet::TIterator SelectedIter(SelectedNodes);
	      SelectedIter;
	      ++SelectedIter )
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		if ( Node == nullptr )
		{
			SelectedIter.RemoveCurrent();
			continue;
		}

		Node->PrepareForCopying();
	}

	FEdGraphUtilities::ExportNodesToText(SelectedNodes, ExportedText);
	FPlatformApplicationMisc::ClipboardCopy(*ExportedText);

	for ( UObject* SelectedNode : SelectedNodes )
	{
		UPLUGIN_NAMEGraphNode* Node = Cast<UPLUGIN_NAMEGraphNode>(SelectedNode);
		if ( Node )
		{
			// todo
			//Node->PostCopyNode();
		}
	}
}

bool FPLUGIN_NAMEEditor::CanCopyNodes() const
{
	// If any of the nodes can be duplicated then we should allow copying
	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	for ( const UObject* SelectNode : SelectedNodes )
	{
		const UEdGraphNode* Node = Cast<UEdGraphNode>(SelectNode);
		if ( Node && Node->CanDuplicateNode() )
		{
			return true;
		}
	}

	return false;
}

void FPLUGIN_NAMEEditor::PasteNodes()
{
	if ( TSharedPtr<SGraphEditor> CurrentGraphEditor = UpdateGraphEdPtr.Pin() )
	{
		PasteNodesHere(CurrentGraphEditor->GetPasteLocation());
	}
}

void FPLUGIN_NAMEEditor::PasteNodesHere(const FVector2D& Location)
{
	TSharedPtr<SGraphEditor> CurrentGraphEditor = UpdateGraphEdPtr.Pin();
	if ( !CurrentGraphEditor.IsValid() )
	{
		return;
	}

	// Undo/Redo support
	const FScopedTransaction Transaction(
	    FGenericCommands::Get().Paste->GetDescription());
	UEdGraph*          EdGraph   = CurrentGraphEditor->GetCurrentGraph();
	UPLUGIN_NAMEGraph* PiyoGraph = Cast<UPLUGIN_NAMEGraph>(EdGraph);

	EdGraph->Modify();
	if ( PiyoGraph )
	{
		// todo
		//PiyoGraph->LockUpdates();
	}

	UPLUGIN_NAMEGraphNode* SelectedParent            = nullptr;
	bool                   bHasMultipleNodesSelected = false;

	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	for ( UObject* SelectNode : SelectedNodes )
	{
		UPLUGIN_NAMEGraphNode* Node = Cast<UPLUGIN_NAMEGraphNode>(SelectNode);
		if ( Node )
		{
			if ( SelectedParent == nullptr )
			{
				SelectedParent = Node;
			}
			else
			{
				bHasMultipleNodesSelected = true;
				break;
			}
		}
	}

	// Clear the selection set (newly pasted stuff will be selected)
	CurrentGraphEditor->ClearSelectionSet();

	// Grab the text to paste from the clipboard.
	FString TextToImport;
	FPlatformApplicationMisc::ClipboardPaste(TextToImport);

	// Import the nodes
	TSet<UEdGraphNode*> PastedNodes;
	FEdGraphUtilities::ImportNodesFromText(
	    EdGraph, TextToImport, /*out*/ PastedNodes);

	//Average position of nodes so we can move them while still maintaining relative distances to each other
	FVector2D AvgNodePosition(0.0f, 0.0f);

	// Number of nodes used to calculate AvgNodePosition
	int32 AvgCount = 0;

	for ( UEdGraphNode* EdNode : PastedNodes )
	{
		if ( EdNode )
		{
			AvgNodePosition.X += EdNode->NodePosX;
			AvgNodePosition.Y += EdNode->NodePosY;
			++AvgCount;
		}
	}

	if ( AvgCount > 0 )
	{
		float InvNumNodes = 1.0f / float(AvgCount);
		AvgNodePosition.X *= InvNumNodes;
		AvgNodePosition.Y *= InvNumNodes;
	}

	bool bPastedParentNode = false;

	TMap<FGuid /*New*/, FGuid /*Old*/> NewToOldNodeMapping;

	TMap<int32, UPLUGIN_NAMEGraphNode*> ParentMap;
	for ( UEdGraphNode* PasteNode : PastedNodes )
	{
		if ( PasteNode )
		{
			bPastedParentNode = true;

			// Select the newly pasted stuff
			CurrentGraphEditor->SetNodeSelection(PasteNode, true);

			PasteNode->NodePosX =
			    (PasteNode->NodePosX - AvgNodePosition.X) + Location.X;
			PasteNode->NodePosY =
			    (PasteNode->NodePosY - AvgNodePosition.Y) + Location.Y;

			PasteNode->SnapToGrid(16);

			const FGuid OldGuid = PasteNode->NodeGuid;

			// Give new node a different Guid from the old one
			PasteNode->CreateNewGuid();

			const FGuid NewGuid = PasteNode->NodeGuid;

			NewToOldNodeMapping.Add(NewGuid, OldGuid);
		}
	}

	if ( PiyoGraph )
	{
		// todo
		//PiyoGraph->UpdateClassData();
		//PiyoGraph->OnNodesPasted(TextToImport);
		//PiyoGraph->UnlockUpdates();
	}

	// Update UI
	CurrentGraphEditor->NotifyGraphChanged();

	UObject* GraphOwner = EdGraph->GetOuter();
	if ( GraphOwner )
	{
		GraphOwner->PostEditChange();
		GraphOwner->MarkPackageDirty();
	}
}

bool FPLUGIN_NAMEEditor::CanPasteNodes() const
{
	TSharedPtr<SGraphEditor> CurrentGraphEditor = UpdateGraphEdPtr.Pin();
	if ( !CurrentGraphEditor.IsValid() )
	{
		return false;
	}

	FString ClipboardContent;
	FPlatformApplicationMisc::ClipboardPaste(ClipboardContent);

	return FEdGraphUtilities::CanImportNodesFromText(
	    CurrentGraphEditor->GetCurrentGraph(), ClipboardContent);
}

void FPLUGIN_NAMEEditor::DuplicateNodes()
{
	CopySelectedNodes();
	PasteNodes();
}

bool FPLUGIN_NAMEEditor::CanDuplicateNodes() const
{
	return CanCopyNodes();
}

bool FPLUGIN_NAMEEditor::CanCreateComment() const
{
	TSharedPtr<SGraphEditor> CurrentGraphEditor = UpdateGraphEdPtr.Pin();
	return CurrentGraphEditor.IsValid()
	           ? (CurrentGraphEditor->GetNumberOfSelectedNodes() != 0)
	           : false;
}

void FPLUGIN_NAMEEditor::OnCreateComment()
{
	TSharedPtr<SGraphEditor> CurrentGraphEditor = UpdateGraphEdPtr.Pin();
	if ( UEdGraph* EdGraph = CurrentGraphEditor.IsValid()
	                             ? CurrentGraphEditor->GetCurrentGraph()
	                             : nullptr )
	{
		TSharedPtr<FEdGraphSchemaAction> Action =
		    EdGraph->GetSchema()->GetCreateCommentAction();
		if ( Action.IsValid() )
		{
			Action->PerformAction(EdGraph, nullptr, FVector2D());
		}
	}
}

#undef LOCTEXT_NAMESPACE
