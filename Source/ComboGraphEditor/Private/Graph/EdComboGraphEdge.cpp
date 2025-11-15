// 


#include "Graph/EdComboGraphEdge.h"

#include "Edge/ComboGraphEdge.h"
#include "Graph/EdComboGraphNode.h"
#include "Graph/Widgets/SComboGraphEdge.h"
#include "Kismet2/BlueprintEditorUtils.h"

UEdComboGraphEdge::UEdComboGraphEdge()
{
}

UComboGraphEdge* UEdComboGraphEdge::GetAssetEdge() const
{
	return EdgeAsset;
}

void UEdComboGraphEdge::SetAssetEdge(UComboGraphEdge* InEdge)
{
	EdgeAsset = InEdge;
}

void UEdComboGraphEdge::AllocateDefaultPins()
{
	UEdGraphPin* Inputs = CreatePin(EGPD_Input, TEXT("Edge"), FName(), TEXT("In"));
	Inputs->bHidden = true;
	UEdGraphPin* Outputs = CreatePin(EGPD_Output, TEXT("Edge"), FName(), TEXT("Out"));
	Outputs->bHidden = true;
}

void UEdComboGraphEdge::PinConnectionListChanged(UEdGraphPin* Pin)
{
	if (Pin->LinkedTo.Num() == 0)
	{
		// Commit suicide; transitions must always have an input and output connection
		Modify();

		// Our parent graph will have our graph in SubGraphs so needs to be modified to record that.
		if (UEdGraph* ParentGraph = GetGraph())
		{
			ParentGraph->Modify();
		}

		DestroyNode();
	}
}

TSharedPtr<SGraphNode> UEdComboGraphEdge::CreateVisualWidget()
{
	return SNew(SComboGraphEdge, this);
}

void UEdComboGraphEdge::CreateConnections(UEdComboGraphNode* Start, UEdComboGraphNode* End)
{
	Pins[0]->Modify();
	Pins[0]->LinkedTo.Empty();

	Start->GetOutputPin()->Modify();
	Pins[0]->MakeLinkTo(Start->GetOutputPin());

	// This to next
	Pins[1]->Modify();
	Pins[1]->LinkedTo.Empty();

	End->GetInputPin()->Modify();
	Pins[1]->MakeLinkTo(End->GetInputPin());
}

UObject* UEdComboGraphEdge::GetUObjectToEditProperty()
{
	return EdgeAsset;
}

void UEdComboGraphEdge::SaveAsset()
{
	EdgeAsset->Id = NodeGuid;
	EdgeAsset->StartNodeId = GetInputNode()->NodeGuid;
	EdgeAsset->EndNodeId = GetOutputNode()->NodeGuid;
}

UEdComboGraphNode* UEdComboGraphEdge::GetInputNode()
{
	if (Pins[0]->LinkedTo.Num() > 0)
	{
		return Cast<UEdComboGraphNode>(Pins[0]->LinkedTo[0]->GetOwningNode());
	}
	else
	{
		return nullptr;
	}
}

UEdComboGraphNode* UEdComboGraphEdge::GetOutputNode()
{
	if (Pins[1]->LinkedTo.Num() > 0)
	{
		return Cast<UEdComboGraphNode>(Pins[1]->LinkedTo[0]->GetOwningNode());
	}
	else
	{
		return nullptr;
	}
}

