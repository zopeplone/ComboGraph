
#include "Asset/ComboGraphAssetFactory.h"

#include "ComboGraphAsset.h"
#include "AssetToolsModule.h"
#include "Graph/EdComboGraph.h"

UComboGraphAssetFactory::UComboGraphAssetFactory()
{
	SupportedClass = UComboGraphAsset::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UComboGraphAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name,
	EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	// 持久化ComboGraphAsset以及其EdGraph
	auto* ComboGraphAsset = NewObject<UComboGraphAsset>(InParent, Class, Name, Flags);
	UEdComboGraph::CreateGraph(ComboGraphAsset);
	return ComboGraphAsset;
}

uint32 UComboGraphAssetFactory::GetMenuCategories() const
{
	// 让它出现在指定分类下（比如蓝图分类）
	return EAssetTypeCategories::Misc; 
}