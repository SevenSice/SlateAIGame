// Fill out your copyright notice in the Description page of Project Settings.


#include "SlAiJsonHandle.h"
#include "SlAiHelper.h"

SlAiJsonHandle::SlAiJsonHandle()
{
	RecordDataFileName = FString("RecordData.json");
	RelativePath = FString("Res/ConfigData/");
}

bool SlAiJsonHandle::LoadStringFromFile(const FString& FileName, const FString& RelativePath, FString& ResultString)
{
	if (!FileName.IsEmpty())
	{
		//��ȡ����·��
		FString AbsoPath = FPaths::GameContentDir() + RelativePath + FileName;
		//�ж��ļ��Ƿ����
		if (FPaths::FileExists(AbsoPath))
		{
			if (FFileHelper::LoadFileToString(ResultString, *AbsoPath))
			{
				return true;
			}
			else
			{
				//���ز��ɹ�
				SlAiHelper::Debug(FString("Load Error") + AbsoPath);
				return false;
			}
		}
		else
		{
			//����ļ�������
			SlAiHelper::Debug(FString("File is Exists ! ") + AbsoPath);
		}
	}
	return false;
}
