// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "PLUGIN_NAMEGraph.generated.h"

/**
 * 
 */
UCLASS()
class UPLUGIN_NAMEGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	virtual void OnCreated();
	virtual void OnLoaded();
	virtual void Initialize();
};
