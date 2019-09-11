// Fill out your copyright notice in the Description page of Project Settings.


#include "SlAiJsonHandle.h"
#include "SlAiHelper.h"



SlAiJsonHandle::SlAiJsonHandle()
{
	RecordDataFileName = FString("RecordData.json");
	RelativePath = FString("Res/ConfigData/");
}

void SlAiJsonHandle::RecordDataJsonRead(FString& Culture, float& MusicVolume, float& SoundVolume, TArray<FString>& RecordDataList)
{
	FString JsonValue;
	LoadStringFromFile(RecordDataFileName,RelativePath,JsonValue);
	//��������JsonParsed�������������������
	TArray<TSharedPtr<FJsonValue>> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);
	//����
	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
	{
		//�����ɹ�
		//��ȡ����
		Culture = JsonParsed[0]->AsObject()->GetStringField(FString("Culture"));
		MusicVolume = JsonParsed[1]->AsObject()->GetNumberField(FString("MusicVolume"));
		SoundVolume = JsonParsed[2]->AsObject()->GetNumberField(FString("SoundVolume"));
		//��ȡ�浵���ݣ��浵����Ϊ "x:[1,2,3]",��Ҫ����������ܻ�ȡ������ֵ��
		TArray<TSharedPtr<FJsonValue>> RecordDataArray = JsonParsed[3]->AsObject()->GetArrayField(FString("RecordData")); 
		for (int i=0;i<RecordDataArray.Num();++i)
		{
			FString RecordDataName = RecordDataArray[i]->AsObject()->GetStringField(FString::FromInt(i));
			RecordDataList.Add(RecordDataName);
		}
	}
	else
	{
		//����ʧ��
		SlAiHelper::Debug(FString("Deserialize Failed"));
	}
}

void SlAiJsonHandle::UpdateRecordData(FString Culture, float MusicVolume, float SoundVolume, TArray<FString>* RecordDataList)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	TArray<TSharedPtr<FJsonValue>> BaseDataArray;

	TSharedPtr<FJsonObject> CultureObject = MakeShareable(new FJsonObject);
	CultureObject->SetStringField("Culture", Culture);
	TSharedPtr<FJsonValueObject> CultureValue = MakeShareable(new FJsonValueObject(CultureObject));

	TSharedPtr<FJsonObject> MusicVolumeObject = MakeShareable(new FJsonObject);
	MusicVolumeObject->SetNumberField("MusicVolume", MusicVolume);
	TSharedPtr<FJsonValueObject> MusicVolumeValue = MakeShareable(new FJsonValueObject(MusicVolumeObject));

	TSharedPtr<FJsonObject> SoundVolumeObject = MakeShareable(new FJsonObject);
	SoundVolumeObject->SetNumberField("SoundVolume", SoundVolume);
	TSharedPtr<FJsonValueObject> SoundVolumeValue = MakeShareable(new FJsonValueObject(SoundVolumeObject));

	TArray<TSharedPtr<FJsonValue>> RecordDataArray;

	for (int i = 0; i < RecordDataList->Num(); i++)
	{
		TSharedPtr<FJsonObject> RecordItem = MakeShareable(new FJsonObject);
		RecordItem->SetStringField(FString::FromInt(i), (*RecordDataList)[i]);
		TSharedPtr<FJsonValueObject>RecordDataValue = MakeShareable(new FJsonValueObject(RecordItem));
		RecordDataArray.Add(RecordDataValue);
	}
	//����������
	TSharedPtr<FJsonObject>RecordDataObject = MakeShareable(new FJsonObject);
	RecordDataObject->SetArrayField("RecordData", RecordDataArray);
	TSharedPtr<FJsonValueObject>RecordDataValue = MakeShareable(new FJsonValueObject(RecordDataObject));

	//����������飩
	BaseDataArray.Add(CultureValue);
	BaseDataArray.Add(MusicVolumeValue);
	BaseDataArray.Add(SoundVolumeValue);
	BaseDataArray.Add(RecordDataValue);

	//����������һ�����󣨼����һ������
	JsonObject->SetArrayField("T", BaseDataArray);

	//������ת���ַ���
	FString JsonStr;
	GetFStringInJsonData(JsonObject, JsonStr);

	SlAiHelper::Debug(FString("Origin Str : " + JsonStr), 60.f);

	//ȥ�������ַ�
	JsonStr.RemoveAt(0, 8);//��ֵ��Ҫ���㣨�ӵ�һ���ַ���ʼ��
	JsonStr.RemoveFromEnd(FString("}"));//remove���һ��"}"�ַ�

	SlAiHelper::Debug(FString("Final Str : " + JsonStr), 60.f);

	WriteFileWithJsonData(JsonStr, RelativePath, RecordDataFileName);
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

bool SlAiJsonHandle::GetFStringInJsonData(const TSharedPtr<FJsonObject>& JsonObj, FString& JsonStr)
{
	if (JsonObj.IsValid() && JsonObj->Values.Num() > 0)
	{
		TSharedRef<TJsonWriter<TCHAR>> JsonWrite = TJsonWriterFactory<TCHAR>::Create(&JsonStr);
		FJsonSerializer::Serialize(JsonObj.ToSharedRef(), JsonWrite);
		return true;
	}
	return false;
}

bool SlAiJsonHandle::WriteFileWithJsonData(const FString& JsonString, const FString& RelativePath, const FString& FileName)
{
	if (!JsonString.IsEmpty())
	{
		if (!FileName.IsEmpty())
		{
			FString AbsoPath = FPaths::GameContentDir() + RelativePath + FileName;
			//����
			if (FFileHelper::SaveStringToFile(JsonString, *AbsoPath))
			{
				return true;
			}
			else
			{
				SlAiHelper::Debug(FString("Save") + AbsoPath + FString("-->Failed"), 10.0f);
				return false;
			}
		}
	}
	return false;
}
