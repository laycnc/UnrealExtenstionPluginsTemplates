// Fill out your copyright notice in the Description page of Project Settings.
#include "PLUGIN_NAMEGraphNode.h"

#define LOCTEXT_NAMESPACE "PLUGIN_NAMEGraphNode"

UPLUGIN_NAMEGraphNode::UPLUGIN_NAMEGraphNode(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

//~ Begin EdGraphSchema Interface

void UPLUGIN_NAMEGraphNode::PostPlacedNewNode()
{
	// NodeInstance can be already spawned by paste operation, don't override it

	UClass* NodeClass = ClassData.GetClass(true);
	if ( NodeClass && (NodeInstance == nullptr) )
	{
		UEdGraph* MyGraph    = GetGraph();
		UObject*  GraphOwner = MyGraph ? MyGraph->GetOuter() : nullptr;
		if ( GraphOwner )
		{
			NodeInstance = NewObject<UObject>(GraphOwner, NodeClass);
			NodeInstance->SetFlags(RF_Transactional);
			InitializeInstance();
		}
	}
}

void UPLUGIN_NAMEGraphNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, TEXT("SingleNode"), FName(), TEXT(""));
}

FText UPLUGIN_NAMEGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	FText TooltipDesc;

	if ( !NodeInstance )
	{
		FString StoredClassName = ClassData.GetClassName();
		StoredClassName.RemoveFromEnd(TEXT("_C"));

		TooltipDesc = FText::Format(
		    LOCTEXT("NodeClassError", "Class {0} not found, make sure it's saved!"),
		    FText::FromString(StoredClassName));
	}
	else
	{
		//if ( ErrorMessage.Len() > 0 )
		//{
		//	TooltipDesc = FText::FromString(ErrorMessage);
		//}
		//else
		{
			if ( NodeInstance->GetClass()->HasAnyClassFlags(
			         CLASS_CompiledFromBlueprint) )
			{
				FAssetData AssetData(NodeInstance->GetClass()->ClassGeneratedBy);
				FString    Description = AssetData.GetTagValueRef<FString>(
                    GET_MEMBER_NAME_CHECKED(UBlueprint, BlueprintDescription));
				if ( !Description.IsEmpty() )
				{
					Description.ReplaceInline(TEXT("\\n"), TEXT("\n"));
					TooltipDesc = FText::FromString(MoveTemp(Description));
				}
			}
			else
			{
				TooltipDesc = NodeInstance->GetClass()->GetToolTipText();
			}
		}
	}

	return TooltipDesc;
}

FText UPLUGIN_NAMEGraphNode::GetTooltipText() const
{

	if ( IsValid(NodeInstance) )
	{
		FText TooltipDesc = NodeInstance->GetClass()->GetToolTipText();
		if ( !TooltipDesc.IsEmpty() )
		{
			return TooltipDesc;
		}
	}
	return FText::GetEmpty();
}

//~ End EdGraphSchema Interface

/** initialize instance object  */
void UPLUGIN_NAMEGraphNode::InitializeInstance() {}

#undef LOCTEXT_NAMESPACE
