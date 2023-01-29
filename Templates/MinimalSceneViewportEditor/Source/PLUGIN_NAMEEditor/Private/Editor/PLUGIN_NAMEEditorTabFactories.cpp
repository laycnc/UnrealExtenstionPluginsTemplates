#include "PLUGIN_NAMEEditorTabFactories.h"
#include "AdvancedPreviewSceneModule.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "EditorStyleSet.h"
#include "IPLUGIN_NAMEPreviewScene.h"
#include "Editor/PLUGIN_NAMEEditor.h"
#include "Editor/PLUGIN_NAMEEditorTabs.h"
//#include "PLUGIN_NAMEPreviewSceneDescription.h"
//#include "Editor/PLUGIN_NAMEDetails.h"
#include "Editor/PLUGIN_NAMEViewport.h"
//#include "Editor/SPLUGIN_NAMEEditor.h"

#define LOCTEXT_NAMESPACE "PLUGIN_NAMEEditorTabFactories"


//////////////////////////////////////////////////////////////////////////
// FAdvancedPreviewSceneSettingsTabSummoner

FAdvancedPreviewSceneSettingsTabSummoner::FAdvancedPreviewSceneSettingsTabSummoner(TSharedPtr<FPLUGIN_NAMEEditor> InHostingApp, const TSharedRef<IPLUGIN_NAMEPreviewScene>& InPreviewScene)
	: FWorkflowTabFactory(FPLUGIN_NAMEEditorTabs::AdvancedPreviewSceneSettingsID, InHostingApp)
	, PreviewScene(InPreviewScene)
{
}

TSharedRef<SWidget> FAdvancedPreviewSceneSettingsTabSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	//auto PreviewSceneRef = StaticCastSharedRef<FAnimationEditorPreviewScene>(PreviewScene.Pin().ToSharedRef());
	auto PreviewSceneRef = PreviewScene.Pin().ToSharedRef();

	TArray<FAdvancedPreviewSceneModule::FDetailCustomizationInfo> DetailsCustomizations;
	TArray<FAdvancedPreviewSceneModule::FPropertyTypeCustomizationInfo> PropertyTypeCustomizations;

	//DetailsCustomizations.Add({UPersonaPreviewSceneDescription::StaticClass(), FOnGetDetailCustomizationInstance::CreateSP(const_cast<FAdvancedPreviewSceneTabSummoner *>(this), &FAdvancedPreviewSceneTabSummoner::CustomizePreviewSceneDescription)});
	//PropertyTypeCustomizations.Add({FPreviewMeshCollectionEntry::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateSP(const_cast<FAdvancedPreviewSceneTabSummoner *>(this), &FAdvancedPreviewSceneTabSummoner::CustomizePreviewMeshCollectionEntry)});

	FAdvancedPreviewSceneModule& AdvancedPreviewSceneModule = FModuleManager::LoadModuleChecked<FAdvancedPreviewSceneModule>("AdvancedPreviewScene");
	return AdvancedPreviewSceneModule.CreateAdvancedPreviewSceneSettingsWidget(PreviewSceneRef, PreviewSceneRef->GetPreviewSceneDescription(), DetailsCustomizations, PropertyTypeCustomizations);
}

FText FAdvancedPreviewSceneSettingsTabSummoner::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return LOCTEXT("AdvancedPreviewSettingsToolTip", "The Advanced Preview Settings tab will let you alter the preview scene's settings.");
}


#if 0


//////////////////////////////////////////////////////////////////////////
// FDetailsTabSummoner


FDetailsTabSummoner::FDetailsTabSummoner(TSharedPtr<class FPLUGIN_NAMEEditor> InHostingApp)
	: FWorkflowTabFactory(FPLUGIN_NAMEEditorTabs::DetailsID, InHostingApp)
{
	TabLabel = LOCTEXT("DetailsTab", "Details");
	TabIcon = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details");
	bIsSingleton = true;

	ViewMenuDescription = LOCTEXT("DetailsDescription", "Details");
	ViewMenuTooltip = LOCTEXT("DetailsToolTip", "Shows the details tab for selected objects.");

	Details = SNew(SPLUGIN_NAMEDetails);

	//OnDetailsCreated.ExecuteIfBound(PersonaDetails->DetailsView.ToSharedRef());
}

TSharedRef<SWidget> FDetailsTabSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	return Details.ToSharedRef();
}

FText FDetailsTabSummoner::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return LOCTEXT("PersonaDetailsToolTip", "Edit the details of selected objects.");
}

//////////////////////////////////////////////////////////////////////////
// FEasinessEditorTabSummoner


