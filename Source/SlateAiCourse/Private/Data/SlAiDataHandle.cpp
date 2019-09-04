// Fill out your copyright notice in the Description page of Project Settings.


#include "SlAiDataHandle.h"
#include "Internationalization.h"

TSharedPtr<SlAiDataHandle> SlAiDataHandle:: DataInstance = NULL;

SlAiDataHandle::SlAiDataHandle()
{
	//��ʼ��Ϊ����
	CurrentCulture = ECultureTeam::ZH;
	//��ʼ������
	MusicVolume = 0.5f;
	SoundVolume = 0.5f;
}

void SlAiDataHandle::Initialize()
{
	if (!DataInstance.IsValid())
	{
		DataInstance = Create();
	}
}

TSharedPtr<SlAiDataHandle> SlAiDataHandle::Get()
{
	Initialize();
	return DataInstance;
}

TSharedPtr<SlAiDataHandle> SlAiDataHandle::Create()
{
	TSharedRef<SlAiDataHandle> DataRef = MakeShareable(new SlAiDataHandle());
	return DataRef;
}

void SlAiDataHandle::ChangeLocalizationCulture(ECultureTeam Culture)
{
	switch (Culture)
	{
	case ECultureTeam::EN:
		FInternationalization::Get().SetCurrentCulture(TEXT("en"));
		break;
	case ECultureTeam::ZH:
		FInternationalization::Get().SetCurrentCulture(TEXT("zh"));
		break;
	}
	//�������Ը�ֵ
	CurrentCulture = Culture;
}

void SlAiDataHandle::ResetMenuVolume(float MusicVol, float SoundVol)
{
	//�ж��Ƿ�����ֵ����Ҫ�޸ģ�����С��0��ֵ���޸�
	if (MusicVol>0)
	{
		MusicVolume = MusicVol;
	}
	if (SoundVol>0)
	{
		SoundVolume = SoundVol;
	}
}

template<typename TEnum>
FString SlAiDataHandle::GetEnumValueAsString(const FString& Name, TEnum Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, Name, true);
	if (!EnumPtr)
	{
		return FString("In Valid");
	}
	return EnumPtr->GetEnumName((int32)Value);
}

template<typename TEnum>
TEnum SlAiDataHandle::GetEnumValueFromString(const FString& Name, FString Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, Name, true);
	if (!EnumPtr)
	{
		return EnumPtr(0);
	}
	return (TEnum)EnumPtr->GetIndexByName(FName(*FString(Value)));
}