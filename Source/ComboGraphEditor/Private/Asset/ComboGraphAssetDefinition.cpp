// 


#include "Asset/ComboGraphAssetDefinition.h"

#include "ComboGraphAsset.h"
#include "ComboGraphEditor.h"

FText UComboGraphAssetDefinition::GetAssetDisplayName() const
{
	return FText::FromString(TEXT("Combo Graph"));
}

FLinearColor UComboGraphAssetDefinition::GetAssetColor() const
{
	return FColor(255, 196, 128);
}

TSoftClassPtr<UObject> UComboGraphAssetDefinition::GetAssetClass() const
{
	return UComboGraphAsset::StaticClass();
}

// TConstArrayView<FAssetCategoryPath> UComboGraphAssetDefinition::GetAssetCategories() const
// {
// 	return {NSLOCTEXT("ComboGraph","ComboGraphCategory","ComboGraph")};
// }

EAssetCommandResult UComboGraphAssetDefinition::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
	for (UComboGraphAsset* ComboGraphAsset : OpenArgs.LoadObjects<UComboGraphAsset>())
	{
		const FComboGraphEditorModule* ComboGraphEditorModule = &FModuleManager::LoadModuleChecked<FComboGraphEditorModule>("ComboGraphEditor");
		ComboGraphEditorModule->CreateComboGraphAssetEditor(OpenArgs.GetToolkitMode(), OpenArgs.ToolkitHost, ComboGraphAsset);
	}

	return EAssetCommandResult::Handled;
}
