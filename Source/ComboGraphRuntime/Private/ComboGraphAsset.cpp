// 


#include "ComboGraphAsset.h"

TObjectPtr<UComboGraphNode> UComboGraphAsset::GetNode(FGuid Id) const
{
	return *Nodes.Find(Id);
}

TObjectPtr<UComboGraphEdge> UComboGraphAsset::GetEdge(FGuid Id) const
{
	return *Edges.Find(Id);
}
