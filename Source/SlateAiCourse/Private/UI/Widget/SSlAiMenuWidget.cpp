// Fill out your copyright notice in the Description page of Project Settings.


#include "SSlAiMenuWidget.h"
#include "SlateOptMacros.h"
#include <SlAiMenuWidgetStyle.h>
#include <SlAiStyle.h>
#include "SBox.h"
#include "SImage.h"
#include "SBorder.h"
#include "STextBlock.h"
#include "SSlAiMenuItemWidget.h"
#include "Common/SlAiHelper.h"
#include <SSlAiGameOptionWidget.h>
#include "SlAiDataHandle.h"
#include "SSlAiNewGameWidget.h"
#include "SSlAiChooseRecordWidget.h"

struct MenuGroup
{
	//�˵�����
	FText MenuName;
	//�˵��߶�
	float MenuHeight;
	TArray<TSharedPtr<SCompoundWidget>> ChildWidget;
	//���캯��
	MenuGroup(const FText Name, const float height, TArray<TSharedPtr<SCompoundWidget>>* Children)
	{
		MenuName = Name;
		MenuHeight = height;

		//ChildWidget = *Children;    //Ҳ���ԡ�
		for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It(*Children);It;It++)
		{
			ChildWidget.Add(*It);
		}
	}
};


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiMenuWidget::Construct(const FArguments& InArgs)
{
	MenuStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiMenuStyle>("BP_SlAiMenuStyle");
	

	ChildSlot
		[
			SAssignNew(RootSizeBox, SBox)
			[
				SNew(SOverlay)
			+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(0.0f, 50.0f, 0.0f, 0.0f))
				[
					SNew(SImage)
					.Image(&MenuStyle->MenuBackgroundBrush)
				]
			+ SOverlay::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
				.Padding(FMargin(0.0f, 25.0f, 0.0f, 0.0f))
				[
					SNew(SImage)
					.Image(&MenuStyle->LeftIconBrush)
				]
			+ SOverlay::Slot()
				.HAlign(HAlign_Right)
				.VAlign(VAlign_Center)
				.Padding(FMargin(0.0f, 25.0f, 0.0f, 0.0f))
				[
					SNew(SImage)
					.Image(&MenuStyle->RightIconBrush)
				]
			//����
			+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Top)
				[
					SNew(SBox)
					.WidthOverride(400.0f)
					.HeightOverride(100.0f)
					[
						SNew(SBorder)
						.BorderImage(&MenuStyle->TitleBorderBrush)
						.HAlign(HAlign_Center) 
						.VAlign(VAlign_Center)
						[
							SAssignNew(TitleText, STextBlock)
							.Font(MenuStyle->Font_60)
							.Text(NSLOCTEXT("SlAiMenu", "Menu", "Menu"))
						]
					]
				]
			+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Top)
				.Padding(FMargin(0.0f, 130.0f, 0.0f, 0.0f))
				[
					SAssignNew(ContentBox,SVerticalBox)
				]
		]
	];

	InitializedMenuList();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiMenuWidget::MenuItemOnClicked(EMenuItem::Type ItemType)
{
	//SlAiHelper::Debug(TEXT("Start Game"),5.0f);
}

void SSlAiMenuWidget::ChangeCulture(ECultureTeam Culture)
{
	SlAiDataHandle::Get()->ChangeLocalizationCulture(Culture);
}

void SSlAiMenuWidget::ChangeVolume(const float MusicVolume, const float SoundVolume)
{
	SlAiDataHandle::Get()->ResetMenuVolume(MusicVolume, SoundVolume);
}

