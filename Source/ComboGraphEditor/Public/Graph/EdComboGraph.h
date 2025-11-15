// 

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "EdComboGraph.generated.h"

class UComboGraphAsset;
/**
 * 
 */
UCLASS()
class COMBOGRAPHEDITOR_API UEdComboGraph : public UEdGraph
{
	GENERATED_BODY()
public:
	
	static void CreateGraph(UComboGraphAsset* InAsset);

	UComboGraphAsset* GetComboGraphAsset() const;
	virtual void PostEditUndo() override;
	virtual void SaveAsset();
};
