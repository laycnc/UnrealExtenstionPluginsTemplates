#include "Editor/PLUGIN_NAMEPreviewScene.h"

FPLUGIN_NAMEPreviewScene::FPLUGIN_NAMEPreviewScene(ConstructionValues CVS)
	: Super(CVS) 
{
	// create the preview scene description
	PreviewSceneDescription = NewObject<UPLUGIN_NAMEPreviewSceneDescription>(GetTransientPackage());
	PreviewSceneDescription->SetFlags(RF_Transactional);
}

FPLUGIN_NAMEPreviewScene::~FPLUGIN_NAMEPreviewScene() {}

void FPLUGIN_NAMEPreviewScene::FlagTickable()
{
	LastTickTime = FPlatformTime::Seconds();
}

/** FPreviewScene interface */
void FPLUGIN_NAMEPreviewScene::Tick(float InDeltaTime)
{
	Super::Tick(InDeltaTime);

	if (!GIntraFrameDebuggingGameThread)
	{
		GetWorld()->Tick(LEVELTICK_All, InDeltaTime);
	}
}

bool FPLUGIN_NAMEPreviewScene::IsTickable() const
{
	constexpr float VisibilityTimeThreshold = 0.25f;

	// The preview scene is tickable if any viewport can see it
	return  LastTickTime == 0.0 ||	// Never been ticked
		FPlatformTime::Seconds() - LastTickTime <= VisibilityTimeThreshold;	// Ticked recently
}

UPLUGIN_NAMEPreviewSceneDescription* FPLUGIN_NAMEPreviewScene::GetPreviewSceneDescription() const 
{
	return PreviewSceneDescription;
}
