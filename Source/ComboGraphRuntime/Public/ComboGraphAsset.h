// 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ComboGraphAsset.generated.h"

class UComboGraphAnyNode;
class UComboGraphEdge;
class UComboGraphNode;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, hideCategories = Object)
class COMBOGRAPHRUNTIME_API UComboGraphAsset : public UObject
{
	GENERATED_BODY()
public:
	friend class UComboGraphLibrary;
	UPROPERTY(EditDefaultsOnly, Category = "ComboGraph")
	FString Name;
	UFUNCTION(BlueprintCallable, Category = "ComboGraph")
	UComboGraphNode* GetNode(FGuid Id) const;
	UFUNCTION(BlueprintCallable, Category = "ComboGraph")
	UComboGraphEdge* GetEdge(FGuid Id) const;
private:
	UPROPERTY()
	TMap<FGuid, TObjectPtr<UComboGraphNode>> Nodes;
	UPROPERTY()
	TMap<FGuid,TObjectPtr<UComboGraphEdge>> Edges;
	UPROPERTY()
	TArray<FGuid> AnyNodeIds;
	UPROPERTY()
	FGuid RootNodeId;
	
// Graph (editor-only)
#if WITH_EDITOR
public:	
	friend class UEdComboGraph;
	UEdGraph* GetEdGraph() const { return EdGraph; }
#endif

	
#if WITH_EDITORONLY_DATA
private:
	UPROPERTY()
	TObjectPtr<UEdGraph> EdGraph;
#endif
	
};
