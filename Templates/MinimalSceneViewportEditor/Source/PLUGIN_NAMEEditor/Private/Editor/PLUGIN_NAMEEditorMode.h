#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

class FPLUGIN_NAMEEditor;

class FPLUGIN_NAMEEditorMode
	: public FApplicationMode
{
public:
	FPLUGIN_NAMEEditorMode(TSharedRef<FPLUGIN_NAMEEditor> InHostingApp);

	/** FApplicationMode interface */
	virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;

protected:
	virtual void AddTabFactory(FCreateWorkflowTabFactory FactoryCreator) override;
	virtual void RemoveTabFactory(FName TabFactoryID) override;
private:
	/** The hosting app */
	TWeakPtr<FPLUGIN_NAMEEditor> HostingAppPtr;

	/** The tab factories we support */
	FWorkflowAllowedTabSet TabFactories;
};
