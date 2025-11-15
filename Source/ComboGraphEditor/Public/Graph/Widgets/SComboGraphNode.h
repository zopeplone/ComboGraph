// 

#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"

class UEdComboGraphNode;
/**
 * 
 */
class COMBOGRAPHEDITOR_API SComboGraphNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SComboGraphNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdComboGraphNode* InNode);

	virtual void UpdateGraphNode() override;
	virtual void CreatePinWidgets() override;
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;
	virtual bool IsNameReadOnly() const override;
};
