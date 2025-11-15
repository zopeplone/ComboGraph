// 


#include "Graph/Widgets/SComboGraphNode.h"

#include "GraphEditorSettings.h"
#include "SCommentBubble.h"
#include "SGraphPin.h"
#include "Graph/EdComboGraphNode.h"
#include "Graph/Widgets/SComboGraphPin.h"
#include "Node/ComboGraphNode.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"
#include "AssetThumbnail.h"
#include "ThumbnailRendering/ThumbnailManager.h"


void SComboGraphNode::Construct(const FArguments& InArgs, UEdComboGraphNode* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
	InNode->SEdNode = this;
	SetCursor(EMouseCursor::CardinalCross);
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SComboGraphNode::UpdateGraphNode()
{
	
}

void SComboGraphNode::CreatePinWidgets()
{
	// SGraphNode::CreatePinWidgets();
	UEdComboGraphNode* EdComboGraphNode = CastChecked<UEdComboGraphNode>(GraphNode);

	for (int32 PinIdx = 0; PinIdx < EdComboGraphNode->Pins.Num(); PinIdx++)
	{
		UEdGraphPin* MyPin = EdComboGraphNode->Pins[PinIdx];
		if (!MyPin->bHidden)
		{
			TSharedPtr<SComboGraphPin> NewPin = SNew(SComboGraphPin, MyPin);

			AddPin(NewPin.ToSharedRef());
		}
	}
}

void SComboGraphNode::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	// SGraphNode::AddPin(PinToAdd);
	PinToAdd->SetOwner(SharedThis(this));

	const UEdGraphPin* PinObj = PinToAdd->GetPinObj();
	const bool bAdvancedParameter = PinObj && PinObj->bAdvancedView;
	if (bAdvancedParameter)
	{
		PinToAdd->SetVisibility(TAttribute<EVisibility>(PinToAdd, &SGraphPin::IsPinVisibleAsAdvanced));
	}

	TSharedPtr<SVerticalBox> PinBox;
	if (PinToAdd->GetDirection() == EEdGraphPinDirection::EGPD_Input)
	{
		PinBox = LeftNodeBox;
		InputPins.Add(PinToAdd);
	}
	else // Direction == EEdGraphPinDirection::EGPD_Output
	{
		PinBox = RightNodeBox;
		OutputPins.Add(PinToAdd);
	}

	if (PinBox)
	{
		PinBox->AddSlot()
		      .HAlign(HAlign_Fill)
		      .VAlign(VAlign_Fill)
		      .FillHeight(1.0f)
			//.Padding(6.0f, 0.0f)
			[
				PinToAdd
			];
	}
}

bool SComboGraphNode::IsNameReadOnly() const
{
	return SGraphNode::IsNameReadOnly();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
