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
#if WITH_EDITOR
	virtual FText GetContextMenuDescription() const
	{
		return NSLOCTEXT("ComboGraph", "ExecuteNodeName", "招式节点");
	}
#endif
	
};
