

#include "PLUGIN_NAMEEditorTabs.h"

#include "HAL/Platform.h"
#include "UObject/NameTypes.h"


const FName FPLUGIN_NAMEEditorTabs::AdvancedPreviewSceneSettingsID = FName(TEXT("AdvancedPreviewSceneSettingsID"));
const FName DetailsID = TEXT("PLUGIN_NAMEDetails");
const FName MainViewportID = TEXT("Viewport");
const FName TimelineID = TEXT("Timeline");

const FName FPLUGIN_NAMEEditorTabs::PLUGIN_NAMEEditorMode(TEXT("PLUGIN_NAME"));

const FName FPLUGIN_NAMEEditorTabs::EditorAppIdentifier = FName(TEXT("PLUGIN_NAMEEditorToolkitApp"));
const FName FPLUGIN_NAMEEditorTabs::PropertiesTabId = FName(TEXT("PLUGIN_NAMEEditorToolkit_Properties"));
const FName FPLUGIN_NAMEEditorTabs::ToolkitFName = FName(TEXT("PLUGIN_NAMEEditorToolkit"));


FName FPLUGIN_NAMEEditorTabs::ViewportInstanceToTabName(int32 Index)
{
	static const FName ArrayIn[4] = { "Viewport", "Viewport1", "Viewport2", "Viewport3" };
	return ArrayIn[Index];
}