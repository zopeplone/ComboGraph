// 

#pragma once

#include "CoreMinimal.h"
#include "EdComboGraphNode.h"
#include "EdComboGraphExecuteNode.generated.h"

/**
 * 
 */
UCLASS()
class COMBOGRAPHEDITOR_API UEdComboGraphExecuteNode : public UEdComboGraphNode
{
	GENERATED_BODY()
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
	virtual TSubclassOf<UComboGraphNode> GetAssetNodeClass() const override;
};
