// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/Blueprint.h"
#include "PLUGIN_NAME.generated.h"

/**
 * 
 */
UCLASS( MinimalAPI )
class UPLUGIN_NAME : public UObject
{
	GENERATED_UCLASS_BODY()
	

#if WITH_EDITORONLY_DATA

	/** Graph for Behavior Tree */
	UPROPERTY()
	TObjectPtr<class UEdGraph>	PLUGIN_NAMEGraph;

	/** Info about the graphs we last edited */
	UPROPERTY()
	TArray<FEditedDocumentInfo> LastEditedDocuments;

#endif

};
