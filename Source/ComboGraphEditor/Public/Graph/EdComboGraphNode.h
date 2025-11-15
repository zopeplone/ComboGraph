// 

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "Interface/ComboGraphPropertyEdit.h"
#include "Widgets/SComboGraphNode.h"
#include "EdComboGraphNode.generated.h"

class UComboGraphNode;
/**
 * 
 */
UCLASS()
class COMBOGRAPHEDITOR_API UEdComboGraphNode : public UEdGraphNode,public IComboGraphPropertyEdit
{
	GENERATED_BODY()
	friend SComboGraphNode;
public:
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PrepareForCopying() override;
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
	// virtual FLinearColor GetBackgroundColor() const;
	// virtual UEdGraphPin* GetInputPin() const;
	// virtual UEdGraphPin* GetOutputPin() const;
	UComboGraphNode* GetAssetNode();
	void SetAssetNode(UComboGraphNode* InNode);
	virtual UEdGraphPin* GetInputPin() const { return Pins[0]; }
	virtual UEdGraphPin* GetOutputPin() const { return Pins[1]; }
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

	// IComboGraphPropertyEdit
	virtual UObject* GetUObjectToEditProperty() override;
	virtual void SaveAsset();

	virtual TSubclassOf<UComboGraphNode> GetAssetNodeClass() const;
	virtual bool CanAcceptConnectionFrom() const { return true; }
	virtual bool CanCreateConnectionTo() const { return true; }
	
#if WITH_EDITOR
	virtual void PostEditUndo() override;
#endif

protected:
#if WITH_EDITORONLY_DATA
	UPROPERTY()
	TObjectPtr<UComboGraphNode> AssetNode;
	SComboGraphNode* SEdNode;
#endif
};
