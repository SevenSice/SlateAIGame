// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Json.h"
#include "SlAiTypes.h"
/**
 * 
 */
class SLATEAICOURSE_API SlAiJsonHandle
{
public:
	SlAiJsonHandle();

	//�����浵����(������Ӧ����"Res/ConfigData/RecordData.json"�ļ������Json��ʽ)
	void RecordDataJsonRead(FString& Culture, float& MusicVolume, float& SoundVolume, TArray<FString>& RecordDataList);
private:
	//��ȡJson�ļ����ַ���
	bool LoadStringFromFile(const FString& FileName, const FString& RelativePath, FString& ResultString);

private:

	//�浵�ļ���
	FString RecordDataFileName;

	//���·��
	FString RelativePath;
};
