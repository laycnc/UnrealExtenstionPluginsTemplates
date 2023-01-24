// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtenstionPluginsTemplateSettings.h"

#define LOCTEXT_NAMESPACE "UExtenstionPluginsTemplateSettings"

UExtenstionPluginsTemplateSettings::UExtenstionPluginsTemplateSettings(const FObjectInitializer& ObjectInitializer)
{
	{
		FExtenstionPluginsTemplateData MinimalTemplate = {};
		MinimalTemplate.Path  = TEXT("Templates/MinimalAsset");
		MinimalTemplate.Label = LOCTEXT("MinimalAsset_Label", "MinimalAsset");
		MinimalTemplate.Description =
		    LOCTEXT("MinimalAsset_Description", "Asset with minimum configuration");
		MinimalTemplate.bIsEnabledByDefault = false;

		PluginTemplates.Add(MinimalTemplate);
	}
	{
		FExtenstionPluginsTemplateData MinimalAssetEditorTemplate = {};
		MinimalAssetEditorTemplate.Path  = TEXT("Templates/MinimalAssetEditor");
		MinimalAssetEditorTemplate.Label = LOCTEXT("MinimalAssetEditor_Label", "MinimalAssetEditor");
		MinimalAssetEditorTemplate.Description =
		    LOCTEXT("MinimalAssetEditor_Description", "Asset Editor Minimum Configuration");
		MinimalAssetEditorTemplate.bIsEnabledByDefault = false;

		PluginTemplates.Add(MinimalAssetEditorTemplate);
	}
	{
		FExtenstionPluginsTemplateData MinimalMovieSceneTemplate = {};
		MinimalMovieSceneTemplate.Path  = TEXT("Templates/MinimalMovieScene");
		MinimalMovieSceneTemplate.Label = LOCTEXT("MinimalMovieScene_Label", "MinimalMovieScene");
		MinimalMovieSceneTemplate.Description = LOCTEXT("MinimalMovieScene_Description", "Create a movie scene track with minimal configuration");
		MinimalMovieSceneTemplate.bIsEnabledByDefault = false;

		PluginTemplates.Add(MinimalMovieSceneTemplate);
	}
	{
		FExtenstionPluginsTemplateData MinimalMovieSceneTemplate = {};
		MinimalMovieSceneTemplate.Path  = TEXT("Templates/MinimalGraph");
		MinimalMovieSceneTemplate.Label = LOCTEXT("MinimalGraph_Label", "MinimalGraph");
		MinimalMovieSceneTemplate.Description = LOCTEXT("MinimalGraph_Description", "Create a minimally configured graph editor");
		MinimalMovieSceneTemplate.bIsEnabledByDefault = false;

		PluginTemplates.Add(MinimalMovieSceneTemplate);
	}
}

#undef LOCTEXT_NAMESPACE
