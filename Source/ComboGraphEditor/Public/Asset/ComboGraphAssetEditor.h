// 

#pragma once

#include "CoreMinimal.h"


class SComboGraphEditor;
class UComboGraphAsset;
/**
 * 
 */
class COMBOGRAPHEDITOR_API FComboGraphAssetEditor : public FAssetEditorToolkit, public FEditorUndoClient, public FGCObject, public FNotifyHook
{
public:
	/**	The tab ids for all the tabs used */
	static const FName DetailsTab;
	static const FName GraphTab;

protected:
	TObjectPtr<UComboGraphAsset> ComboGraphAsset;
public:
	FComboGraphAssetEditor();
	virtual ~FComboGraphAssetEditor();
	// 必须实现的接口
	virtual FName GetToolkitFName() const override { return FName("ComboGraphEditor"); }
	virtual FText GetBaseToolkitName() const override { return NSLOCTEXT("ComboGraph", "AssetToolkitName", "ComboGraph编辑器"); }
	virtual FString GetWorldCentricTabPrefix() const override { return NSLOCTEXT("ComboGraph", "AssetToolkitTabPrefix", "ComboGraphAsset").ToString(); }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor::Green; }

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void SaveAsset_Execute() override;
	
	void InitComboGraphAssetEditor(EToolkitMode::Type Mode,const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* ObjectToEdit);

	UComboGraphAsset* GetComboGraphAsset() const {return ComboGraphAsset.Get();}
private:
	// 生成细节面板
	TSharedRef<SDockTab> SpawnDetailTab(const FSpawnTabArgs& Args);
	
	// 生成图面板
	TSharedPtr<FUICommandList> GraphEditorCommands;
	
	TSharedRef<SDockTab> SpawnGraphTab(const FSpawnTabArgs& Args);
	void CreateGraphCommands();
	FGraphPanelSelectionSet GetSelectedNodes() const;
	void SelectAllNodes();
	bool CanSelectAllNodes() const;
	void DeleteSelectedNodes();
	bool CanDeleteNodes() const;
	void CopySelectedNodes();
	bool CanCopyNodes() const;
	void CutSelectedNodes();
	bool CanCutNodes() const;
	void PasteNodes();
	bool CanPasteNodes() const;
	void DuplicateNodes();
	bool CanDuplicateNodes() const;

	// Graph Events
	void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection);

	void OnNodeDoubleClicked(UEdGraphNode* Node);
protected:
	TSharedPtr<class IDetailsView> PropertyWidget;
	TSharedPtr<SComboGraphEditor> GraphWidget;
	
public:
	// FGCObject
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	virtual FString GetReferencerName() const override
	{
		return TEXT("FComboGraphAssetEditor");
	}
};


