// Copyright(c) 2023 laycnc

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "IPluginBrowser.h"
#include "Interfaces/IPluginManager.h"
#include "Features/EditorFeatures.h"
#include "Features/IPluginsEditorFeature.h"
#include "ExtenstionPluginsTemplateSettings.h"

#define LOCTEXT_NAMESPACE "FExtenstionPluginsTemplatesModule"

class FExtenstionPluginsTemplatesModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TArray<TSharedPtr<FPluginTemplateDescription>> PluginTemplateDescriptions;

};

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

        IPluginManager& PluginManager = IPluginManager::Get();
		auto ExtenstionPluginsTemplatesPlugin = PluginManager.GetModuleOwnerPlugin(TEXT("ExtenstionPluginsTemplates"));
		if ( ExtenstionPluginsTemplatesPlugin.IsValid() )
		{
			// ExtenstionPluginsTemplates plugin base dir
			const FString BaseDir = ExtenstionPluginsTemplatesPlugin->GetBaseDir();

			for ( const FExtenstionPluginsTemplateData& Template :
			      GetDefault<UExtenstionPluginsTemplateSettings>()->PluginTemplates )
			{
				FText               InName                 = Template.Label;
				FText               InDescription          = Template.Description;
				FString             InOnDiskPath = BaseDir + "/" + Template.Path;
				bool                InCanContainContent    = false;
				EHostType::Type     InModuleDescriptorType = EHostType::Runtime;
				ELoadingPhase::Type InLoadingPhase         = ELoadingPhase::Default;

				TSharedPtr<FPluginTemplateDescription> Description = MakeShareable(
				    new FPluginTemplateDescription(InName,
				                                   InDescription,
				                                   InOnDiskPath,
				                                   InCanContainContent,
				                                   InModuleDescriptorType,
				                                   InLoadingPhase));
				PluginTemplateDescriptions.Add(Description);
				PluginEditor.RegisterPluginTemplate(Description.ToSharedRef());
			}
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