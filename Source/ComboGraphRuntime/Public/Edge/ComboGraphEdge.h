// 

#pragma once

#include "CoreMinimal.h"
#include "ComboEdgeFunctionLibrary.h"
#include "UObject/Object.h"
#include "ComboGraphEdge.generated.h"

class UComboGraphAsset;


/**
 * 
 */
UCLASS()
class COMBOGRAPHRUNTIME_API UComboGraphEdge : public UObject

{
	GENERATED_BODY()
public:
	UPROPERTY()
	FGuid Id;
	UPROPERTY()
	TObjectPtr<UComboGraphAsset> GraphAsset;
	UPROPERTY()
	FGuid StartNodeId;
	UPROPERTY()
	FGuid EndNodeId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Sort;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UComboEdgeFunctionLibrary> FunctionClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta=(GetOptions="GetEdgeFunctionList"))
	FName FunctionName;

	UFUNCTION(BlueprintPure, Category = "ComboGraphEdge")
	UComboGraphAsset* GetGraph() const;

	
#if WITH_EDITOR
	UFUNCTION()
	TArray<FName> GetEdgeFunctionList();
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
