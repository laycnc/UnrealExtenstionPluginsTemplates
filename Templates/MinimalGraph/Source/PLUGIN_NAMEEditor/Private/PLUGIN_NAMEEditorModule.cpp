// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "IAssetTools.h"
#include "AIGraphTypes.h"
#include "IPLUGIN_NAMEEditorModule.h"
#include "AssetTypeActions/AssetTypeActions_PLUGIN_NAME.h"
#include "PLUGIN_NAMENode.h"

#define LOCTEXT_NAMESPACE "FPLUGIN_NAMEEditorModule"

IPLUGIN_NAMEEditorModule& IPLUGIN_NAMEEditorModule::Get()
{
	return FModuleManager::GetModuleChecked<IPLUGIN_NAMEEditorModule>(
	    TEXT("PLUGIN_NAMEEditor"));
}

class FPLUGIN_NAMEEditorModule : public IPLUGIN_NAMEEditorModule
{
public:
	/** IModuleInterface implementation */
	virtual void                              StartupModule() override;
	virtual void                              ShutdownModule() override;
	virtual TSharedPtr<FGraphNodeClassHelper> GetClassCache() override;
private:
	TSharedPtr<IAssetTypeActions>     PLUGIN_NAMETypeAction;
	TSharedPtr<FGraphNodeClassHelper> ClassCache;
};

void FPLUGIN_NAMEEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	{
		// Register Asset Type Actions
		IAssetTools& AssetTools = IAssetTools::Get();

		PLUGIN_NAMETypeAction = MakeShareable(new FAssetTypeActions_PLUGIN_NAME());
		AssetTools.RegisterAssetTypeActions(PLUGIN_NAMETypeAction.ToSharedRef());
	}
}

void FPLUGIN_NAMEEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	{
		// Unregister Asset Type Actions
		IAssetTools& AssetTools = IAssetTools::Get();

		AssetTools.UnregisterAssetTypeActions(PLUGIN_NAMETypeAction.ToSharedRef());
		PLUGIN_NAMETypeAction.Reset();
	}
}

TSharedPtr<FGraphNodeClassHelper> FPLUGIN_NAMEEditorModule::GetClassCache()
{
	if ( !ClassCache.IsValid() )
	{
		ClassCache =
		    MakeShareable(new FGraphNodeClassHelper(UPLUGIN_NAMENode::StaticClass()));
		ClassCache->UpdateAvailableBlueprintClasses();
	}
	return ClassCache;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPLUGIN_NAMEEditorModule, PLUGIN_NAMEEditor)