// 

#pragma once

#include "CoreMinimal.h"
#include "SComboGraphNode.h"

/**
 * 
 */
class COMBOGRAPHEDITOR_API SComboGraphRootNode : public SComboGraphNode
{
public:
	SLATE_BEGIN_ARGS(SComboGraphRootNode) {}
	SLATE_END_ARGS()
	void Construct(const FArguments& InArgs, UEdComboGraphNode* InNode);
	virtual void UpdateGraphNode() override;
};
