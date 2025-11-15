// 

#include "Graph/Widgets/SComboGraphEditor.h"
#include "Asset/ComboGraphAssetEditor.h"
#include "ComboGraphRuntime/Public/ComboGraphAsset.h"

void SComboGraphEditor::Construct(const FArguments& InArgs, const TSharedPtr<FComboGraphAssetEditor> InAssetEditor)
{
	ComboGraphAssetEditor = InAssetEditor.ToWeakPtr();
	ComboGraphAsset = ComboGraphAssetEditor.Pin()->GetComboGraphAsset();
	

	SGraphEditor::FArguments Arguments;
	Arguments._AdditionalCommands = InArgs._AdditionalCommands;
	// Arguments._Appearance = GetGraphAppearanceInfo();
	Arguments._GraphToEdit = ComboGraphAsset->GetEdGraph();
	Arguments._IsEditable = true;
	Arguments._GraphEvents = InArgs._GraphEvents;
	// Arguments._AutoExpandActionMenu = true;
	// Arguments._GraphEvents.OnSelectionChanged = FOnSelectionChanged::CreateSP(this, &SFlowGraphEditor::OnSelectedNodesChanged);
	// Arguments._GraphEvents.OnNodeDoubleClicked = FSingleNodeEvent::CreateSP(this, &SFlowGraphEditor::OnNodeDoubleClicked);
	// Arguments._GraphEvents.OnTextCommitted = FOnNodeTextCommitted::CreateSP(this, &SFlowGraphEditor::OnNodeTitleCommitted);
	// Arguments._GraphEvents.OnSpawnNodeByShortcut = FOnSpawnNodeByShortcut::CreateStatic(&SFlowGraphEditor::OnSpawnGraphNodeByShortcut, static_cast<UEdGraph*>(FlowAsset->GetGraph()));

	SGraphEditor::Construct(Arguments);
}
