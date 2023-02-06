
#include "Editor/SGraphNode_PLUGIN_NAME.h"
#include "GenericPlatform/ICursor.h"
#include "Misc/Optional.h"

void SGraphNode_PLUGIN_NAME::Construct(const FArguments& InArgs, UPLUGIN_NAMEGraphNode* InNode)
{
	GraphNode = InNode;

	SetCursor( EMouseCursor::CardinalCross );

	UpdateGraphNode();
}
