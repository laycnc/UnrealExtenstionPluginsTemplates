#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Framework/MultiBox/MultiBoxExtender.h"
#include "Logging/TokenizedMessage.h"
#include "SEditorViewport.h"

class FPLUGIN_NAMEEditor;
class IPLUGIN_NAMEPreviewScene;
class FEditorViewportClient;
class SViewportToolBar;

class IPLUGIN_NAMEViewport 
	: public SEditorViewport
{
public:

	virtual TSharedRef<FPLUGIN_NAMEEditor> GetToolkit() const = 0;
	virtual TSharedRef<IPLUGIN_NAMEPreviewScene> GetPreviewScene() const = 0;

};