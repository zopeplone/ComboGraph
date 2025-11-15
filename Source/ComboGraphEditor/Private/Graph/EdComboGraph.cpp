// 


#include "Graph/EdComboGraph.h"

#include "ComboGraphAsset.h"
#include "Graph/EdComboGraphAnyNode.h"
#include "Graph/EdComboGraphEdge.h"
#include "Graph/EdComboGraphRootNode.h"
#include "Graph/EdComboGraphSchema.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Node/ComboGraphNode.h"

void UEdComboGraph::CreateGraph(UComboGraphAsset* InAsset)
{
	UEdComboGraph* NewGraph = CastChecked<UEdComboGraph>(FBlueprintEditorUtils::CreateNewGraph(InAsset, NAME_None, StaticClass(), UEdComboGraphSchema::StaticClass()));
	NewGraph->bAllowDeletion = false;


	InAsset->EdGraph = NewGraph;
	InAsset->EdGraph->GetSchema()->CreateDefaultNodesForGraph(*InAsset->EdGraph);
}

UComboGraphAsset* UEdComboGraph::GetComboGraphAsset() const
{
	return GetTypedOuter<UComboGraphAsset>();
}

void UEdComboGraph::PostEditUndo()
{
	Super::PostEditUndo();
	NotifyGraphChanged();
}

void UEdComboGraph::SaveAsset()
{
	auto* ComboGraphAsset = GetComboGraphAsset();
	
	TArray<UEdComboGraphRootNode*> RootNodes;
	GetNodesOfClass(RootNodes);
	check(RootNodes.Num() > 0);
	auto* RootNode = RootNodes[0];
	
	TArray<UEdComboGraphNode*> AllNodes;
	GetNodesOfClass(AllNodes);
	
	TArray<UEdComboGraphEdge*> AllEdges;
	GetNodesOfClass(AllEdges);
	
	TArray<UEdComboGraphAnyNode*> AnyNodes;
	GetNodesOfClass(AnyNodes);
	
	ComboGraphAsset->Nodes.Empty();
	ComboGraphAsset->Edges.Empty();
	ComboGraphAsset->AnyNodeIds.Empty();
	// 先在图Asset中保存所有Nodes,Edges 及其id
	for (UEdComboGraphNode* Node : AllNodes)
	{
		ComboGraphAsset->Nodes.Add(Node->NodeGuid, Node->GetAssetNode());
		Node->SaveAsset();
	}
	for (UEdComboGraphEdge* Edge : AllEdges)
	{
		ComboGraphAsset->Edges.Add(Edge->NodeGuid, Edge->GetAssetEdge());
		Edge->SaveAsset();
	}
	// 再填充RootNodeId和AnyNodeIds
	ComboGraphAsset->RootNodeId = RootNode->NodeGuid;
	for (UEdComboGraphAnyNode* AnyNode : AnyNodes)
	{
		ComboGraphAsset->AnyNodeIds.Add(AnyNode->NodeGuid);
	}
}
