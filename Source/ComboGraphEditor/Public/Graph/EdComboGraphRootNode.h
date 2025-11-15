// 

#pragma once

#include "CoreMinimal.h"
#include "EdComboGraphNode.h"
#include "EdComboGraphRootNode.generated.h"

/**
 * 
 */
UCLASS()
class COMBOGRAPHEDITOR_API UEdComboGraphRootNode : public UEdComboGraphNode
{
	GENERATED_BODY()
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
	virtual bool CanUserDeleteNode() const override;
	virtual UObject* GetUObjectToEditProperty() override{return nullptr;}
	virtual bool CanAcceptConnectionFrom() const override {return false;}

};
