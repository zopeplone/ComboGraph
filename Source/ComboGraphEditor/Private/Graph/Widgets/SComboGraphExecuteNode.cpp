// 


#include "Graph/Widgets/SComboGraphExecuteNode.h"

#include "GraphEditorSettings.h"
#include "SCommentBubble.h"
#include "Abilities/GameplayAbility.h"

#include "Graph/EdComboGraphNode.h"
#include "Node/ComboGraphExecuteNode.h"
#include "Node/ComboGraphNode.h"
#include "ThumbnailRendering/ThumbnailManager.h"


void SComboGraphExecuteNode::Construct(const FArguments& InArgs, UEdComboGraphNode* InNode)
{
	SComboGraphNode::Construct(SComboGraphNode::FArguments(),InNode);
}

void SComboGraphExecuteNode::UpdateGraphNode()
{
	const FMargin NodePadding = FMargin(5);
	const FMargin NamePadding = FMargin(2);

	InputPins.Empty();
	OutputPins.Empty();

	// Reset variables that are going to be exposed, in case we are refreshing an already setup node.
	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	const FSlateBrush* NodeTypeIcon = FAppStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Icon"));

	FLinearColor TitleShadowColor(0.6f, 0.6f, 0.6f);
	TSharedPtr<SErrorText> ErrorText;
	TSharedPtr<SVerticalBox> NodeBody;
	TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);

	
	
	TSharedPtr<SWidget> Thumbnail;
	UEdComboGraphNode* EdNode = Cast<UEdComboGraphNode>(GraphNode);
	UAnimMontage* Montage = nullptr;
	TSubclassOf<UGameplayAbility> Ability = nullptr;
	if (EdNode && EdNode->GetAssetNode())
	{
		UComboGraphExecuteNode* ComboGraphExecuteNode = CastChecked<UComboGraphExecuteNode>(EdNode->GetAssetNode());
		Montage = ComboGraphExecuteNode->Montage;
		Ability = ComboGraphExecuteNode->Ability;
	}
	// TSharedPtr<FAssetThumbnailPool> ThumbnailPool = MakeShareable(new FAssetThumbnailPool(4));
	
	FAssetData AD(Montage);
	auto AssetThumbnail = MakeShared<FAssetThumbnail>(AD, 180, 180, UThumbnailManager::Get().GetSharedThumbnailPool());
	FAssetThumbnailConfig Config;
	
	// Config.bAllowAssetSpecificThumbnailOverlay = true;
	Thumbnail = AssetThumbnail->MakeThumbnailWidget(Config);
	
	

	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);
	this->GetOrAddSlot(ENodeZone::Center)
	    .HAlign(HAlign_Fill)
	    .VAlign(VAlign_Center)
	[
		SNew(SBorder)
		             .BorderImage(FAppStyle::GetBrush("Graph.StateNode.Body"))
		             .Padding(0.0f)
			// TODO: 获取可修改的边框颜色
		             .BorderBackgroundColor(FLinearColor::Gray)
		[
			SNew(SOverlay)

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SVerticalBox)

				// Input Pin Area
				+ SVerticalBox::Slot()
				.FillHeight(1)
				[
					SAssignNew(LeftNodeBox, SVerticalBox)
				]

				// Output Pin Area	
				+ SVerticalBox::Slot()
				.FillHeight(1)
				[
					SAssignNew(RightNodeBox, SVerticalBox)
				]
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.Padding(8.0f)
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::GetBrush("Graph.StateNode.ColorSpill"))
				.BorderBackgroundColor(TitleShadowColor)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.Visibility(EVisibility::SelfHitTestInvisible)
				.Padding(6.0f)
				[
					SAssignNew(NodeBody, SVerticalBox)

					// Title
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						SNew(SVerticalBox)
						// 中间：缩略图（尽量保持固定大小并居中）
						+ SVerticalBox::Slot()
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Center)
						.AutoHeight()
						[
							// 尝试从 GraphNode 获取 Montage 并用 AssetThumbnail 显示
							Thumbnail.ToSharedRef()
						]
						// 底部：蒙太奇名字栏
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(FMargin(0, 6, 0, 0))
						[
							SNew(SBorder)
							.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
							.BorderBackgroundColor(FLinearColor(0.12f, 0.12f, 0.12f))
							.Padding(FMargin(6.0f, 4.0f))
							.HAlign(HAlign_Left)
							[
								SNew(STextBlock)
								.WrapTextAt(180.f)
								.WrappingPolicy(ETextWrappingPolicy::AllowPerCharacterWrapping)
								.Text_Lambda([this,Montage]() -> FText
								{
									if (Montage)
									{
										return FText::FromString(TEXT("Montage: ") + Montage->GetName());
									}
									return FText::FromString(TEXT("Montage: None"));
								})
								.ColorAndOpacity(FSlateColor::UseForeground())
								
							]
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(FMargin(0, 6, 0, 0))
						[
							SNew(SBorder)
							.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
							.BorderBackgroundColor(FLinearColor(0.12f, 0.12f, 0.12f))
							.Padding(FMargin(6.0f, 4.0f))
							.HAlign(HAlign_Left)
							[
								SNew(STextBlock)
								.WrapTextAt(180.f)
								.WrappingPolicy(ETextWrappingPolicy::AllowPerCharacterWrapping)
								.Text_Lambda([this,Ability]() -> FText
								{
									if (Ability)
									{
										return FText::FromString(TEXT("Ability: ") + Ability->GetName());
									}
									return FText::FromString(TEXT("Ability: None"));
								})
								.ColorAndOpacity(FSlateColor::UseForeground())
								
							]
						]
						// SNew(SHorizontalBox)
						//
						// // Error message
						// + SHorizontalBox::Slot()
						// .AutoWidth()
						// [
						// 	SAssignNew(ErrorText, SErrorText)
						// 	.BackgroundColor(FLinearColor::Red)
						// 	.ToolTipText(FText::FromString(TEXT("ErrorText")))
						// ]

						// Icon
						// +SHorizontalBox::Slot()
						// .AutoWidth()
						// .VAlign(VAlign_Center)
						// [
						// 	SNew(SImage)
						// 	.Image(NodeTypeIcon)
						// ]

						// Node Title
						// + SHorizontalBox::Slot()
						// .Padding(FMargin(4.0f, 0.0f, 4.0f, 0.0f))
						// [
						// 	SNew(SVerticalBox)
						// 	+ SVerticalBox::Slot()
						// 	.AutoHeight()
						// 	[
						// 		SAssignNew(InlineEditableText, SInlineEditableTextBlock)
						// 		.Style(FAppStyle::Get(), "Graph.StateNode.NodeTitleInlineEditableText")
						// 		.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
						// 		// TODO: 绑定名称更改事件
						// 		// .OnVerifyTextChanged(this, &SEdNode_GenericGraphNode::OnVerifyNameTextChanged)
						// 		// .OnTextCommitted(this, &SEdNode_GenericGraphNode::OnNameTextCommited)
						// 		// .IsReadOnly(this, &SEdNode_GenericGraphNode::IsNameReadOnly)
						// 		// .IsSelected(this, &SEdNode_GenericGraphNode::IsSelectedExclusively)
						// 	]
						// 	+ SVerticalBox::Slot()
						// 	.AutoHeight()
						// 	[
						// 		NodeTitle.ToSharedRef()
						// 	]
						// ]
					]
				]
			]
		]
	];

	// Create comment bubble
	TSharedPtr<SCommentBubble> CommentBubble;
	const FSlateColor CommentColor = GetDefault<UGraphEditorSettings>()->DefaultCommentNodeTitleColor;

	SAssignNew(CommentBubble, SCommentBubble)
	.GraphNode(GraphNode)
	.Text(this, &SGraphNode::GetNodeComment)
	.OnTextCommitted(this, &SGraphNode::OnCommentTextCommitted)
	.ColorAndOpacity(CommentColor)
	.AllowPinning(true)
	.EnableTitleBarBubble(true)
	.EnableBubbleCtrls(true)
	.GraphLOD(this, &SGraphNode::GetCurrentLOD)
	.IsGraphNodeHovered(this, &SGraphNode::IsHovered);

	GetOrAddSlot(ENodeZone::TopCenter)
		.SlotOffset(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetOffset))
		.SlotSize(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetSize))
		.AllowScaling(TAttribute<bool>(CommentBubble.Get(), &SCommentBubble::IsScalingAllowed))
		.VAlign(VAlign_Top)
		[
			CommentBubble.ToSharedRef()
		];

	// ErrorReporting = ErrorText;
	// ErrorReporting->SetError(ErrorMsg);
	CreatePinWidgets();
}
