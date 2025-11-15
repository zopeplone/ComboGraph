// 

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "EdComboGraphSchema.generated.h"


class UEdComboGraphNode;

USTRUCT()
struct COMBOGRAPHEDITOR_API FComboGraphAssetSchemaAction_NewNode : public FEdGraphSchemaAction
{
	GENERATED_BODY()
	
	TSubclassOf<UEdComboGraphNode> EdNodeClass;
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	
};

USTRUCT()
struct COMBOGRAPHEDITOR_API FComboGraphAssetSchemaAction_NewEdge : public FEdGraphSchemaAction
{
	GENERATED_BODY()

	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	
};

/**
 * 
 */
UCLASS()
class COMBOGRAPHEDITOR_API UEdComboGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()
	
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	virtual EGraphType GetGraphType(const UEdGraph* TestEdGraph) const override;
	virtual class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;

	// Connection: 外部调用 TryCreateConnection, Super::TryCreateConnection中调用CanCreateConnection判断连接类型/是否可以连接
	// 这里CanCreateConnection返回AutomaticConversion,Super::TryCreateConnection调用CreateAutomaticConversionNodeAndConnections来实现连接操作,或者拒绝连接;
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
	virtual bool TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const override;
	virtual bool CreateAutomaticConversionNodeAndConnections(UEdGraphPin* A, UEdGraphPin* B) const override;
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;
};



