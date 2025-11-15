#include "ComboGraphEditor.h"

#include "ComboGraphAsset.h"
#include "Asset/ComboGraphAssetEditor.h"

#define LOCTEXT_NAMESPACE "FComboGraphEditorModule"

void FComboGraphEditorModule::StartupModule()
{
    
}

void FComboGraphEditorModule::ShutdownModule()
{
    
}

TSharedRef<FComboGraphAssetEditor> FComboGraphEditorModule::CreateComboGraphAssetEditor(const EToolkitMode::Type Mode,
	const TSharedPtr<IToolkitHost>& InitToolkitHost, UComboGraphAsset* ComboGraphAsset)
{
	TSharedRef<FComboGraphAssetEditor> NewAssetEditor = MakeShared<FComboGraphAssetEditor>();
	NewAssetEditor->InitComboGraphAssetEditor(Mode, InitToolkitHost, ComboGraphAsset);
	return NewAssetEditor;
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FComboGraphEditorModule, ComboGraphEditor)