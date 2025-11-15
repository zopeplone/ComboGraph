// 


#include "Asset/ComboGraphAssetEditor.h"

#include "ComboGraphAsset.h"
#include "GraphEditorActions.h"
#include "Framework/Commands/GenericCommands.h"
#include "Graph/EdComboGraph.h"
#include "Graph/EdComboGraphNode.h"
#include "Graph/Widgets/SComboGraphEditor.h"

const FName FComboGraphAssetEditor::DetailsTab(TEXT("Details"));
const FName FComboGraphAssetEditor::GraphTab(TEXT("Graph"));
FComboGraphAssetEditor::FComboGraphAssetEditor()
{
}

FComboGraphAssetEditor::~FComboGraphAssetEditor()
{
}

void FComboGraphAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(NSLOCTEXT("ComboGraph", "WorkspaceMenu_ComboGraphEditor", "ComboGraphEditor"));
	const auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	InTabManager->RegisterTabSpawner(DetailsTab,
		FOnSpawnTab::CreateRaw(this, &FComboGraphAssetEditor::SpawnDetailTab))
		.SetDisplayName(NSLOCTEXT("ComboGraph", "DetailsTab" ,"细节"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details"));

	InTabManager->RegisterTabSpawner(GraphTab,
		FOnSpawnTab::CreateRaw(this, &FComboGraphAssetEditor::SpawnGraphTab))
		.SetDisplayName(NSLOCTEXT("ComboGraph", "GraphTab" ,"图表"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "GraphEditor.EventGraph_16x"));
}

void FComboGraphAssetEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner(DetailsTab);
}

void FComboGraphAssetEditor::SaveAsset_Execute()
{
	UE_LOG(LogTemp,Display,TEXT("保存文件 FComboGraphAssetEditor"));
	UEdComboGraph* EdComboGraph = CastChecked<UEdComboGraph>( ComboGraphAsset->GetEdGraph());
	EdComboGraph->SaveAsset();
	FAssetEditorToolkit::SaveAsset_Execute();
}

void FComboGraphAssetEditor::InitComboGraphAssetEditor(EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* ObjectToEdit)
{
	FGenericCommands::Register();
	FGraphEditorCommands::Register();
	ComboGraphAsset = CastChecked<UComboGraphAsset>(ObjectToEdit);
	
	
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("ComboGraphAssetEditor_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.225f)
					->AddTab(DetailsTab, ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewSplitter()
					->SetSizeCoefficient(0.65f)
					->SetOrientation(Orient_Vertical)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.8f)
						->SetHideTabWell(true)
						->AddTab(GraphTab, ETabState::OpenedTab)
					)
				)
										
		);

	InitAssetEditor(Mode, InitToolkitHost, FName("ComboGraphAssetEditor"), StandaloneDefaultLayout, true, true, ObjectToEdit);
	RegenerateMenusAndToolbars();
}

TSharedRef<SDockTab> FComboGraphAssetEditor::SpawnDetailTab(const FSpawnTabArgs& Args)
{
	//加载属性编辑器模块
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::Get().LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	const FDetailsViewArgs DetailsViewArgs;
	//创建属性编辑器的Slate
	PropertyWidget = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	//将对象传入，这样就是自动生成对象的属性面板
	PropertyWidget->SetObject(GetEditingObject());
	
	return SNew(SDockTab)
		.Label(NSLOCTEXT("ComboGraph", "DetailTabTitle", "细节"))
	[
		PropertyWidget.ToSharedRef()
	];
}

TSharedRef<SDockTab> FComboGraphAssetEditor::SpawnGraphTab(const FSpawnTabArgs& Args) 
{
	CreateGraphCommands();
	SGraphEditor::FGraphEditorEvents Events;
	Events.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FComboGraphAssetEditor::OnSelectedNodesChanged);
	Events.OnNodeDoubleClicked = FSingleNodeEvent::CreateSP(this,&FComboGraphAssetEditor::OnNodeDoubleClicked);
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.Label(NSLOCTEXT("ComboGraph", "GraphTabTitle", "图表"))
		[
			SAssignNew(GraphWidget,SComboGraphEditor,SharedThis(this))
				.AdditionalCommands(GraphEditorCommands)
				.GraphEvents(Events)
				.IsEditable(true)
		];
	
	return SpawnedTab;
}

