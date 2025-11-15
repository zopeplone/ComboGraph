// 

#pragma once

#include "CoreMinimal.h"
#include "ComboGraphNode.h"
#include "ComboGraphExecuteNode.generated.h"

/**
 * 
 */
UCLASS()
class COMBOGRAPHRUNTIME_API UComboGraphExecuteNode : public UComboGraphNode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> Montage;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayAbility> Ability;
};
