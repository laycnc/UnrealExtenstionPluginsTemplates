#include "Editor/PLUGIN_NAMEViewport.h"
#include "Editor/PLUGIN_NAMEPreviewScene.h"
#include "Editor/PLUGIN_NAMEEditor.h"
#include "SViewportToolBar.h"

void SPLUGIN_NAMEViewport::Construct(const FArguments &InArgs, TSharedRef<FPLUGIN_NAMEEditor> Toolkit)
{
	ToolkitPtr = Toolkit;
	PreviewScenePtr = Toolkit->GetPreviewScene();

	Super::Construct(SEditorViewport::FArguments());
}

SPLUGIN_NAMEViewport::SPLUGIN_NAMEViewport() 
{
}

SPLUGIN_NAMEViewport::~SPLUGIN_NAMEViewport() 
{
}

// SEditorViewport interface

TSharedRef<FEditorViewportClient> SPLUGIN_NAMEViewport::MakeEditorViewportClient()
{

	LevelViewportClient = MakeShareable(new FEditorViewportClient(nullptr, &GetPreviewScene().Get(), SharedThis(this)));

	LevelViewportClient->ViewportType = LVT_Perspective;
	LevelViewportClient->bSetListenerPosition = false;
	LevelViewportClient->SetViewLocation(EditorViewportDefs::DefaultPerspectiveViewLocation);
	LevelViewportClient->SetViewRotation(EditorViewportDefs::DefaultPerspectiveViewRotation);

	return LevelViewportClient.ToSharedRef();
}

TSharedPtr<SWidget> SPLUGIN_NAMEViewport::MakeViewportToolbar()
{
#if 0
	return SAssignNew(ViewportToolbar, SAnimViewportToolBar, TabBodyPtr.Pin(), SharedThis(this))
		.Cursor(EMouseCursor::Default)
		.Extenders(Extenders)
		.ContextName(ContextName)
		.ShowShowMenu(bShowShowMenu)
		.ShowLODMenu(bShowLODMenu)
		.ShowPlaySpeedMenu(bShowPlaySpeedMenu)
		.ShowFloorOptions(bShowFloorOptions)
		.ShowTurnTable(bShowTurnTable)
		.ShowPhysicsMenu(bShowPhysicsMenu);
#else
	return SAssignNew(ViewportToolbar, SViewportToolBar);
#endif
}

void SPLUGIN_NAMEViewport::OnFocusViewportToSelection()
{
	//TSharedRef<FAnimationViewportClient> AnimViewportClient = StaticCastSharedRef<FAnimationViewportClient>(LevelViewportClient.ToSharedRef());
	//AnimViewportClient->SetCameraFollowMode(EAnimationViewportCameraFollowMode::None);
	//AnimViewportClient->FocusViewportOnPreviewMesh(false);
}

void SPLUGIN_NAMEViewport::PopulateViewportOverlays(TSharedRef<SOverlay> Overlay)
{
	SEditorViewport::PopulateViewportOverlays(Overlay);

}

// End of SEditorViewport interface


// IEasinessSequencerViewport interface

TSharedRef<FPLUGIN_NAMEEditor> SPLUGIN_NAMEViewport::GetToolkit() const
{
	return ToolkitPtr.Pin().ToSharedRef();
}

TSharedRef<IPLUGIN_NAMEPreviewScene> SPLUGIN_NAMEViewport::GetPreviewScene() const
{
	return PreviewScenePtr.Pin().ToSharedRef();
}

// End of IEasinessSequencerViewport interface
