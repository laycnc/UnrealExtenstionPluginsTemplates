#pragma once

#include "CoreMinimal.h"
#include "Input/Reply.h"
#include "Layout/Visibility.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "EngineDefines.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "BlueprintEditor.h"
#include "EditorViewportClient.h"
#include "SNameComboBox.h"
#include "IPLUGIN_NAMEViewport.h"

class IPLUGIN_NAMEPreviewScene;
class FPLUGIN_NAMEEditor;
class FEditorViewportClient;
class SViewportToolBar;

class SPLUGIN_NAMEViewport
	: public IPLUGIN_NAMEViewport
{
public:
    using Super = IPLUGIN_NAMEViewport;
	SLATE_BEGIN_ARGS(SPLUGIN_NAMEViewport)
		{}
	SLATE_END_ARGS()

public:

	void Construct(const FArguments& InArgs, TSharedRef<FPLUGIN_NAMEEditor> Toolkit);
	SPLUGIN_NAMEViewport();
	virtual ~SPLUGIN_NAMEViewport();

	// SEditorViewport interface
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
	virtual TSharedPtr<SWidget> MakeViewportToolbar() override;
	virtual void OnFocusViewportToSelection() override;
	virtual void PopulateViewportOverlays(TSharedRef<SOverlay> Overlay) override;
	// End of SEditorViewport interface

	// IPLUGIN_NAMEViewport interface
	virtual TSharedRef<FPLUGIN_NAMEEditor> GetToolkit() const override;
	virtual TSharedRef<IPLUGIN_NAMEPreviewScene> GetPreviewScene() const override;
	// End of IPLUGIN_NAMEViewport interface

private:
	TSharedPtr<FEditorViewportClient>   LevelViewportClient;
	TSharedPtr<SViewportToolBar>        ViewportToolbar;
	TWeakPtr<FPLUGIN_NAMEEditor>             ToolkitPtr;
	TWeakPtr<IPLUGIN_NAMEPreviewScene>       PreviewScenePtr;
};