// 


#include "Graph/ComboGraphDragConnection.h"

#include "SGraphPanel.h"
#include "SGraphPin.h"


FComboGraphDragConnection::FComboGraphDragConnection(const TSharedRef<SGraphPanel>& GraphPanelIn, const FGraphPinHandle& DraggedPinIn)
: GraphPanel(GraphPanelIn)
	, DraggingPin(DraggedPinIn)
	, DecoratorAdjust(FSlateApplication::Get().GetCursorSize())
{
	if (const UEdGraphPin* PinObj = DraggingPin.GetPinObj(*GraphPanel.Get()))
	{
		if (PinObj && PinObj->Direction == EGPD_Input)
		{
			DecoratorAdjust *= FVector2D(-1.0f, 1.0f);
		}
		GraphPanelIn->OnBeginMakingConnection(DraggingPin);
	}
}



TSharedRef<FComboGraphDragConnection> FComboGraphDragConnection::New(const TSharedRef<SGraphPanel>& GraphPanel, const FGraphPinHandle& DraggedPin)
{
	TSharedRef<FComboGraphDragConnection> Operation = MakeShareable(new FComboGraphDragConnection(GraphPanel,DraggedPin));
	Operation->Construct();

	return Operation;
}

void FComboGraphDragConnection::OnDragged(const class FDragDropEvent& DragDropEvent)
{
	FVector2D TargetPosition = DragDropEvent.GetScreenSpacePosition();

	// Reposition the info window wrt to the drag
	CursorDecoratorWindow->MoveWindowTo(DragDropEvent.GetScreenSpacePosition() + DecoratorAdjust);
	// Request the active panel to scroll if required
	GraphPanel->RequestDeferredPan(TargetPosition);
}

void FComboGraphDragConnection::OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent)
{
	GraphPanel->OnStopMakingConnection();
	FGraphEditorDragDropAction::OnDrop(bDropWasHandled, MouseEvent);
}

FReply FComboGraphDragConnection::DroppedOnPin(const FVector2f& ScreenPosition, const FVector2f& GraphPosition)
{
	const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "GraphEd_CreateConnection", "Create Pin Link"));
	UEdGraphPin* PinA = DraggingPin.GetPinObj(*GraphPanel);
	UEdGraphPin* PinB = GetHoveredPin();
	
	
	if (!PinA || !PinB)
	{
		return FReply::Unhandled();
	}
	UEdGraph* MyGraphObj = PinA->GetOwningNode()->GetGraph();

	if (MyGraphObj->GetSchema()->TryCreateConnection(PinA, PinB))
	{
		if (!PinA->IsPendingKill())
		{
			PinA->GetOwningNode()->NodeConnectionListChanged();
		}
		if (!PinB->IsPendingKill())
		{
			PinB->GetOwningNode()->NodeConnectionListChanged();
		}
	}
	else return FReply::Unhandled();
	
	return FReply::Handled();
}

FReply FComboGraphDragConnection::DroppedOnPanel(const TSharedRef< SWidget >& Panel, const FVector2f& ScreenPosition, const FVector2f& GraphPosition, UEdGraph& Graph)
{
	TArray<UEdGraphPin*> PinObjects {DraggingPin.GetPinObj(*GraphPanel)};
	// Create a context menu
	TSharedPtr<SWidget> WidgetToFocus = GraphPanel->SummonContextMenu(ScreenPosition, GraphPosition, nullptr, nullptr, PinObjects);

	// Give the context menu focus
	return (WidgetToFocus.IsValid())
		? FReply::Handled().SetUserFocus(WidgetToFocus.ToSharedRef(), EFocusCause::SetDirectly)
		: FReply::Handled();
}
