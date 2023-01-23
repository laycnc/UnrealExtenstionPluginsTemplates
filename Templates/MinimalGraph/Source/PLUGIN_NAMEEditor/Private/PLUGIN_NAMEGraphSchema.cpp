// Fill out your copyright notice in the Description page of Project Settings.

#include "PLUGIN_NAMEGraphSchema.h"
#include "AIGraphTypes.h"
#include "Settings/EditorStyleSettings.h"
#include "IPLUGIN_NAMEEditorModule.h"
#include "PLUGIN_NAMENode.h"
#include "PLUGIN_NAMEGraphNode.h"

#define LOCTEXT_NAMESPACE "PLUGIN_NAMEGraphSchema"

namespace
{
	// Maximum distance a drag can be off a node edge to require 'push off' from node
	const int32 NodeDistance = 60;

	TSharedPtr<FPLUGIN_NAMEGraphSchemaAction_NewNode> AddNewNodeAction(
	    FGraphActionListBuilderBase& ContextMenuBuilder,
	    const FText&                 Category,
	    const FText&                 MenuDesc,
	    const FText&                 Tooltip)
	{
		TSharedPtr<FPLUGIN_NAMEGraphSchemaAction_NewNode> NewAction =
		    TSharedPtr<FPLUGIN_NAMEGraphSchemaAction_NewNode>(
		        new FPLUGIN_NAMEGraphSchemaAction_NewNode(
		            Category, MenuDesc, Tooltip, 0));
		ContextMenuBuilder.AddAction(NewAction);

		return NewAction;
	}

} // namespace

//////////////////////////////////////////////////////////////////////////
// FPLUGIN_NAMEGraphSchemaAction_NewNode

//~ Begin FEdGraphSchemaAction Interface
UEdGraphNode* FPLUGIN_NAMEGraphSchemaAction_NewNode::PerformAction(
    class UEdGraph* ParentGraph,
    UEdGraphPin*    FromPin,
    const FVector2D Location,
    bool            bSelectNewNode)
{
#if 0
	return FEdGraphSchemaAction::PerformAction(
	    ParentGraph, FromPin, Location, bSelectNewNode);
#else
	UEdGraphNode* ResultNode = NULL;

	// If there is a template, we actually use it
	if ( NodeTemplate != NULL )
	{
		const FScopedTransaction Transaction(LOCTEXT("AddNode", "Add Node"));
		ParentGraph->Modify();
		if ( FromPin )
		{
			FromPin->Modify();
		}

		NodeTemplate->SetFlags(RF_Transactional);

		// set outer to be the graph so it doesn't go away
		NodeTemplate->Rename(NULL, ParentGraph, REN_NonTransactional);
		ParentGraph->AddNode(NodeTemplate, true);

		NodeTemplate->CreateNewGuid();
		NodeTemplate->PostPlacedNewNode();

		// For input pins, new node will generally overlap node being dragged off
		// Work out if we want to visually push away from connected node
		int32 XLocation = Location.X;
		if ( FromPin && FromPin->Direction == EGPD_Input )
		{
			UEdGraphNode* PinNode = FromPin->GetOwningNode();
			const float   XDelta  = FMath::Abs(PinNode->NodePosX - Location.X);

			if ( XDelta < NodeDistance )
			{
				// Set location to edge of current node minus the max move distance
				// to force node to push off from connect node enough to give selection handle
				XLocation = PinNode->NodePosX - NodeDistance;
			}
		}

		NodeTemplate->NodePosX = XLocation;
		NodeTemplate->NodePosY = Location.Y;
		NodeTemplate->SnapToGrid(GetDefault<UEditorStyleSettings>()->GridSnapSize);

		// setup pins after placing node in correct spot, since pin sorting will happen as soon as link connection change occurs
		NodeTemplate->AllocateDefaultPins();
		NodeTemplate->AutowireNewNode(FromPin);

		ResultNode = NodeTemplate;
	}
	return ResultNode;
#endif
}

UEdGraphNode* FPLUGIN_NAMEGraphSchemaAction_NewNode::PerformAction(
    class UEdGraph*       ParentGraph,
    TArray<UEdGraphPin*>& FromPins,
    const FVector2D       Location,
    bool                  bSelectNewNode)
{
	UEdGraphNode* ResultNode = nullptr;
	if ( FromPins.Num() > 0 )
	{
		ResultNode = PerformAction(ParentGraph, FromPins[0], Location);

		// Try autowiring the rest of the pins
		for ( int32 Index = 1; Index < FromPins.Num(); ++Index )
		{
			ResultNode->AutowireNewNode(FromPins[Index]);
		}
	}
	else
	{
		ResultNode = PerformAction(ParentGraph, nullptr, Location, bSelectNewNode);
	}
	return ResultNode;
}