void SSlAiMenuWidget::InitializedMenuList()
{
	RootSizeBox->SetWidthOverride(600.0f);
	RootSizeBox->SetWidthOverride(510.0f);

	//ʵ����������
	TArray<TSharedPtr<SCompoundWidget>> MainMenuList;
	MainMenuList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "StartGame", "StartGame")).ItemType(EMenuItem::StartGame).OnClick(this, &SSlAiMenuWidget::MenuItemOnClicked));
	MainMenuList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "GameOption", "GameOption")).ItemType(EMenuItem::GameOption).OnClick(this, &SSlAiMenuWidget::MenuItemOnClicked));
	MainMenuList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "QuitGame", "QuitGame")).ItemType(EMenuItem::QuitGame).OnClick(this, &SSlAiMenuWidget::MenuItemOnClicked));

	MenuMap.Add(EMenuType::MainMenu, MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu", "Menu", "Menu"), 510.f, &MainMenuList)));

	//��ʼ��Ϸ����
	TArray<TSharedPtr<SCompoundWidget>> StartGameList;
	StartGameList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "NewGame", "NewGame")).ItemType(EMenuItem::NewGame).OnClick(this, &SSlAiMenuWidget::MenuItemOnClicked));
	StartGameList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "LoadRecord", "LoadRecord")).ItemType(EMenuItem::LoadRecord).OnClick(this, &SSlAiMenuWidget::MenuItemOnClicked));
	StartGameList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "GoBack", "GoBack")).ItemType(EMenuItem::StartGameGoBack).OnClick(this, &SSlAiMenuWidget::MenuItemOnClicked));

	MenuMap.Add(EMenuType::StartGame, MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu", "StartGame", "StartGame"), 510.f, &StartGameList)));
	
	//��Ϸ���ý���
	TArray<TSharedPtr<SCompoundWidget>> GameOptionList;
	//ʵ������Ϸ���õ�Widget
	SAssignNew(GameOptionWidget, SSlAiGameOptionWidget)
		.ChangeCulture(this, &SSlAiMenuWidget::ChangeCulture)
		.ChangeVolume(this, &SSlAiMenuWidget::ChangeVolume);
	//��ӿؼ�������
	GameOptionList.Add(GameOptionWidget);
	GameOptionList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "GoBack", "GoBack")).ItemType(EMenuItem::GameOptionGoBack).OnClick(this, &SSlAiMenuWidget::MenuItemOnClicked));

	MenuMap.Add(EMenuType::GameOption, MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu", "GameOption", "GameOption"), 610.f, &GameOptionList)));

	//��ʼ����Ϸ����
	TArray<TSharedPtr<SCompoundWidget>> NewGameList;
	SAssignNew(NewGameWidget, SSlAiNewGameWidget);
	NewGameList.Add(NewGameWidget);
	NewGameList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "EnterGame", "EnterGame")).ItemType(EMenuItem::EnterGame).OnClick(this, &SSlAiMenuWidget::MenuItemOnClicked));
	NewGameList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "GoBack", "GoBack")).ItemType(EMenuItem::NewGameGoBack).OnClick(this, &SSlAiMenuWidget::MenuItemOnClicked));

	MenuMap.Add(EMenuType::NewGame, MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu", "NewGame", "NewGame"), 510.f, &NewGameList)));

	//ѡ��浵����
	TArray<TSharedPtr<SCompoundWidget>> ChooseRecordList;
	SAssignNew(ChooseRecordWidget, SSlAiChooseRecordWidget);
	ChooseRecordList.Add(ChooseRecordWidget);
	ChooseRecordList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "EnterRecord", "EnterRecord")).ItemType(EMenuItem::EnterRecord).OnClick(this, &SSlAiMenuWidget::MenuItemOnClicked));
	ChooseRecordList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "GoBack", "GoBack")).ItemType(EMenuItem::ChooseRecordGoBack).OnClick(this, &SSlAiMenuWidget::MenuItemOnClicked));

	MenuMap.Add(EMenuType::ChooseRecord, MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu", "LoadRecord", "LoadRecord"), 510.f, &ChooseRecordList)));

	ChooseWidget(EMenuType::MainMenu);
}

void SSlAiMenuWidget::ChooseWidget(EMenuType::Type WidgetType)
{
	//�Ƴ��������(�л��¿ؼ�ǰ���ԭ�����е��ӿؼ�)
	ContentBox->ClearChildren();
	//���Menutype��None
	if (WidgetType == EMenuType::None)
		return;
	for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It((*MenuMap.Find(WidgetType))->ChildWidget); It; ++It)
	{
		ContentBox->AddSlot().AutoHeight()[(*It)->AsShared()];
	}
	//���ı���
	TitleText->SetText((*MenuMap.Find(WidgetType))->MenuName);
	//�޸�size
	ResetWidgetSize(600.0f, (*MenuMap.Find(WidgetType))->MenuHeight);
}

//������޸ĸ߶�,NewHeightת��-1
void SSlAiMenuWidget::ResetWidgetSize(float NewWidget, float NewHeight)
{
	RootSizeBox->SetWidthOverride(NewWidget);
	if (NewHeight < 0) return;
	RootSizeBox->SetHeightOverride(NewHeight);
}
