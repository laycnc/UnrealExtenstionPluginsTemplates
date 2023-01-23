// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

struct FGraphNodeClassHelper;

class IPLUGIN_NAMEEditorModule : public IModuleInterface
{
public:
	static IPLUGIN_NAMEEditorModule& Get();

	virtual TSharedPtr<FGraphNodeClassHelper> GetClassCache() = 0;

};
