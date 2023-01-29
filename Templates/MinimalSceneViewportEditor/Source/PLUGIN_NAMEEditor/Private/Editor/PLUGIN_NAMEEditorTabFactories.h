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

#if 0

/**
 * 詳細タブ
 */
struct FDetailsTabSummoner : public FWorkflowTabFactory
{
public:
	FDetailsTabSummoner(TSharedPtr<class FPLUGIN_NAMEEditor> InHostingApp)
		: FWorkflowTabFactory(PLUGIN_NAMEDetailsID, InHostingApp)
	{
		TabLabel = LOCTEXT("PersonaDetailsTab", "Details");
		TabIcon = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details");
		bIsSingleton = true;

		ViewMenuDescription = LOCTEXT("DetailsDescription", "Details");
		ViewMenuTooltip = LOCTEXT("DetailsToolTip", "Shows the details tab for selected objects.");

		Details = SNew(SPLUGIN_NAMEDetails);

		// OnDetailsCreated.ExecuteIfBound(PersonaDetails->DetailsView.ToSharedRef());
	}

	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo &Info) const override
	{
		return Details.ToSharedRef();
	}

	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo &Info) const override
	{
		return LOCTEXT("PersonaDetailsToolTip", "Edit the details of selected objects.");
	}

private:
	TSharedPtr<SPLUGIN_NAMEDetails> Details;
};

/**
 * 詳細タブ
 */
struct FEasinessEditorTabSummoner : public FWorkflowTabFactory
{
public:
	FEasinessEditorTabSummoner(TSharedPtr<FPLUGIN_NAMEEditor> InHostingApp)
		: FWorkflowTabFactory(PLUGIN_NAMEEditorID, InHostingApp)
	{
		Editor = SNew(SPLUGIN_NAMEEditor, InHostingApp.ToSharedRef());
	}

	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo &Info) const override
	{
		return Editor.ToSharedRef();
	}

	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo &Info) const override
	{
		return LOCTEXT("PersonaDetailsToolTip", "Edit the details of selected objects.");
	}

private:
	TSharedPtr<SPLUGIN_NAMEEditor> Editor;
};

#endif


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