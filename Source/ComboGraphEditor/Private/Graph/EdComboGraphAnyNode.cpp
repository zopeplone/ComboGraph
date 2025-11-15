// 


#include "Graph/EdComboGraphAnyNode.h"

#include "Graph/Widgets/SComboGraphAnyNode.h"
#include "Node/ComboGraphAnyNode.h"

TSharedPtr<SGraphNode> UEdComboGraphAnyNode::CreateVisualWidget()
{
	return SNew(SComboGraphAnyNode,this);
}

UObject* UEdComboGraphAnyNode::GetUObjectToEditProperty()
{
	return nullptr;
}

TSubclassOf<UComboGraphNode> UEdComboGraphAnyNode::GetAssetNodeClass() const
{
	return UComboGraphAnyNode::StaticClass();
}
