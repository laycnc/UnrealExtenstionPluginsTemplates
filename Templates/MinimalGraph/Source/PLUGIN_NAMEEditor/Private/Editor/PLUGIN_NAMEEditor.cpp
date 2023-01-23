// Copyright Epic Games, Inc. All Rights Reserved.

#include "PLUGIN_NAMEEditor.h"
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

#define LOCTEXT_NAMESPACE "FPLUGIN_NAMEEditor"

//////////////////////////////////////////////////////////////////////////

const FName PLUGIN_NAMEEditorAppName = FName(TEXT("PLUGIN_NAMEEditorApp"));

//////////////////////////////////////////////////////////////////////////
// PLUGIN_NAMEEditor

void FPLUGIN_NAMEEditor::InitPLUGIN_NAMEEditor(
    const EToolkitMode::Type        Mode,
    const TSharedPtr<IToolkitHost>& InitToolkitHost,
    UPLUGIN_NAME*                  InitAsset)
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
			            CreateSP(this, &FPLUGIN_NAMEEditor::CreateGraphEditorWidget)));

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

FPLUGIN_NAMEEditor::FPLUGIN_NAMEEditor() {}

FPLUGIN_NAMEEditor ::~FPLUGIN_NAMEEditor() {}

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
	return LOCTEXT("FPLUGIN_NAMEEditorAppLabel", "Dev Menu Editor");
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

void FPLUGIN_NAMEEditor::BindCommands()
{
	FGraphEditorCommands::Register();
	FPLUGIN_NAMEEditorCommands::Register();

	if ( GraphEditorCommands.IsValid() )
	{
		return;
	}

	GraphEditorCommands = MakeShareable(new FUICommandList);
}

FGraphAppearanceInfo FPLUGIN_NAMEEditor::GetGraphAppearance() const
{
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = LOCTEXT("AppearanceCornerText", "PLUGIN_NAME");

	return AppearanceInfo;
}

TSharedRef<SGraphEditor> FPLUGIN_NAMEEditor::CreateGraphEditorWidget(UEdGraph* InGraph)
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
	UPLUGIN_NAMEGraph* MyGraph   = Cast<UPLUGIN_NAMEGraph>(AssetEdited->PLUGIN_NAMEGraph);
	const bool      bNewGraph = MyGraph == NULL;
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

#undef LOCTEXT_NAMESPACE
