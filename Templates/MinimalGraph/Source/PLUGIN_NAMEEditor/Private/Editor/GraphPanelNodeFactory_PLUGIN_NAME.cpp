

#include "Editor/GraphPanelNodeFactory_PLUGIN_NAME.h"
#include "Editor/SGraphNode_PLUGIN_NAME.h"
#include "PLUGIN_NAMEGraphNode.h"

TSharedPtr<class SGraphNode> FGraphPanelNodeFactory_PLUGIN_NAME::CreateNode(UEdGraphNode* Node) const
{
	if (UPLUGIN_NAMEGraphNode* FoolNode = Cast<UPLUGIN_NAMEGraphNode>(Node))
	{
		return SNew(SGraphNode_PLUGIN_NAME, FoolNode);
	}

	return nullptr;
}

