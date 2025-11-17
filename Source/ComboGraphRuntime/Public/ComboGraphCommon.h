// 

#pragma once

#include "CoreMinimal.h"
#include "ComboGraphCommon.generated.h"

class UComboGraphAsset;


UCLASS(BlueprintType,Blueprintable,Abstract)
class COMBOGRAPHRUNTIME_API UComboGraphEdgeFuncContext : public UObject
{
	GENERATED_BODY()
public:
	// UComboGraphEdgeFuncContext(const FObjectInitializer& ObjectInitializer);
	virtual ~UComboGraphEdgeFuncContext() override = default;
	
	// 留给子类继承
};

USTRUCT(BlueprintType)
struct FComboGraphResolveContext
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite)
	FGuid CurrentNodeId;
	UPROPERTY(BlueprintReadOnly)
	UComboGraphAsset* GraphAsset;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UComboGraphEdgeFuncContext> EdgeFuncContext = nullptr;
};
USTRUCT(BlueprintType)
struct FComboGraphResolveResult
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly)
	bool CanEnterNext = false;
	UPROPERTY(BlueprintReadOnly)
	FGuid NextNodeId;
};