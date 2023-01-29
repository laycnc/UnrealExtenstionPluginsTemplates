// Copyright Epic Games, Inc. All Rights Reserved.

#include "PLUGIN_NAMEEditor.h"
#include "Framework/Commands/GenericCommands.h"
#include "PLUGIN_NAME.h"
#include "PLUGIN_NAMEEditorCommands.h"
#include "Editor/PLUGIN_NAMEPreviewScene.h"
#include "Editor/PLUGIN_NAMEEditorTabs.h"
#include "Editor/PLUGIN_NAMEEditorMode.h"

#define LOCTEXT_NAMESPACE "FPLUGIN_NAMEEditor"

//////////////////////////////////////////////////////////////////////////

const FName PLUGIN_NAMEEditorAppName = FName(TEXT("PLUGIN_NAMEEditorApp"));

//////////////////////////////////////////////////////////////////////////
// PLUGIN_NAMEEditor

void FPLUGIN_NAMEEditor::InitPLUGIN_NAMEEditor(
	const EToolkitMode::Type        Mode,
	const TSharedPtr<IToolkitHost>& InitToolkitHost,
	UPLUGIN_NAME* InitAsset)
{
	AssetEdited = InitAsset;
	PreviewScene = MakeShareable(new FPLUGIN_NAMEPreviewScene(FPreviewScene::ConstructionValues().AllowAudioPlayback(true).ShouldSimulatePhysics(true)));

	BindCommands();

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	// Initialize the asset editor and spawn nothing (dummy layout)
	InitAssetEditor(Mode,
		InitToolkitHost,
		PLUGIN_NAMEEditorAppName,
		FTabManager::FLayout::NullLayout,
		bCreateDefaultStandaloneMenu,
		bCreateDefaultToolbar,
		InitAsset);

	AddApplicationMode(
		FPLUGIN_NAMEEditorTabs::PLUGIN_NAMEEditorMode,
		MakeShareable(new FPLUGIN_NAMEEditorMode(SharedThis(this))));

	SetCurrentMode(FPLUGIN_NAMEEditorTabs::PLUGIN_NAMEEditorMode);
}

FPLUGIN_NAMEEditor::FPLUGIN_NAMEEditor()
{
}

FPLUGIN_NAMEEditor ::~FPLUGIN_NAMEEditor()
{
}

// IToolkit interface
void FPLUGIN_NAMEEditor::RegisterTabSpawners(
	const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
}
void FPLUGIN_NAMEEditor::UnregisterTabSpawners(
	const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
}
// End of IToolkit interface

// FAssetEditorToolkit
FName FPLUGIN_NAMEEditor::GetToolkitFName() const
{
	return FName("PLUGIN_NAMEEditor");
}

FText FPLUGIN_NAMEEditor::GetBaseToolkitName() const
{
	return LOCTEXT("FPLUGIN_NAMEEditorAppLabel", "Dev Menu Editor");
}

FText FPLUGIN_NAMEEditor::GetToolkitName() const
{
	return FText::FromString(AssetEdited->GetName());
}

FText FPLUGIN_NAMEEditor::GetToolkitToolTipText() const
{
	return FAssetEditorToolkit::GetToolTipTextForObject(AssetEdited);
}

FLinearColor FPLUGIN_NAMEEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}

FString FPLUGIN_NAMEEditor::GetWorldCentricTabPrefix() const
{
	return TEXT("PLUGIN_NAMEEditor");
}

// End of FAssetEditorToolkit

// FGCObject interface
void FPLUGIN_NAMEEditor::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(AssetEdited);
}

FString FPLUGIN_NAMEEditor::GetReferencerName() const
{
	return TEXT("FPLUGIN_NAMEEditor");
}

// End of FGCObject interface


void FPLUGIN_NAMEEditor::BindCommands()
{
	FPLUGIN_NAMEEditorCommands::Register();
}

#undef LOCTEXT_NAMESPACE
