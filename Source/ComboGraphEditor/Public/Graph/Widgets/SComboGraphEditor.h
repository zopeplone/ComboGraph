// 

#pragma once

#include "CoreMinimal.h"

class UComboGraphAsset;
class FComboGraphAssetEditor;
/**
 * 
 */
class COMBOGRAPHEDITOR_API SComboGraphEditor: public SGraphEditor
{
public:
	void Construct(const FArguments& InArgs, const TSharedPtr<FComboGraphAssetEditor> InAssetEditor);

protected:
	TWeakObjectPtr<UComboGraphAsset> ComboGraphAsset;
	TWeakPtr<FComboGraphAssetEditor> ComboGraphAssetEditor;
};
