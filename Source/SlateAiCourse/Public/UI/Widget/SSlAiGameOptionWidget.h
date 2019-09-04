// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateTypes.h "
#include "SlAiTypes.h"
#include "Widgets/SCompoundWidget.h"



struct FSlAiMenuStyle;
class SCheckBox;
class STextBlock;
class SSlider;

//�޸���Ӣ��ί��
DECLARE_DELEGATE_OneParam(FChangeCulture, const ECultureTeam)
//�޸�����ί��
DECLARE_DELEGATE_TwoParams(FChangeVolume, const float, const float)

/**
 * 
 */
class SLATEAICOURSE_API SSlAiGameOptionWidget : public SCompoundWidget
{

public:
	SLATE_BEGIN_ARGS(SSlAiGameOptionWidget)
	{}
	SLATE_EVENT(FChangeCulture, ChangeCulture)
	SLATE_EVENT(FChangeVolume, ChangeVolume)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	//����CheckBox�¼�
	void ZhCheckBoxStateChanged(ECheckBoxState NewState);
	//Ӣ��CheckBox�¼�
	void EnCheckBoxStateChanged(ECheckBoxState NewState);

	//ͳһ������ʽ
	void StyleInitialized();
	//�����仯�¼�
	void MusicSliderChanged(float value);
	//��Ч�仯�¼�
	void SoundSliderChanged(float value);
private:
	//��ȡMenuStyle
	const FSlAiMenuStyle* MenuStyle;
	//��ȡCheckBoxָ��
	TSharedPtr<SCheckBox> EnCheckBox;
	TSharedPtr<SCheckBox> ZhCheckBox;
	//����������
	TSharedPtr<SSlider> MuSlider;//���ֻ�����
	TSharedPtr<SSlider> SoSlider;//��Ч������
	//�������ٷֱ�
	TSharedPtr<STextBlock> MuTextBlock;
	TSharedPtr<STextBlock> SoTextBlock;
	//ί�У���������
	FChangeCulture ChangeCulture;
	FChangeVolume ChangeVolume;
};
