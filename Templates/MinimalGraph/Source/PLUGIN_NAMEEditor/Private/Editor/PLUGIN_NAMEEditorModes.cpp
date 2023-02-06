
#include "PLUGIN_NAMEEditorModes.h"
#include "Editor/PLUGIN_NAMEEditorTabs.h"
#include "Editor/PLUGIN_NAMEEditorTabFactories.h"
#include "Editor/PLUGIN_NAMEEditor.h"

FPLUGIN_NAMEEditorModes::FPLUGIN_NAMEEditorModes(TSharedPtr<FPLUGIN_NAMEEditor> InEditor)
    : FApplicationMode(FPLUGIN_NAMEEditorTabs::PLUGIN_NAMEMode)
{
	WeakEditor = InEditor;

	// clang-format off

	TabLayout = FTabManager::NewLayout("Standalone_PLUGIN_NAME_Layout_v0")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.7f)
					->AddTab(FPLUGIN_NAMEEditorTabs::GraphEditorID, ETabState::ClosedTab)
				)
				->Split
				(
					FTabManager::NewSplitter()
					->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.3f)
					->Split
					(
						FTabManager::NewStack()->SetSizeCoefficient(0.6f)
						//->AddTab(FPLUGIN_NAMEEditorTabs::GraphDetailsID, ETabState::OpenedTab)
						//->AddTab(FPLUGIN_NAMEEditorTabs::SearchID, ETabState::ClosedTab)
					)
					->Split
					(
						FTabManager::NewStack()->SetSizeCoefficient(0.4f)
						//->AddTab(FPLUGIN_NAMEEditorTabs::BlackboardID, ETabState::OpenedTab)
					)
				)
			)
		);

	// clang-format on
}

void FPLUGIN_NAMEEditorModes::RegisterTabFactories(
    TSharedPtr<class FTabManager> InTabManager)
{
	check(WeakEditor.IsValid());
	TSharedPtr<FPLUGIN_NAMEEditor> EditorPtr = WeakEditor.Pin();

	EditorPtr->PushTabFactories(PLUGIN_NAMEEditorTabFactories);

	FApplicationMode::RegisterTabFactories(InTabManager);
}

void FPLUGIN_NAMEEditorModes::PreDeactivateMode() {}

void FPLUGIN_NAMEEditorModes::PostActivateMode() 
{
	// Reopen any documents that were open when the blueprint was last saved
	check(WeakEditor.IsValid());
	TSharedPtr<FPLUGIN_NAMEEditor> EditorPtr = WeakEditor.Pin();
	EditorPtr->RestoreGraphAsset();
}
