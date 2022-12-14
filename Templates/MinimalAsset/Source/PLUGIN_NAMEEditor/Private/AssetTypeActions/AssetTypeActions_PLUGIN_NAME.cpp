// Fill out your copyright notice in the Description page of Project Settings.

#include "AssetTypeActions/AssetTypeActions_PLUGIN_NAME.h"
#include "PLUGIN_NAME.h"

#define LOCTEXT_NAMESPACE "FAssetTypeActions_PLUGIN_NAME"

FAssetTypeActions_PLUGIN_NAME::FAssetTypeActions_PLUGIN_NAME()
    : FAssetTypeActions_Base()
{
}

// IAssetTypeActions interface

FText FAssetTypeActions_PLUGIN_NAME::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_PLUGIN_NAME", "PLUGIN_NAME");
}
FColor FAssetTypeActions_PLUGIN_NAME::GetTypeColor() const
{
	return FColor(255, 255, 255);
}
UClass* FAssetTypeActions_PLUGIN_NAME::GetSupportedClass() const
{
	return UPLUGIN_NAME::StaticClass();
}

bool FAssetTypeActions_PLUGIN_NAME::HasActions(const TArray<UObject*>& InObjects) const
{
	return false;
}

void FAssetTypeActions_PLUGIN_NAME::GetActions(const TArray<UObject*>& InObjects, struct FToolMenuSection& Section)
{
}

uint32 FAssetTypeActions_PLUGIN_NAME::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

void FAssetTypeActions_PLUGIN_NAME::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
    FAssetTypeActions_Base::OpenAssetEditor(InObjects, EditWithinLevelEditor);
}

// End of IAssetTypeActions interface

#undef LOCTEXT_NAMESPACE
