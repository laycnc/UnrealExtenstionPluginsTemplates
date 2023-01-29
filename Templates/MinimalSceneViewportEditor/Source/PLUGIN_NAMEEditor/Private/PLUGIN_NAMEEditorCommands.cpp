// Copyright Epic Games, Inc. All Rights Reserved.

#include "PLUGIN_NAMEEditorCommands.h"
#include "Styling/AppStyle.h"
#include "UObject/NameTypes.h"
#include "UObject/UnrealNames.h"

#define LOCTEXT_NAMESPACE "PLUGIN_NAMEEditorCommands"

FPLUGIN_NAMEEditorCommands::FPLUGIN_NAMEEditorCommands() 
	: TCommands<FPLUGIN_NAMEEditorCommands>("PLUGIN_NAMEEditor",
                                         LOCTEXT("PLUGIN_NAMEEditor", "PLUGIN_NAME Editor"),
                                         NAME_None,
                                         FAppStyle::GetAppStyleSetName())
{
}

void FPLUGIN_NAMEEditorCommands::RegisterCommands()
{
    // UI_COMMAND 
}

#undef LOCTEXT_NAMESPACE
