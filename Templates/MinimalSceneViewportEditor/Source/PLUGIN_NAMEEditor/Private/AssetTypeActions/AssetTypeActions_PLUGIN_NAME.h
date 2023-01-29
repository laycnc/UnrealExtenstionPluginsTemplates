// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/IToolkitHost.h"
#include "AssetTypeActions_Base.h"

/**
 *
 */
class FAssetTypeActions_PLUGIN_NAME : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_PLUGIN_NAME();
	// IAssetTypeActions interface
	virtual FText   GetName() const override;
	virtual FColor  GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual bool    HasActions(const TArray<UObject*>& InObjects) const override;
	virtual void    GetActions(const TArray<UObject*>&  InObjects, struct FToolMenuSection& Section) override;
	virtual uint32  GetCategories() override;
	virtual void    OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor) override;
	// End of IAssetTypeActions interface
};
