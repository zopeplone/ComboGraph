// 

#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"

class UEdComboGraphEdge;
/**
 * 
 */
class COMBOGRAPHEDITOR_API SComboGraphEdge : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SComboGraphEdge) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdComboGraphEdge* InEdge);

	virtual void UpdateGraphNode() override;

	virtual void PerformSecondPassLayout(const TMap<UObject*, TSharedRef<SNode>>& InNodeToWidgetLookup) const override;
	virtual bool RequiresSecondPassLayout() const override;
	
};
