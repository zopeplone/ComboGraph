#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class UComboGraphAsset;
class FComboGraphAssetEditor;

class FComboGraphEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
public:
    static TSharedRef<FComboGraphAssetEditor> CreateComboGraphAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UComboGraphAsset* ComboGraphAsset);
};
