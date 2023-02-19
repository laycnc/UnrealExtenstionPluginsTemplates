// Copyright(c) 2023 laycnc

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
		FExtenstionPluginsTemplateData MinimalGraphSceneTemplate = {};
		MinimalGraphSceneTemplate.Path  = TEXT("Templates/MinimalGraph");
		MinimalGraphSceneTemplate.Label = LOCTEXT("MinimalGraph_Label", "MinimalGraph");
		MinimalGraphSceneTemplate.Description = LOCTEXT("MinimalGraph_Description", "Create a minimally configured graph editor");
		MinimalGraphSceneTemplate.bIsEnabledByDefault = false;

		PluginTemplates.Add(MinimalGraphSceneTemplate);
	}
	{
		FExtenstionPluginsTemplateData MinimalSceneViewportEditorTemplate = {};
		MinimalSceneViewportEditorTemplate.Path  = TEXT("Templates/MinimalSceneViewportEditor");
		MinimalSceneViewportEditorTemplate.Label = LOCTEXT("MinimalSceneViewportEditor_Label", "MinimalSceneViewportEditor");
		MinimalSceneViewportEditorTemplate.Description = LOCTEXT("MinimalSceneViewportEditor_Description", "Minimally configured asset editor with scene viewport");
		MinimalSceneViewportEditorTemplate.bIsEnabledByDefault = false;

		PluginTemplates.Add(MinimalSceneViewportEditorTemplate);
	}
}

#undef LOCTEXT_NAMESPACE
