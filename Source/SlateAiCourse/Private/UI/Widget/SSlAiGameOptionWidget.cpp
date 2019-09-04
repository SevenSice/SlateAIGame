// Fill out your copyright notice in the Description page of Project Settings.


#include "SSlAiGameOptionWidget.h"
#include "SlateOptMacros.h"
#include <SlAiStyle.h>
#include <SlAiMenuWidgetStyle.h>
#include <SlAiTypes.h>
#include "SBox.h"
#include "SOverlay.h"
#include "SImage.h"
#include "SBoxPanel.h"
#include "SCheckBox.h"
#include "Common/SlAiHelper.h"
#include "SSlider.h"
#include "STextBlock.h"

#include "SlAiDataHandle.h"



BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiGameOptionWidget::Construct(const FArguments& InArgs)
{
	//��ȡMenuStyle
	MenuStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiMenuStyle>("BP_SlAiMenuStyle");

	//��ȡί�У�����
	ChangeCulture = InArgs._ChangeCulture;
	ChangeVolume = InArgs._ChangeVolume;

	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(500.0f)
		.HeightOverride(300.0f)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(&MenuStyle->GameOptionBGBrush)
			]
		+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(FMargin(5.0f))
			[
				SNew(SVerticalBox)
				//��һ��
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.0f)
				[
					SNew(SHorizontalBox)

				+SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.FillWidth(1.0f)
					[
						SAssignNew(ZhCheckBox, SCheckBox)
						.OnCheckStateChanged(this, &SSlAiGameOptionWidget::ZhCheckBoxStateChanged)
						[
							SNew(STextBlock)
							.Font(MenuStyle->Font_40)
							.ColorAndOpacity(MenuStyle->FontColor_Black)
							.Text(NSLOCTEXT("SlAiMenu", "Chinese", "Chinese"))
						]
					]
				+ SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.FillWidth(1.0f)
					[
						SAssignNew(EnCheckBox, SCheckBox)
						.OnCheckStateChanged(this, &SSlAiGameOptionWidget::EnCheckBoxStateChanged)
						[
							SNew(STextBlock)
							.Font(MenuStyle->Font_40)
							.ColorAndOpacity(MenuStyle->FontColor_Black)
							.Text(NSLOCTEXT("SlAiMenu", "English", "English"))
						]
					]
				]
				//�ڶ���
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.0f)
				[
					SNew(SOverlay)

				+SOverlay::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Font(MenuStyle->Font_40)
					.ColorAndOpacity(MenuStyle->FontColor_Black)
					.Text(NSLOCTEXT("SlAiMenu", "Music", "Music"))
					]
				+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						SNew(SBox)
						.WidthOverride(240.0f)
						[
							SNew(SOverlay)
						+SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Center)
							.Padding(FMargin(30.0f,0.0f))
							[
								SNew(SImage)
								.Image(&MenuStyle->SliderBarBrush)
							]
						+SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Center)
							[
								SAssignNew(MuSlider,SSlider)
								.Style(&MenuStyle->SliderStyle)
								.OnValueChanged(this,&SSlAiGameOptionWidget::MusicSliderChanged)
							]
						]

					]
				+ SOverlay::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					[
						SAssignNew(MuTextBlock,STextBlock)
						.Font(MenuStyle->Font_40)
						.ColorAndOpacity(MenuStyle->FontColor_Black)
					]
				]
				//������
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.0f)
				[
					SNew(SOverlay)

				+ SOverlay::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Font(MenuStyle->Font_40)
						.ColorAndOpacity(MenuStyle->FontColor_Black)
						.Text(NSLOCTEXT("SlAiMenu", "Sound", "Sound"))
					]
				+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						SNew(SBox)
						.WidthOverride(240.0f)
						[
							SNew(SOverlay)
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Center)
							.Padding(FMargin(30.0f, 0.0f))
							[
								SNew(SImage)
								.Image(&MenuStyle->SliderBarBrush)
							]
					+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Center)
							[
								SAssignNew(SoSlider, SSlider)
								.Style(&MenuStyle->SliderStyle)
								.OnValueChanged(this, &SSlAiGameOptionWidget::SoundSliderChanged)
							]
						]

					]
				+ SOverlay::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					[
						SAssignNew(SoTextBlock, STextBlock)
						.Font(MenuStyle->Font_40)
						.ColorAndOpacity(MenuStyle->FontColor_Black)
					]
				]
			]
		]

	];
	StyleInitialized();
}
void SSlAiGameOptionWidget::StyleInitialized()
{
	//����ZhCheckBox��ʽ
	ZhCheckBox->SetUncheckedImage(&MenuStyle->UnCheckedBoxBrush);
	ZhCheckBox->SetUncheckedHoveredImage(&MenuStyle->UnCheckedBoxBrush);
	ZhCheckBox->SetUncheckedPressedImage(&MenuStyle->UnCheckedBoxBrush);
	ZhCheckBox->SetCheckedImage(&MenuStyle->CheckedBoxBrush);
	ZhCheckBox->SetCheckedHoveredImage(&MenuStyle->CheckedBoxBrush);
	ZhCheckBox->SetCheckedPressedImage(&MenuStyle->CheckedBoxBrush);

	//����EnCheckBox��ʽ
	EnCheckBox->SetUncheckedImage(&MenuStyle->UnCheckedBoxBrush);
	EnCheckBox->SetUncheckedHoveredImage(&MenuStyle->UnCheckedBoxBrush);
	EnCheckBox->SetUncheckedPressedImage(&MenuStyle->UnCheckedBoxBrush);
	EnCheckBox->SetCheckedImage(&MenuStyle->CheckedBoxBrush);
	EnCheckBox->SetCheckedHoveredImage(&MenuStyle->CheckedBoxBrush);
	EnCheckBox->SetCheckedPressedImage(&MenuStyle->CheckedBoxBrush);

	
	switch (SlAiDataHandle::Get()->CurrentCulture)
	{
	case ECultureTeam::EN:
		EnCheckBox->SetIsChecked(ECheckBoxState::Checked);
		ZhCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
		break;
	case ECultureTeam::ZH:
		EnCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
		ZhCheckBox->SetIsChecked(ECheckBoxState::Checked);
		break;
	}

	MuSlider->SetValue(SlAiDataHandle::Get()->MusicVolume);
	SoSlider->SetValue(SlAiDataHandle::Get()->SoundVolume);

	MuTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt
	(SlAiDataHandle::Get()->MusicVolume * 100)) + FString("%")));
	SoTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt
	(SlAiDataHandle::Get()->SoundVolume * 100)) + FString("%")));
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION


