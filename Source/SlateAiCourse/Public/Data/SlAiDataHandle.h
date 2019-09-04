// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <SlAiTypes.h>

/**
 * 
 */

class SLATEAICOURSE_API SlAiDataHandle
{
public:
	SlAiDataHandle();

	static void Initialize();

	static TSharedPtr<SlAiDataHandle> Get();

	//�޸���Ӣ��
	void ChangeLocalizationCulture(ECultureTeam Culture);
	//�޸Ĳ˵�����
	void ResetMenuVolume(float MusicVol, float SoundVol);
public:
	//��ǰ����
	ECultureTeam CurrentCulture;
	//����
	float MusicVolume;
	float SoundVolume;
private:
	//��������
	static TSharedPtr<SlAiDataHandle> Create();

	//����Enum���ͻ�ȡ�ַ���
	template<typename TEnum>
	FString GetEnumValueAsString(const FString& Name, TEnum Value);

	//�����ַ�����ȡEnum��ֵ
	template<typename TEnum>
	TEnum GetEnumValueFromString(const FString& Name, FString Value);
private:

	static TSharedPtr<SlAiDataHandle> DataInstance;
};
