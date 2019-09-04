// Fill out your copyright notice in the Description page of Project Settings.


#include "SlAiStyle.h"
#include "SlateGameResources.h"

TSharedPtr<FSlateStyleSet>SlAiStyle::SlAiStyleInstance = NULL;
void SlAiStyle::Initialize()
{
	if (!SlAiStyleInstance.IsValid())
	{
		SlAiStyleInstance = Create();
		//ע��
		FSlateStyleRegistry::RegisterSlateStyle(*SlAiStyleInstance);
	}
}

FName SlAiStyle::GetStyleSetName()
{ 
	static FName StyleSetName(TEXT("SlAiStyle"));

	return StyleSetName;
}
//��Ϸ����ʱ
void SlAiStyle::ShutDown()
{
	//ȡ��ע��
	FSlateStyleRegistry::UnRegisterSlateStyle(*SlAiStyleInstance);
	//ȷ����Ч
	ensure(SlAiStyleInstance.IsUnique());
	SlAiStyleInstance.Reset();
}

const ISlateStyle& SlAiStyle::Get()
{
	return *SlAiStyleInstance;
}

TSharedRef<class FSlateStyleSet> SlAiStyle::Create()
{
	TSharedRef<class FSlateStyleSet> StyleRef = FSlateGameResources::New(SlAiStyle::GetStyleSetName(), "/Game/UI/Style", "/Game/UI/Style");
	return StyleRef;
}
