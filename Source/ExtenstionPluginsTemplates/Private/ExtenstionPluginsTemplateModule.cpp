// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "IPluginBrowser.h"
#include "Features/EditorFeatures.h"
#include "Features/IPluginsEditorFeature.h"
#include "ExtenstionPluginsTemplateSettings.h"

class FExtenstionPluginsTemplatesModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TArray<TSharedPtr<FPluginTemplateDescription>> PluginTemplateDescriptions;

};

#define LOCTEXT_NAMESPACE "FExtenstionPluginsTemplatesModule"

void FExtenstionPluginsTemplatesModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

    if ( IModularFeatures::Get().IsModularFeatureAvailable( EditorFeatures::PluginsEditor) )
	{
		IPluginsEditorFeature& PluginEditor = IModularFeatures::Get().GetModularFeature<IPluginsEditorFeature>(EditorFeatures::PluginsEditor);
		for ( const auto& TemplateDescription : PluginTemplateDescriptions )
		{
			PluginEditor.RegisterPluginTemplate(TemplateDescription.ToSharedRef());
		}

        for ( const FExtenstionPluginsTemplateData& Template : GetDefault<UExtenstionPluginsTemplateSettings>()->PluginTemplates )
        {
			FText InName = Template.Label;
			FText InDescription = Template.Description;
			FString InOnDiskPath  = Template.Path.Path;
			bool    InCanContainContent = false;
			EHostType::Type InModuleDescriptorType = EHostType::Runtime;
            ELoadingPhase::Type InLoadingPhase = ELoadingPhase::Default;

            TSharedPtr<FPluginTemplateDescription> Description = MakeShareable(new FPluginTemplateDescription( InName, InDescription, InOnDiskPath, InCanContainContent, InModuleDescriptorType, InLoadingPhase ));
			PluginTemplateDescriptions.Add(Description);
            PluginEditor.RegisterPluginTemplate(Description.ToSharedRef());
        }

	}


}

void FExtenstionPluginsTemplatesModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

    if ( IModularFeatures::Get().IsModularFeatureAvailable(
	         EditorFeatures::PluginsEditor) )
	{
		IPluginsEditorFeature& PluginEditor =
		    IModularFeatures::Get().GetModularFeature<IPluginsEditorFeature>(
		        EditorFeatures::PluginsEditor);

		for ( const auto& Description : PluginTemplateDescriptions )
		{
			PluginEditor.UnregisterPluginTemplate(Description.ToSharedRef());
		}
		PluginTemplateDescriptions.Emplace();
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FExtenstionPluginsTemplatesModule, ExtenstionPluginsTemplates)