void FComboGraphAssetEditor::CreateGraphCommands()
{
	if (GraphEditorCommands.IsValid())
	{
		return;
	}
	GraphEditorCommands = MakeShareable(new FUICommandList);
	
	GraphEditorCommands->MapAction(FGenericCommands::Get().SelectAll,
		FExecuteAction::CreateRaw(this, &FComboGraphAssetEditor::SelectAllNodes),
		FCanExecuteAction::CreateRaw(this, &FComboGraphAssetEditor::CanSelectAllNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Delete,
		FExecuteAction::CreateRaw(this, &FComboGraphAssetEditor::DeleteSelectedNodes),
		FCanExecuteAction::CreateRaw(this, &FComboGraphAssetEditor::CanDeleteNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Copy,
		FExecuteAction::CreateRaw(this, &FComboGraphAssetEditor::CopySelectedNodes),
		FCanExecuteAction::CreateRaw(this, &FComboGraphAssetEditor::CanCopyNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Cut,
		FExecuteAction::CreateRaw(this, &FComboGraphAssetEditor::CutSelectedNodes),
		FCanExecuteAction::CreateRaw(this, &FComboGraphAssetEditor::CanCutNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Paste,
		FExecuteAction::CreateRaw(this, &FComboGraphAssetEditor::PasteNodes),
		FCanExecuteAction::CreateRaw(this, &FComboGraphAssetEditor::CanPasteNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Duplicate,
		FExecuteAction::CreateRaw(this, &FComboGraphAssetEditor::DuplicateNodes),
		FCanExecuteAction::CreateRaw(this, &FComboGraphAssetEditor::CanDuplicateNodes)
	);
	//
	// GraphEditorCommands->MapAction(FGenericCommands::Get().Rename,
	// 	FExecuteAction::CreateSP(this, &FComboGraphAssetEditor::OnRenameNode),
	// 	FCanExecuteAction::CreateSP(this, &FComboGraphAssetEditor::CanRenameNodes)
	// );
}

FGraphPanelSelectionSet FComboGraphAssetEditor::GetSelectedNodes() const
{
	FGraphPanelSelectionSet CurrentSelection;
	TSharedPtr<SGraphEditor> FocusedGraphEd = GraphWidget;
	if (FocusedGraphEd.IsValid())
	{
		CurrentSelection = FocusedGraphEd->GetSelectedNodes();
	}

	return CurrentSelection;
}

void FComboGraphAssetEditor::SelectAllNodes()
{
	if (GraphWidget.IsValid())
	{
		GraphWidget->SelectAllNodes();
	}
}

bool FComboGraphAssetEditor::CanSelectAllNodes() const
{
	if (GraphWidget.IsValid()) return true;
	return false;
}

void FComboGraphAssetEditor::DeleteSelectedNodes()
{
	if (!GraphWidget.IsValid())
	{
		return;
	}
	const FScopedTransaction Transaction(FGenericCommands::Get().Delete->GetDescription());

	GraphWidget->GetCurrentGraph()->Modify();

	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	GraphWidget->ClearSelectionSet();

	for (FGraphPanelSelectionSet::TConstIterator NodeIt(SelectedNodes); NodeIt; ++NodeIt)
	{
		UEdGraphNode* EdNode = Cast<UEdGraphNode>(*NodeIt);
		if (EdNode == nullptr || !EdNode->CanUserDeleteNode())
			continue;

		if (UEdComboGraphNode* EdNode_Node = Cast<UEdComboGraphNode>(EdNode))
		{
			EdNode_Node->Modify();

			const UEdGraphSchema* Schema = EdNode_Node->GetSchema();
			if (Schema != nullptr)
			{
				Schema->BreakNodeLinks(*EdNode_Node);
			}

			EdNode_Node->DestroyNode();
		}
		else
		{
			EdNode->Modify();
			EdNode->DestroyNode();
		}
	}
}

bool FComboGraphAssetEditor::CanDeleteNodes() const
{
	// If any of the nodes can be deleted then we should allow deleting
	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		if (Node != nullptr && Node->CanUserDeleteNode())
		{
			return true;
		}
	}

	return false;
}

void FComboGraphAssetEditor::CopySelectedNodes()
{
}

bool FComboGraphAssetEditor::CanCopyNodes() const
{
	return true;
}

void FComboGraphAssetEditor::CutSelectedNodes()
{
}

bool FComboGraphAssetEditor::CanCutNodes() const
{
	return CanCopyNodes() && CanDeleteNodes();
}

void FComboGraphAssetEditor::PasteNodes()
{
}

bool FComboGraphAssetEditor::CanPasteNodes() const
{
	return false;
}

void FComboGraphAssetEditor::DuplicateNodes()
{
}


bool FComboGraphAssetEditor::CanDuplicateNodes() const
{
	return false;
}

void FComboGraphAssetEditor::OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection)
{
	if (NewSelection.Num() > 0)
	{
		auto SelectionNode = NewSelection.Array();
		TArray<UObject*> PropertyObjects;
		for (auto Node : SelectionNode)
		{
			if (Node && Node->GetClass()->ImplementsInterface(UComboGraphPropertyEdit::StaticClass()))
			{
				auto* ComboGraphPropertyEdit = Cast<IComboGraphPropertyEdit>(Node);
				UObject* UObjectToEditProperty = ComboGraphPropertyEdit->GetUObjectToEditProperty();
				if (UObjectToEditProperty) PropertyObjects.Add(UObjectToEditProperty);
			}
		}
		PropertyWidget->SetObjects(PropertyObjects);
	}
	else
	{
		PropertyWidget->SetObject(GetEditingObject());
	}
}
void FComboGraphAssetEditor::OnNodeDoubleClicked(UEdGraphNode* Node)
{
	auto EdgeNode = Cast<UEdComboGraphNode>(Node);
	if (!EdgeNode) return;
	// TODO: 双击Edge进入蓝图编辑
}

void FComboGraphAssetEditor::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(ComboGraphAsset);
}
