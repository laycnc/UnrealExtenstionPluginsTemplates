// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "IAssetTools.h"
#include "ISequencerModule.h"
#include "TrackEditors/PLUGIN_NAMETrackEditor.h"

#define LOCTEXT_NAMESPACE "PLUGIN_NAMEEditorModule"

class FPLUGIN_NAMEEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
private:
	FDelegateHandle PLUGIN_NAMETrackEditorHandle;
};


void FPLUGIN_NAMEEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    
    ISequencerModule& SequencerModule = FModuleManager::Get().LoadModuleChecked<ISequencerModule>("Sequencer");
	PLUGIN_NAMETrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(FPLUGIN_NAMETrackEditor::CreateTrackEditor));
}

void FPLUGIN_NAMEEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

    ISequencerModule& SequencerModule = FModuleManager::Get().LoadModuleChecked<ISequencerModule>("Sequencer");
	SequencerModule.UnRegisterTrackEditor(PLUGIN_NAMETrackEditorHandle);

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPLUGIN_NAMEEditorModule, MovieSequencerTrackSampleEditor)