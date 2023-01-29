#pragma once

#include "CoreMinimal.h"
#include "AdvancedPreviewScene.h"
#include "Containers/ArrayView.h"
#include "Types/SlateEnums.h"

class UPLUGIN_NAMEPreviewSceneDescription;

class IPLUGIN_NAMEPreviewScene
	: public FAdvancedPreviewScene
{
public:
	IPLUGIN_NAMEPreviewScene(ConstructionValues CVS)
		: FAdvancedPreviewScene(CVS)
	{}

	virtual UPLUGIN_NAMEPreviewSceneDescription* GetPreviewSceneDescription() const = 0;

};