// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EdGraph/EdGraphNode.h"
#include "AIGraphTypes.h"
#include "PLUGIN_NAMEGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class UPLUGIN_NAMEGraphNode : public UEdGraphNode
{
	GENERATED_UCLASS_BODY()
public:
	//~ Begin EdGraphSchema Interface
	virtual void  PostPlacedNewNode() override;
	virtual void  AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	//~ End EdGraphSchema Interface

protected:
	/** initialize instance object  */
	virtual void InitializeInstance();

public:
	UPROPERTY()
	FGraphNodeClassData ClassData;

	UPROPERTY()
	TObjectPtr<UObject> NodeInstance = nullptr;
};
