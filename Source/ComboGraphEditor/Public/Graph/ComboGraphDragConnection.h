// 

#pragma once

#include "CoreMinimal.h"
#include "GraphEditorDragDropAction.h"
#include "SGraphPin.h"

struct FGraphPinHandle;
/**
 * 
 */
class COMBOGRAPHEDITOR_API FComboGraphDragConnection : public FGraphEditorDragDropAction
{
public:

	static TSharedRef<FComboGraphDragConnection> New(const TSharedRef<SGraphPanel>& GraphPanelIn, const FGraphPinHandle& DraggedPinIn);
	virtual void OnDragged(const class FDragDropEvent& DragDropEvent) override;
	virtual void OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent) override;
	virtual FReply DroppedOnPin(FVector2D ScreenPosition, FVector2D GraphPosition) override;
	virtual FReply DroppedOnPanel(const TSharedRef<SWidget>& Panel, FVector2D ScreenPosition, FVector2D GraphPosition, UEdGraph& Graph) override;
protected:
	// Constructor:确保在new之后调用Construct()
	FComboGraphDragConnection(const TSharedRef<SGraphPanel>& GraphPanel, const FGraphPinHandle& DraggedPin);
	TSharedPtr<SGraphPanel> GraphPanel;
	FGraphPinHandle DraggingPin;

	/** Offset information for the decorator widget */
	FVector2D DecoratorAdjust;

};
