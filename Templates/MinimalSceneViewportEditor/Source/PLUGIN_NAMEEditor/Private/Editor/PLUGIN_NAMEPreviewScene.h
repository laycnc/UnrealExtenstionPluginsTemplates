#pragma once

#include "CoreMinimal.h"
#include "IPLUGIN_NAMEPreviewScene.h"

class UPLUGIN_NAMEPreviewSceneDescription;

class FPLUGIN_NAMEPreviewScene
	: public IPLUGIN_NAMEPreviewScene
{
public:
	using Super = IPLUGIN_NAMEPreviewScene;

	FPLUGIN_NAMEPreviewScene(ConstructionValues CVS);
	~FPLUGIN_NAMEPreviewScene();

	virtual void FlagTickable(); // override;

	/** FPreviewScene interface */
	virtual void Tick(float InDeltaTime) override;
	virtual bool IsTickable() const override;
	virtual ETickableTickType GetTickableTickType() const { return ETickableTickType::Conditional; }

	virtual UPLUGIN_NAMEPreviewSceneDescription* GetPreviewSceneDescription() const override;
private:
	UPLUGIN_NAMEPreviewSceneDescription* PreviewSceneDescription = nullptr;
	double LastTickTime = 0.0;
};