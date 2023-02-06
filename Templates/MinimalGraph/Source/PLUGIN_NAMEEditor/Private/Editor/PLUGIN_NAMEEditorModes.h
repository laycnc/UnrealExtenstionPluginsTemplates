

#pragma once

#include "Templates/SharedPointer.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

class FPLUGIN_NAMEEditor;

/** Application mode for main PLUGIN_NAME editing mode */
class FPLUGIN_NAMEEditorModes : public FApplicationMode
{
public:
	FPLUGIN_NAMEEditorModes(TSharedPtr<FPLUGIN_NAMEEditor> InEditor);

	virtual void RegisterTabFactories(TSharedPtr<class FTabManager> InTabManager) override;
	virtual void PreDeactivateMode() override;
	virtual void PostActivateMode() override;

protected:
	TWeakPtr<FPLUGIN_NAMEEditor> WeakEditor;

	// Set of spawnable tabs in behavior tree editing mode
	FWorkflowAllowedTabSet PLUGIN_NAMEEditorTabFactories;
};