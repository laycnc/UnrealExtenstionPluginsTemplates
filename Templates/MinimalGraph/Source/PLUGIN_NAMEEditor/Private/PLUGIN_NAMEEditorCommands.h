

#pragma once

#include "Framework/Commands/Commands.h"
#include "Templates/SharedPointer.h"


class FPLUGIN_NAMEEditorCommands : public TCommands<FPLUGIN_NAMEEditorCommands>
{
public:
	FPLUGIN_NAMEEditorCommands();

	/** Initialize commands */
	virtual void RegisterCommands() override;
};