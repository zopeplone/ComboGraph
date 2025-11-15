// 

#pragma once

#include "CoreMinimal.h"
#include "ComboGraphCommon.generated.h"

class UComboGraphAsset;


UCLASS(BlueprintType,Blueprintable,Abstract)
class UComboGraphEdgeFuncContext : public UObject
{
	GENERATED_BODY()
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