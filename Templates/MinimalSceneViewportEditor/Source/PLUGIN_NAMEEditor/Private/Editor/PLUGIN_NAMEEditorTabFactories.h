#pragma once

#include "WorkflowOrientedApp/WorkflowTabFactory.h"

class FPLUGIN_NAMEEditor;

//////////////////////////////////////////////////////////////////////////
// FAdvancedPreviewSceneSettingsTabSummoner

struct FAdvancedPreviewSceneSettingsTabSummoner
	: public FWorkflowTabFactory
{
public:
	FAdvancedPreviewSceneSettingsTabSummoner(TSharedPtr<FPLUGIN_NAMEEditor> InHostingApp, const TSharedRef<IPLUGIN_NAMEPreviewScene> &InPreviewScene);
	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo &Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo &Info) const override;

private:
	TWeakPtr<IPLUGIN_NAMEPreviewScene> PreviewScene;
};

//////////////////////////////////////////////////////////////////////////
// FPreviewViewportSummoner

struct FPreviewViewportSummoner
	: public FWorkflowTabFactory
{
	FPreviewViewportSummoner(TSharedRef<FPLUGIN_NAMEEditor> InHostingApp, int32 InViewportIndex);

	virtual FTabSpawnerEntry& RegisterTabSpawner(TSharedRef<FTabManager> TabManager, const FApplicationMode* CurrentApplicationMode) const override;
	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;

private:
	TWeakPtr<FPLUGIN_NAMEEditor> HostingAppPtr;
};