void SSlAiGameOptionWidget::ZhCheckBoxStateChanged(ECheckBoxState NewState)
{
	//�������Ŀ�ѡ��
	EnCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
	ZhCheckBox->SetIsChecked(ECheckBoxState::Checked);
	//�������ݿ�����ת��Ϊ����
	//SlAiDataHandle::Get()->ChangeLocalizationCulture(ECultureTeam::ZH);
	ChangeCulture.ExecuteIfBound(ECultureTeam::ZH);
}
void SSlAiGameOptionWidget::EnCheckBoxStateChanged(ECheckBoxState NewState)
{
	//����Ӣ�Ŀ�ѡ��
	EnCheckBox->SetIsChecked(ECheckBoxState::Checked);
	ZhCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
	//�������ݿ�����ת��ΪӢ��
	//SlAiDataHandle::Get()->ChangeLocalizationCulture(ECultureTeam::EN);
	ChangeCulture.ExecuteIfBound(ECultureTeam::EN);
}
void SSlAiGameOptionWidget::MusicSliderChanged(float value)
{
	//��ʾ�����ٷֱ�
	MuTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(value * 100)) + FString("%")));
	//�޸�����
	//SlAiDataHandle::Get()->ResetMenuVolume(value, -1.0f);
	ChangeVolume.ExecuteIfBound(value, -1.0f);
}
void SSlAiGameOptionWidget::SoundSliderChanged(float value)
{
	//��ʾ��Ч�ٷֱ�
	SoTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(value * 100)) + FString("%")));
	//�޸�����
	//SlAiDataHandle::Get()->ResetMenuVolume(-1.0f, value);
	ChangeVolume.ExecuteIfBound(-1.0f, value);
}