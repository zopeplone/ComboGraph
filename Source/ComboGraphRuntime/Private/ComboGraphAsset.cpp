// 


#include "ComboGraphAsset.h"

UComboGraphNode* UComboGraphAsset::GetNode(FGuid Id) const
{
	if (!Nodes.Contains(Id)) return nullptr;
	return *Nodes.Find(Id);
}

UComboGraphEdge* UComboGraphAsset::GetEdge(FGuid Id) const
{
	if (!Edges.Contains(Id)) return nullptr;
	return *Edges.Find(Id);
}
