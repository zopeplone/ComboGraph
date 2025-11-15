// 


#include "Graph/Widgets/SComboGraphEdge.h"

#include "ConnectionDrawingPolicy.h"
#include "Graph/EdComboGraphEdge.h"
#include "Graph/EdComboGraphNode.h"

void SComboGraphEdge::Construct(const FArguments& InArgs, UEdComboGraphEdge* InEdge)
{
	this->GraphNode = InEdge;
	this->UpdateGraphNode();
}

void SComboGraphEdge::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();

	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	// TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);

	this->ContentScale.Bind( this, &SGraphNode::GetContentScale );
	this->GetOrAddSlot( ENodeZone::Center )
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			[
				SNew(SImage)
				.Image(FAppStyle::GetBrush("Graph.TransitionNode.ColorSpill"))
				.ColorAndOpacity(FLinearColor(0.9f, 0.9f, 0.9f, 1.0f))
			]
			+ SOverlay::Slot()
			[
				SNew(SImage)
				.Image(FAppStyle::GetBrush("Graph.TransitionNode.Icon"))
				.Visibility(EVisibility::Visible)
			]
			// NodeTitle
			// + SOverlay::Slot()
			// .Padding(FMargin(4.0f, 4.0f, 4.0f, 4.0f))
			// [
			// 	SNew(SVerticalBox)
			// 	+ SVerticalBox::Slot()
			// 	.HAlign(HAlign_Center)
			// 	.AutoHeight()
			// 	[
			// 		SAssignNew(InlineEditableText, SInlineEditableTextBlock)
			// 		.ColorAndOpacity(FLinearColor::Black)
			// 		.Visibility(this, &SEdNode_GenericGraphEdge::GetEdgeTitleVisbility)
			// 		.Font(FCoreStyle::GetDefaultFontStyle("Regular", 12))
			// 		.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
			// 		.OnTextCommitted(this, &SEdNode_GenericGraphEdge::OnNameTextCommited)
			// 	]
			// 	+ SVerticalBox::Slot()
			// 	.AutoHeight()
			// 	[
			// 		NodeTitle.ToSharedRef()
			// 	]
			// ]
		];
}

void SComboGraphEdge::PerformSecondPassLayout(const TMap<UObject*, TSharedRef<SNode>>& InNodeToWidgetLookup) const
{
	UEdComboGraphEdge* EdgeNode = CastChecked<UEdComboGraphEdge>(GraphNode);
	
	UEdComboGraphNode* Start = EdgeNode->GetInputNode();
	UEdComboGraphNode* End = EdgeNode->GetOutputNode();
	
	if (Start == nullptr || End == nullptr)
	{
		return;
	}
	const TSharedRef<SNode>* pFromWidget = InNodeToWidgetLookup.Find(Start);
	const TSharedRef<SNode>* pToWidget = InNodeToWidgetLookup.Find(End);
	if (pFromWidget == nullptr || pToWidget == nullptr)
	{
		return;
	}
	const TSharedRef<SNode>& FromWidget = *pFromWidget;
	const TSharedRef<SNode>& ToWidget = *pToWidget;

	FGeometry StartGeom = FGeometry(FVector2D(Start->NodePosX, Start->NodePosY), FVector2D::ZeroVector, FromWidget->GetDesiredSize(), 1.0f);
	FGeometry EndGeom = FGeometry(FVector2D(End->NodePosX, End->NodePosY), FVector2D::ZeroVector, ToWidget->GetDesiredSize(), 1.0f);
	
	// Get a reasonable seed point (halfway between the boxes)
	const FVector2D StartCenter = FGeometryHelper::CenterOf(StartGeom);
	const FVector2D EndCenter = FGeometryHelper::CenterOf(EndGeom);
	const FVector2D SeedPoint = (StartCenter + EndCenter) * 0.5f;

	// Find the (approximate) closest points between the two boxes
	const FVector2D StartAnchorPoint = FGeometryHelper::FindClosestPointOnGeom(StartGeom, SeedPoint);
	const FVector2D EndAnchorPoint = FGeometryHelper::FindClosestPointOnGeom(EndGeom, SeedPoint);

	// Position ourselves halfway along the connecting line between the nodes, elevated away perpendicular to the direction of the line
	const float Height = 30.0f;

	const FVector2D DesiredNodeSize = GetDesiredSize();

	FVector2D DeltaPos(EndAnchorPoint - StartAnchorPoint);

	if (DeltaPos.IsNearlyZero())
	{
		DeltaPos = FVector2D(10.0f, 0.0f);
	}

	const FVector2D Normal = FVector2D(DeltaPos.Y, -DeltaPos.X).GetSafeNormal();

	const FVector2D NewCenter = StartAnchorPoint + (0.5f * DeltaPos) + (Height * Normal);

	FVector2D DeltaNormal = DeltaPos.GetSafeNormal();
	
	// Calculate node offset in the case of multiple transitions between the same two nodes
	// MultiNodeOffset: the offset where 0 is the centre of the transition, -1 is 1 <size of node>
	// towards the PrevStateNode and +1 is 1 <size of node> towards the NextStateNode.

	constexpr float MaxNodes = 1;
	constexpr float NodeIndex = 0;
	
	const float MutliNodeSpace = 0.2f; // Space between multiple transition nodes (in units of <size of node> )
	const float MultiNodeStep = (1.f + MutliNodeSpace); //Step between node centres (Size of node + size of node spacer)

	const float MultiNodeStart = -((MaxNodes - 1) * MultiNodeStep) / 2.f;
	const float MultiNodeOffset = MultiNodeStart + (NodeIndex * MultiNodeStep);

	// Now we need to adjust the new center by the node size, zoom factor and multi node offset
	const FVector2D NewCorner = NewCenter - (0.5f * DesiredNodeSize) + (DeltaNormal * MultiNodeOffset * DesiredNodeSize.Size());

	GraphNode->NodePosX = NewCorner.X;
	GraphNode->NodePosY = NewCorner.Y;
}

bool SComboGraphEdge::RequiresSecondPassLayout() const
{
	return true;
}
