// 

#pragma once

#include "CoreMinimal.h"
#include "SComboGraphNode.h"

/**
 * 
 */
class COMBOGRAPHEDITOR_API SComboGraphExecuteNode : public SComboGraphNode
{
public:
	SLATE_BEGIN_ARGS(SComboGraphExecuteNode) {}
	SLATE_END_ARGS()
	void Construct(const FArguments& InArgs, UEdComboGraphNode* InNode);

	virtual void UpdateGraphNode() override;
};