void FPLUGIN_NAMEGraphSchemaAction_NewNode::AddReferencedObjects(
    FReferenceCollector& Collector)
{
	FEdGraphSchemaAction::AddReferencedObjects(Collector);

	// These don't get saved to disk, but we want to make sure the objects don't get GC'd while the action array is around
	Collector.AddReferencedObject(NodeTemplate);
}

//~ End FEdGraphSchemaAction Interface

//////////////////////////////////////////////////////////////////////////
// UPLUGIN_NAMEGraphSchema

UPLUGIN_NAMEGraphSchema::UPLUGIN_NAMEGraphSchema(
    const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UPLUGIN_NAMEGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	// todo
	Super::CreateDefaultNodesForGraph(Graph);
}

void UPLUGIN_NAMEGraphSchema::GetGraphContextActions(
    FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	IPLUGIN_NAMEEditorModule& EditorModule = IPLUGIN_NAMEEditorModule::Get();
	FGraphNodeClassHelper*     ClassCache   = EditorModule.GetClassCache().Get();

	FCategorizedGraphActionListBuilder TasksBuilder(TEXT("Node"));

	TArray<FGraphNodeClassData> NodeClasses;
	ClassCache->GatherClasses(UPLUGIN_NAMENode::StaticClass(), NodeClasses);

	for ( const FGraphNodeClassData& NodeClass : NodeClasses )
	{
		const FText NodeTypeName = FText::FromString(
		    FName::NameToDisplayString(NodeClass.ToString(), false));

		TSharedPtr<FPLUGIN_NAMEGraphSchemaAction_NewNode> AddOpAction =
		    AddNewNodeAction(TasksBuilder,
		                     NodeClass.GetCategory(),
		                     NodeTypeName,
		                     FText::GetEmpty());

		UClass* GraphNodeClass = UPLUGIN_NAMEGraphNode::StaticClass();

		UPLUGIN_NAMEGraphNode* OpNode = NewObject<UPLUGIN_NAMEGraphNode>(
		    ContextMenuBuilder.OwnerOfTemporaries, GraphNodeClass);
		OpNode->ClassData         = NodeClass;
		AddOpAction->NodeTemplate = OpNode;
	}

	ContextMenuBuilder.Append(TasksBuilder);
}

void UPLUGIN_NAMEGraphSchema::GetContextMenuActions(
    class UToolMenu*                    Menu,
    class UGraphNodeContextMenuContext* Context) const
{
	// todo
	Super::GetContextMenuActions(Menu, Context);
}

const FPinConnectionResponse UPLUGIN_NAMEGraphSchema::CanCreateConnection(
    const UEdGraphPin* A,
    const UEdGraphPin* B) const
{
	// todo
	return Super::CanCreateConnection(A, B);
}

const FPinConnectionResponse UPLUGIN_NAMEGraphSchema::CanMergeNodes(
    const UEdGraphNode* A,
    const UEdGraphNode* B) const
{
	// todo
	return Super::CanMergeNodes(A, B);
}

FLinearColor UPLUGIN_NAMEGraphSchema::GetPinTypeColor(
    const FEdGraphPinType& PinType) const
{
	return FColor::White;
}

int32 UPLUGIN_NAMEGraphSchema::GetNodeSelectionCount(const UEdGraph* Graph) const
{
	// todo
	return Super::GetNodeSelectionCount(Graph);
}

bool UPLUGIN_NAMEGraphSchema::IsCacheVisualizationOutOfDate(
    int32 InVisualizationCacheID) const
{
	// todo
	return Super::IsCacheVisualizationOutOfDate(InVisualizationCacheID);
}

int32 UPLUGIN_NAMEGraphSchema::GetCurrentVisualizationCacheID() const
{
	// todo
	return Super::GetCurrentVisualizationCacheID();
}

void UPLUGIN_NAMEGraphSchema::ForceVisualizationCacheClear() const
{
	// todo
	Super::GetCreateCommentAction();
}

TSharedPtr<FEdGraphSchemaAction> UPLUGIN_NAMEGraphSchema::GetCreateCommentAction() const
{
	// todo
	return Super::GetCreateCommentAction();
}

#undef LOCTEXT_NAMESPACE
