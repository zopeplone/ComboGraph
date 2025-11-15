// 

#pragma once

#include "CoreMinimal.h"
#include "ComboGraphCommon.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ComboGraphLibrary.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class COMBOGRAPHRUNTIME_API UComboGraphLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category="ComboGraph")
	static bool TryEvaluateEdgeFunc(const FComboGraphResolveContext& Context,FGuid EdgeId);
	UFUNCTION(BlueprintCallable, Category="ComboGraph")
	static FComboGraphResolveResult TryResolveNextNode(const FComboGraphResolveContext& Context);
};
