// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

class FName;

struct FPLUGIN_NAMEEditorTabs
{
    static const FName AdvancedPreviewSceneSettingsID;

    static const FName PLUGIN_NAMEEditorMode;
    
	/** App Identifier. Technically, all simple editors are the same app, despite editing a variety of assets. */
	static const FName EditorAppIdentifier;

	/**	The tab ids for all the tabs used */
	static const FName PropertiesTabId;

	/** The name given to all instances of this type of editor */
	static const FName ToolkitFName;

	static FName ViewportInstanceToTabName(int32 Index);
};

