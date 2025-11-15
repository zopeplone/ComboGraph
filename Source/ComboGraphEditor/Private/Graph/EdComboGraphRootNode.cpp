// 


#include "Graph/EdComboGraphRootNode.h"

#include "Graph/Widgets/SComboGraphRootNode.h"
#include "Node/ComboGraphNode.h"

TSharedPtr<SGraphNode> UEdComboGraphRootNode::CreateVisualWidget()
{
	return SNew(SComboGraphRootNode, this);
}

bool UEdComboGraphRootNode::CanUserDeleteNode() const
{
	return false;
}