FEasinessEditorTabSummoner::FEasinessEditorTabSummoner(TSharedPtr<FPLUGIN_NAMEEditorToolkit> InHostingApp)
	: FWorkflowTabFactory(FPLUGIN_NAMEEditorTabs::TimelineID, InHostingApp)
{
	TabLabel = LOCTEXT("TimelineTab", "Timeline");
	Editor = SNew(SPLUGIN_NAMEEditor, InHostingApp.ToSharedRef());
}

TSharedRef<SWidget> FEasinessEditorTabSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	return Editor.ToSharedRef();
}

FText FEasinessEditorTabSummoner::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return LOCTEXT("PersonaDetailsToolTip", "Edit the details of selected objects.");
}

#endif


//////////////////////////////////////////////////////////////////////////
// FPreviewViewportSummoner


FPreviewViewportSummoner::FPreviewViewportSummoner(TSharedRef<FPLUGIN_NAMEEditor> InHostingApp, int32 InViewportIndex)
	: FWorkflowTabFactory(FPLUGIN_NAMEEditorTabs::ViewportInstanceToTabName(InViewportIndex), InHostingApp)
	, HostingAppPtr(InHostingApp)
{
	TabLabel = FText::Format(LOCTEXT("ViewportTabTitle", "Viewport {0}"), FText::AsNumber(InViewportIndex + 1));
	TabIcon = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Viewports");

	//bIsSingleton = true;

	ViewMenuDescription = FText::Format(LOCTEXT("ViewportViewFormat", "Viewport {0}"), FText::AsNumber(InViewportIndex + 1));
	ViewMenuTooltip = LOCTEXT("ViewportView_ToolTip", "Shows the viewport");
}

FTabSpawnerEntry& FPreviewViewportSummoner::RegisterTabSpawner(TSharedRef<FTabManager> TabManager, const FApplicationMode* CurrentApplicationMode) const
{
	FTabSpawnerEntry& SpawnerEntry = FWorkflowTabFactory::RegisterTabSpawner(TabManager, nullptr);

	if (CurrentApplicationMode)
	{
		// find an existing workspace item or create new
		TSharedPtr<FWorkspaceItem> GroupItem = nullptr;

		for (const TSharedRef<FWorkspaceItem>& Item : CurrentApplicationMode->GetWorkspaceMenuCategory()->GetChildItems())
		{
			if (Item->GetDisplayName().ToString() == LOCTEXT("ViewportsSubMenu", "Viewports").ToString())
			{
				GroupItem = Item;
				break;
			}
		}

		if (!GroupItem.IsValid())
		{
			GroupItem = CurrentApplicationMode->GetWorkspaceMenuCategory()->AddGroup(LOCTEXT("ViewportsSubMenu", "Viewports"), LOCTEXT("ViewportsSubMenu_Tooltip", "Open a new viewport on the scene"), FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Viewports"));
		}

		SpawnerEntry.SetGroup(GroupItem.ToSharedRef());
	}

	return SpawnerEntry;
}

TSharedRef<SWidget> FPreviewViewportSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
#if 0
	TSharedRef<SAnimationEditorViewportTabBody> NewViewport = SNew(SAnimationEditorViewportTabBody, PreviewScene.Pin().ToSharedRef(), HostingApp.Pin().ToSharedRef(), ViewportIndex)
		.BlueprintEditor(BlueprintEditor.Pin())
		.OnInvokeTab(FOnInvokeTab::CreateSP(HostingApp.Pin().Get(), &FPLUGIN_NAMEEditor::InvokeTab))
		.AddMetaData<FTagMetaData>(TEXT("Persona.Viewport"))
		.Extenders(Extenders)
		.ContextName(ContextName)
		.OnGetViewportText(OnGetViewportText)
		.ShowShowMenu(bShowShowMenu)
		.ShowLODMenu(bShowLODMenu)
		.ShowPlaySpeedMenu(bShowPlaySpeedMenu)
		.ShowTimeline(bShowTimeline)
		.ShowStats(bShowStats)
		.AlwaysShowTransformToolbar(bAlwaysShowTransformToolbar)
		.ShowFloorOptions(bShowFloorOptions)
		.ShowTurnTable(bShowTurnTable)
		.ShowPhysicsMenu(bShowPhysicsMenu);

	OnViewportCreated.ExecuteIfBound(NewViewport);
	return NewViewport;
#else
	return SNew(SPLUGIN_NAMEViewport, HostingAppPtr.Pin().ToSharedRef());
#endif
}

#undef LOCTEXT_NAMESPACE
