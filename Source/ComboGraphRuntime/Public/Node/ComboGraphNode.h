// 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ComboGraphNode.generated.h"

class UGameplayAbility;
class UComboGraphAsset;
class UComboGraphEdge;
/**
 * 
 */
UCLASS()
class COMBOGRAPHRUNTIME_API UComboGraphNode : public UObject
{
	GENERATED_BODY()

public:
	UComboGraphNode();
	virtual ~UComboGraphNode();
	
	UPROPERTY()
	FGuid Id;
	UPROPERTY()
	TObjectPtr<UComboGraphAsset> GraphAsset;
	
	UPROPERTY()
	TMap<FGuid,TObjectPtr<UComboGraphEdge>> Input;
	UPROPERTY()
	TMap<FGuid,TObjectPtr<UComboGraphEdge>> Output;

	// UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "ComboGraphNode",meta=(ShowOnlyInnerProperties))
	// FComboNodeParams NodeParams;
	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// TObjectPtr<UAnimMontage> Montage;
	// UPROPERTY(EditAnywhere)
	// TSubclassOf<UGameplayAbility> AnimMontage;
	UFUNCTION(BlueprintPure, Category = "ComboGraphNode")
	UComboGraphEdge* GetOutputEdge(FGuid EdgeId) const;
	
	UFUNCTION(BlueprintPure, Category = "ComboGraphNode")
	bool IsLeafNode() const;
	
	UFUNCTION(BlueprintPure, Category = "ComboGraphNode")
	UComboGraphAsset* GetGraph() const;
	
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditDefaultsOnly, Category = "ComboGraphEditor")
	FText NodeTitle;
#endif
#if WITH_EDITOR
	virtual FText GetNodeTitle() const;
	virtual void SetNodeTitle(const FText& NewTitle);
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	
};
