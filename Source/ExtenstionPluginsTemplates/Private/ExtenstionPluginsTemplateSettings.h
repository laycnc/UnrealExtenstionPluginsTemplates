// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ExtenstionPluginsTemplateSettings.generated.h"

USTRUCT()
struct FExtenstionPluginsTemplateData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = PluginTemplate, meta = (RelativePath))
	FString Path;

	UPROPERTY(EditAnywhere, Category = PluginTemplate)
	FText Label;

	UPROPERTY(EditAnywhere, Category = PluginTemplate)
	FText Description;

	/** If true, the created plugin will be enabled by default without needing to be added to the project file. */
	UPROPERTY(config, EditAnywhere, Category = Plugins)
	bool bIsEnabledByDefault = false;
};

/**
 * 
 */
UCLASS(config = Editor, defaultconfig)
class UExtenstionPluginsTemplateSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	// Array of Plugin templates. Allows projects to specify reusable plugin templates for the plugin creation wizard.
	UPROPERTY(config, EditAnywhere, Category = Plugins)
	TArray<FExtenstionPluginsTemplateData> PluginTemplates;
};
