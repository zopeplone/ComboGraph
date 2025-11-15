// 


#include "Node/ComboGraphNode.h"

#include "ComboGraphAsset.h"

UComboGraphNode::UComboGraphNode()
{
}

UComboGraphNode::~UComboGraphNode()
{
}

UComboGraphEdge* UComboGraphNode::GetOutputEdge(FGuid EdgeId) const
{
	return Output[EdgeId];
}

bool UComboGraphNode::IsLeafNode() const
{
	return Output.IsEmpty();
}

UComboGraphAsset* UComboGraphNode::GetGraph() const
{
	return GraphAsset;
}

FText UComboGraphNode::GetNodeTitle() const
{
	return NodeTitle;
}

void UComboGraphNode::SetNodeTitle(const FText& NewTitle)
{
	NodeTitle = NewTitle;
}

void UComboGraphNode::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	UObject::PostEditChangeProperty(PropertyChangedEvent);
	GraphAsset->GetEdGraph()->NotifyGraphChanged();
}
