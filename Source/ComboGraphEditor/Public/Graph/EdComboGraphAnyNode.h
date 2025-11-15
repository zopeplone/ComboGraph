// 

#pragma once

#include "CoreMinimal.h"
#include "EdComboGraphNode.h"
#include "EdComboGraphAnyNode.generated.h"

/**
 * 
 */
UCLASS()
class COMBOGRAPHEDITOR_API UEdComboGraphAnyNode : public UEdComboGraphNode
{
	GENERATED_BODY()
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;

	virtual UObject* GetUObjectToEditProperty() override;
	virtual bool CanAcceptConnectionFrom() const override { return false; }
	virtual TSubclassOf<UComboGraphNode> GetAssetNodeClass() const override;
};
