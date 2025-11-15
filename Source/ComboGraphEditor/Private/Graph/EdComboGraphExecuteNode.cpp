// 


#include "Graph/EdComboGraphExecuteNode.h"

#include "Graph/Widgets/SComboGraphExecuteNode.h"
#include "Node/ComboGraphExecuteNode.h"

TSharedPtr<SGraphNode> UEdComboGraphExecuteNode::CreateVisualWidget()
{
	return SNew(SComboGraphExecuteNode,this);
}

TSubclassOf<UComboGraphNode> UEdComboGraphExecuteNode::GetAssetNodeClass() const
{
	return UComboGraphExecuteNode::StaticClass();
}
