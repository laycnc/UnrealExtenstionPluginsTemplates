// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "PLUGIN_NAMEGraphSchema.generated.h"

class UPLUGIN_NAMEGraphNode;

/** Action to add a node to the graph */
USTRUCT()
struct FPLUGIN_NAMEGraphSchemaAction_NewNode : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();

	/** Template of node we want to create */
	UPROPERTY()
	TObjectPtr<UPLUGIN_NAMEGraphNode> NodeTemplate = nullptr;

	FPLUGIN_NAMEGraphSchemaAction_NewNode() = default;

	FPLUGIN_NAMEGraphSchemaAction_NewNode(FText       InNodeCategory,
	                                   FText       InMenuDesc,
	                                   FText       InToolTip,
	                                   const int32 InGrouping)
	    : FEdGraphSchemaAction(MoveTemp(InNodeCategory),
	                           MoveTemp(InMenuDesc),
	                           MoveTemp(InToolTip),
	                           InGrouping)
	{
	}

	//~ Begin FEdGraphSchemaAction Interface
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph,
	                                    UEdGraphPin*    FromPin,
	                                    const FVector2D Location,
	                                    bool bSelectNewNode = true) override;
	virtual UEdGraphNode* PerformAction(class UEdGraph*       ParentGraph,
	                                    TArray<UEdGraphPin*>& FromPins,
	                                    const FVector2D       Location,
	                                    bool bSelectNewNode = true) override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	//~ End FEdGraphSchemaAction Interface

	template<typename NodeType>
	static NodeType* SpawnNodeFromTemplate(class UEdGraph* ParentGraph,
	                                       NodeType*       InTemplateNode,
	                                       const FVector2D Location)
	{
		FPLUGIN_NAMEGraphSchemaAction_NewNode Action;
		Action.NodeTemplate = InTemplateNode;

		return Cast<NodeType>(Action.PerformAction(ParentGraph, nullptr, Location));
	}
};

/**
 * 
 */
UCLASS()
class UPLUGIN_NAMEGraphSchema : public UEdGraphSchema
{
	GENERATED_UCLASS_BODY()
public:
	//~ Begin EdGraphSchema Interface
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;
	virtual void GetGraphContextActions(
	    FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	virtual void GetContextMenuActions(
	    class UToolMenu*                    Menu,
	    class UGraphNodeContextMenuContext* Context) const override;
	virtual const FPinConnectionResponse CanCreateConnection(
	    const UEdGraphPin* A,
	    const UEdGraphPin* B) const override;
	virtual const FPinConnectionResponse CanMergeNodes(
	    const UEdGraphNode* A,
	    const UEdGraphNode* B) const override;
	virtual FLinearColor GetPinTypeColor(
	    const FEdGraphPinType& PinType) const override;
	virtual int32 GetNodeSelectionCount(const UEdGraph* Graph) const override;
	virtual bool  IsCacheVisualizationOutOfDate(
	     int32 InVisualizationCacheID) const override;
	virtual int32 GetCurrentVisualizationCacheID() const override;
	virtual void  ForceVisualizationCacheClear() const override;
	virtual TSharedPtr<FEdGraphSchemaAction> GetCreateCommentAction() const override;
	//~ End EdGraphSchema Interface
};
