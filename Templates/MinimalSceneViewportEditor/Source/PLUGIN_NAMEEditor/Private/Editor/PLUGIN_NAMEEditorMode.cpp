#include "PLUGIN_NAMEEditorMode.h"
#include "AdvancedPreviewSceneModule.h"
#include "IPLUGIN_NAMEPreviewScene.h"
#include "Editor/PLUGIN_NAMEEditor.h"
//#include "Editor/PLUGIN_NAMEDetails.h"
//#include "Editor/PLUGIN_NAMEViewport.h"
//#include "Editor/SPLUGIN_NAMEEditor.h"
#include "Editor/PLUGIN_NAMEEditorTabFactories.h"
#include "Editor/PLUGIN_NAMEEditorTabs.h"

#define LOCTEXT_NAMESPACE "PLUGIN_NAMEEditorMode"

namespace
{

	const FName AdvancedPreviewSceneSettingsID = FName(TEXT("AdvancedPreviewSceneSettingsID"));
	const FName PLUGIN_NAMEDetailsID = TEXT("PLUGIN_NAMEDetails");
	const FName PLUGIN_NAMEEditorID = TEXT("EasinessEditor");

	FName ViewportInstanceToTabName(int32 Index)
	{
		const FName ArrayIn[4] = { "Viewport", "Viewport1", "Viewport2", "Viewport3" };

		return ArrayIn[Index];
	}

}


FPLUGIN_NAMEEditorMode::FPLUGIN_NAMEEditorMode(TSharedRef<FPLUGIN_NAMEEditor> InHostingApp)
	: FApplicationMode(FPLUGIN_NAMEEditorTabs::PLUGIN_NAMEEditorMode)
{
	HostingAppPtr = InHostingApp;

	TabFactories.RegisterFactory(MakeShareable(new FAdvancedPreviewSceneSettingsTabSummoner(InHostingApp, InHostingApp->GetPreviewScene())));
	//TabFactories.RegisterFactory(MakeShareable(new FDetailsTabSummoner(InHostingApp)));
	//TabFactories.RegisterFactory(MakeShareable(new FEasinessEditorTabSummoner(InHostingApp)));
	TabFactories.RegisterFactory(MakeShareable(new FPreviewViewportSummoner(InHostingApp, 0)));
	TabFactories.RegisterFactory(MakeShareable(new FPreviewViewportSummoner(InHostingApp, 1)));
	TabFactories.RegisterFactory(MakeShareable(new FPreviewViewportSummoner(InHostingApp, 2)));
	TabFactories.RegisterFactory(MakeShareable(new FPreviewViewportSummoner(InHostingApp, 3)));

	TabLayout = FTabManager::NewLayout("Standalone_AnimationEditor_Layout_v1.0.0")
	->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewSplitter()
				->SetSizeCoefficient(0.9f)
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.2f)
					->AddTab(FPLUGIN_NAMEEditorTabs::ViewportInstanceToTabName(0), ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.6f)
				)
			)
			->Split
			(
				FTabManager::NewSplitter()
				->SetSizeCoefficient(0.9f)
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.2f)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.6f)
				)
			)
		);
}

/** FApplicationMode interface */

void FPLUGIN_NAMEEditorMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	TSharedPtr<FWorkflowCentricApplication> HostingApp = HostingAppPtr.Pin();
	HostingApp->RegisterTabSpawners(InTabManager.ToSharedRef());
	HostingApp->PushTabFactories(TabFactories);

	FApplicationMode::RegisterTabFactories(InTabManager);

}

void FPLUGIN_NAMEEditorMode::AddTabFactory(FCreateWorkflowTabFactory FactoryCreator) 
{
	if (FactoryCreator.IsBound())
	{
		TabFactories.RegisterFactory(FactoryCreator.Execute(HostingAppPtr.Pin()));		
	}
}

void FPLUGIN_NAMEEditorMode::RemoveTabFactory(FName TabFactoryID) 
{
	TabFactories.UnregisterFactory(TabFactoryID);
}

#undef LOCTEXT_NAMESPACE
