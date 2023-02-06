

#pragma once

#include "SGraphNode.h"

class UPLUGIN_NAMEGraphNode;

class SGraphNode_PLUGIN_NAME : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SGraphNode_PLUGIN_NAME){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UPLUGIN_NAMEGraphNode* InNode);

};