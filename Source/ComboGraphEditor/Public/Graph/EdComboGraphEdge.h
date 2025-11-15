// 

#pragma once

#include "CoreMinimal.h"


#include "EdGraph/EdGraphNode.h"
#include "Interface/ComboGraphPropertyEdit.h"
#include "EdComboGraphEdge.generated.h"

class UEdComboGraphNode;
class UComboGraphEdge;
/**
 * 
 */
UCLASS()
class COMBOGRAPHEDITOR_API UEdComboGraphEdge : public UEdGraphNode,public IComboGraphPropertyEdit
{
	GENERATED_BODY()
public:
	UEdComboGraphEdge();

	UPROPERTY()
	UEdGraph* Graph;

	UPROPERTY()
	UComboGraphEdge* EdgeAsset;

	UComboGraphEdge* GetAssetEdge() const;

	void SetAssetEdge(UComboGraphEdge* InEdge);

	virtual void AllocateDefaultPins() override;

	// virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;

	// virtual void PrepareForCopying() override;
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
	virtual UEdGraphPin* GetInputPin() const { return Pins[0]; }
	virtual UEdGraphPin* GetOutputPin() const { return Pins[1]; }

	void CreateConnections(UEdComboGraphNode* Start, UEdComboGraphNode* End);
	// // IComboGraphPropertyEdit
	virtual UObject* GetUObjectToEditProperty() override;
	virtual void SaveAsset();

	UEdComboGraphNode* GetInputNode();
	UEdComboGraphNode* GetOutputNode();
};
