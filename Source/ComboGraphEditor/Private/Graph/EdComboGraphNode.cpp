// 


#include "Graph/EdComboGraphNode.h"

#include "Graph/EdComboGraphEdge.h"
#include "Node/ComboGraphNode.h"

void UEdComboGraphNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, "MultipleNodes", FName(), TEXT("In"));
	CreatePin(EGPD_Output, "MultipleNodes", FName(), TEXT("Out"));
}

FText UEdComboGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return Super::GetNodeTitle(TitleType);
}

void UEdComboGraphNode::PrepareForCopying()
{
	Super::PrepareForCopying();
}

void UEdComboGraphNode::AutowireNewNode(UEdGraphPin* FromPin)
{
	Super::AutowireNewNode(FromPin);
}

TSharedPtr<SGraphNode> UEdComboGraphNode::CreateVisualWidget()
{
	return SNew(SComboGraphNode,this);
}

UComboGraphNode* UEdComboGraphNode::GetAssetNode()
{
	return AssetNode;
}

void UEdComboGraphNode::SetAssetNode(UComboGraphNode* InNode)
{
	AssetNode = InNode;
}

void UEdComboGraphNode::GetNodeContextMenuActions(class UToolMenu* Menu,
	class UGraphNodeContextMenuContext* Context) const
{
	Super::GetNodeContextMenuActions(Menu, Context);
}

UObject* UEdComboGraphNode::GetUObjectToEditProperty()
{
	return AssetNode;
}

void UEdComboGraphNode::SaveAsset()
{
	AssetNode->Id = NodeGuid;;
	AssetNode->Input.Empty();
	AssetNode->Output.Empty();
	for (UEdGraphPin* InputPin : GetInputPin()->LinkedTo)
	{
		UEdComboGraphEdge* Edge = CastChecked<UEdComboGraphEdge>(InputPin->GetOwningNode());
		AssetNode->Input.Add(Edge->NodeGuid, Edge->EdgeAsset);
	}
	for (UEdGraphPin* OutputPin : GetOutputPin()->LinkedTo)
	{
		UEdComboGraphEdge* Edge = CastChecked<UEdComboGraphEdge>(OutputPin->GetOwningNode());
		AssetNode->Output.Add(Edge->NodeGuid, Edge->EdgeAsset);
	}
}

TSubclassOf<UComboGraphNode> UEdComboGraphNode::GetAssetNodeClass() const
{
	return UComboGraphNode::StaticClass();
}

void UEdComboGraphNode::PostEditUndo()
{
	Super::PostEditUndo();
}

