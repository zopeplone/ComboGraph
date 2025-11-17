// 


#include "Graph/EdComboGraphSchema.h"

#include "ComboGraphAsset.h"
#include "Edge/ComboGraphEdge.h"
#include "Graph/ComboGraphConnectionDrawingPolicy.h"
#include "Graph/EdComboGraph.h"
#include "Graph/EdComboGraphAnyNode.h"
#include "Graph/EdComboGraphEdge.h"
#include "Graph/EdComboGraphExecuteNode.h"
#include "Graph/EdComboGraphNode.h"
#include "Graph/EdComboGraphRootNode.h"
#include "Node/ComboGraphNode.h"

UEdGraphNode* FComboGraphAssetSchemaAction_NewNode::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin,
                                                                  const FVector2f& Location, bool bSelectNewNode)
{
	UEdComboGraphNode* NewEdNode = NewObject<UEdComboGraphNode>(ParentGraph,EdNodeClass);
	UEdComboGraph* ComboGraph = Cast<UEdComboGraph>(ParentGraph);
	const FScopedTransaction Transaction(NSLOCTEXT("ComboGraph","NewNode", "新建节点"));
	// 添加节点到图表中
	ParentGraph->Modify();
	if (FromPin != nullptr)
		FromPin->Modify();

	// Rename实际上是将NodeTemplate的Outer设置为ParentGraph
	NewEdNode->Rename(nullptr, ParentGraph);
	ParentGraph->AddNode(NewEdNode, true, bSelectNewNode);

	NewEdNode->CreateNewGuid();
	NewEdNode->PostPlacedNewNode();
	NewEdNode->AllocateDefaultPins();
	NewEdNode->AutowireNewNode(FromPin);

	NewEdNode->NodePosX = Location.X;
	NewEdNode->NodePosY = Location.Y;
	// NodeTemplate->GenericGraphNode->SetFlags(RF_Transactional);
	NewEdNode->SetFlags(RF_Transactional);

	// 持久化节点到GraphAsset
	UComboGraphNode* NodeAsset = NewObject<UComboGraphNode>(ComboGraph->GetComboGraphAsset(),NewEdNode->GetAssetNodeClass());
	
	NodeAsset->GraphAsset = ComboGraph->GetComboGraphAsset();
	NewEdNode->SetAssetNode(NodeAsset);

	return NewEdNode;
	
}

void FComboGraphAssetSchemaAction_NewNode::AddReferencedObjects(FReferenceCollector& Collector)
{
	FEdGraphSchemaAction::AddReferencedObjects(Collector);
}

UEdGraphNode* FComboGraphAssetSchemaAction_NewEdge::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin,
	const FVector2f& Location, bool bSelectNewNode)
{
	UEdComboGraphEdge* EdgeTemplate = NewObject<UEdComboGraphEdge>();
	UEdComboGraph* ComboGraph = Cast<UEdComboGraph>(ParentGraph);
	const FScopedTransaction Transaction(NSLOCTEXT("ComboGraph","NewNode", "新建节点"));
	// 添加边到图表中
	ParentGraph->Modify();
	if (FromPin != nullptr)
		FromPin->Modify();

	// Rename实际上是将NodeTemplate的Outer设置为ParentGraph
	EdgeTemplate->Rename(nullptr, ParentGraph);
	ParentGraph->AddNode(EdgeTemplate, true, bSelectNewNode);

	EdgeTemplate->CreateNewGuid();
	EdgeTemplate->PostPlacedNewNode();
	EdgeTemplate->AllocateDefaultPins();
	EdgeTemplate->AutowireNewNode(FromPin);

	EdgeTemplate->NodePosX = Location.X;
	EdgeTemplate->NodePosY = Location.Y;
	// NodeTemplate->GenericGraphNode->SetFlags(RF_Transactional);
	EdgeTemplate->SetFlags(RF_Transactional);

	// 持久化节点到GraphAsset
	auto EdgeAsset = NewObject<UComboGraphEdge>(ComboGraph->GetComboGraphAsset());
	EdgeAsset->GraphAsset = ComboGraph->GetComboGraphAsset();
	EdgeTemplate->SetAssetEdge(EdgeAsset);

	return EdgeTemplate;
}

void FComboGraphAssetSchemaAction_NewEdge::AddReferencedObjects(FReferenceCollector& Collector)
{
	FEdGraphSchemaAction::AddReferencedObjects(Collector);
}


void UEdComboGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	auto CreateNodeAction = [&ContextMenuBuilder](TSubclassOf<UEdComboGraphNode> SubClass,FText Description,FText CategoryDes = NSLOCTEXT("ComboGraph", "CreateNodeCategory", "创建新节点"))-> void
	{
		const TSharedPtr<FComboGraphAssetSchemaAction_NewNode> Action = MakeShareable(new FComboGraphAssetSchemaAction_NewNode);
		Action->EdNodeClass = SubClass;
		Action->UpdateSearchData(Description,FText(),CategoryDes, FText());
			
		ContextMenuBuilder.AddAction(Action);
	};
	
	CreateNodeAction(UEdComboGraphExecuteNode::StaticClass(),NSLOCTEXT("ComboGraph", "ExecuteNodeName", "招式节点"));
	CreateNodeAction(UEdComboGraphAnyNode::StaticClass(),NSLOCTEXT("ComboGraph", "AnyNodeName", "Any节点"));
	
	Super::GetGraphContextActions(ContextMenuBuilder);
}

EGraphType UEdComboGraphSchema::GetGraphType(const UEdGraph* TestEdGraph) const
{
	return GT_StateMachine;
}

const FPinConnectionResponse UEdComboGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	if (A->GetOwningNode() == B->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, NSLOCTEXT("ComboGraph","PinErrorSameNode", "不能连接到自身"));
	}
	UEdComboGraphNode* NodeA = Cast<UEdComboGraphNode>(A->GetOwningNode());
	UEdComboGraphNode* NodeB = Cast<UEdComboGraphNode>(B->GetOwningNode());
	if (!NodeA || !NodeB)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, NSLOCTEXT("ComboGraph","PinErrorInvalidNode", "无效的节点"));
	}
	if (!NodeB->CanAcceptConnectionFrom())
	{
		// 如果末端不允许添加InputPin，不进行连接
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, NSLOCTEXT("ComboGraph","PinErrorOutNode", "末端不接受连接"));
	}
	if (!NodeA->CanCreateConnectionTo())
	{
		// 如果起始端不允许添加OutputPin，不进行连接
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, NSLOCTEXT("ComboGraph","PinErrorInNode", "起始端不允许连接"));
	}
	// 如果A到B已经有连接了，拒绝重复连接
	for (UEdGraphPin *TestPin : NodeA->GetOutputPin()->LinkedTo)
	{
		UEdGraphNode* ChildEdge = TestPin->GetOwningNode();
		auto Edge = CastChecked<UEdComboGraphEdge>(ChildEdge);
		if (Edge->GetOutputNode() == NodeB)
		{
			return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, NSLOCTEXT("ComboGraph","PinErrorExistingConnection", "连接已存在"));
		}
	}
	
	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE_WITH_CONVERSION_NODE, NSLOCTEXT("ComboGraph","PinConnect", "Connect nodes with edge"));
}

bool UEdComboGraphSchema::TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const
{
	return Super::TryCreateConnection(A, B);
}

bool UEdComboGraphSchema::CreateAutomaticConversionNodeAndConnections(UEdGraphPin* A, UEdGraphPin* B) const
{
	UEdComboGraphNode* NodeA = Cast<UEdComboGraphNode>(A->GetOwningNode());
	UEdComboGraphNode* NodeB = Cast<UEdComboGraphNode>(B->GetOwningNode());

	// Are nodes and pins all valid?
	if (!NodeA || !NodeA->GetOutputPin() || !NodeB || !NodeB->GetInputPin())
		return false;
	
	UEdComboGraph* Graph = CastChecked<UEdComboGraph>(NodeA->GetGraph());

	FVector2f InitPos((NodeA->NodePosX + NodeB->NodePosX) / 2, (NodeA->NodePosY + NodeB->NodePosY) / 2);

	FComboGraphAssetSchemaAction_NewEdge Action;
	
	UEdComboGraphEdge* EdgeNode = Cast<UEdComboGraphEdge>(Action.PerformAction(NodeA->GetGraph(), nullptr, InitPos, false));
	
	// Always create connections from node A to B, don't allow adding in reverse
	EdgeNode->CreateConnections(NodeA, NodeB);

	return true;
}

class FConnectionDrawingPolicy* UEdComboGraphSchema::CreateConnectionDrawingPolicy(int32 InBackLayerID,
                                                                                   int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect,
                                                                                   class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const
{
	return new FComboGraphConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements, InGraphObj);
}

void UEdComboGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	UEdComboGraphNode* RootNode = NewObject<UEdComboGraphRootNode>();
	UEdComboGraph* ComboGraph = Cast<UEdComboGraph>(&Graph);
	// 添加节点到图表中
	ComboGraph->Modify();
	
	RootNode->Rename(nullptr, ComboGraph);
	ComboGraph->AddNode(RootNode, false, false);

	RootNode->CreateNewGuid();
	RootNode->PostPlacedNewNode();
	RootNode->AllocateDefaultPins();


	RootNode->NodePosX = 0;
	RootNode->NodePosY = 0;

	// 持久化节点到GraphAsset
	auto NodeAsset = NewObject<UComboGraphNode>(ComboGraph->GetComboGraphAsset());
	NodeAsset->GraphAsset = ComboGraph->GetComboGraphAsset();
	RootNode->SetAssetNode(NodeAsset);
}