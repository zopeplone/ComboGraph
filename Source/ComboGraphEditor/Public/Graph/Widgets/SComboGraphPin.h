#pragma once
#include "SGraphPin.h"
#include "Graph/ComboGraphDragConnection.h"

class SComboGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SComboGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InPin)
	{

		bShowLabel = true;

		GraphPinObj = InPin;
		check(GraphPinObj != nullptr);

		const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
		check(Schema);
		
		SetCursor(EMouseCursor::Crosshairs);
		SBorder::Construct(SBorder::FArguments()
			// .BorderImage(this, &SComboGraphPin::GetPinBorder)
			.BorderBackgroundColor(FLinearColor::Transparent)
			.OnMouseButtonDown(this, &SComboGraphPin::OnPinMouseDown)
			// .Cursor(this, &SComboGraphPin::GetPinCursor)
			.Padding(FMargin(5.0f))
		);
	}

protected:
	virtual FSlateColor GetPinColor() const override
	{
		return FLinearColor(0.02f, 0.02f, 0.02f);
	}

	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override
	{
		return SNew(STextBlock);
	}

	const FSlateBrush* GetPinBorder() const
	{
		return FAppStyle::GetBrush(TEXT("Graph.StateNode.Body"));
	}

	virtual TSharedRef<FDragDropOperation> SpawnPinDragEvent(const TSharedRef<class SGraphPanel>& InGraphPanel, const TArray< TSharedRef<SGraphPin> >& InStartingPins) override
	{
		// FGenericGraphDragConnection::FDraggedPinTable PinHandles;
		// PinHandles.Reserve(InStartingPins.Num());
		// // since the graph can be refreshed and pins can be reconstructed/replaced 
		// // behind the scenes, the DragDropOperation holds onto FGraphPinHandles 
		// // instead of direct widgets/graph-pins
		// for (const TSharedRef<SGraphPin>& PinWidget : InStartingPins)
		// {
		// 	PinHandles.Add(PinWidget->GetPinObj());
		// }
		//
		// return FGenericGraphDragConnection::New(InGraphPanel, PinHandles);
		UEdGraphPin* PinHandle = nullptr;
		if (InStartingPins.Num() > 0) PinHandle = InStartingPins[0]->GetPinObj();
		return FComboGraphDragConnection::New(InGraphPanel,PinHandle);
	}

};
