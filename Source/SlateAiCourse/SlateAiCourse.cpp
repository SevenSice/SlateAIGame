// Fill out your copyright notice in the Description page of Project Settings.

#include "SlateAiCourse.h"
#include "Modules/ModuleManager.h"
#include "UI/Style/SlAiStyle.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FSlAiCourceModule, SlateAiCourse, "SlateAiCourse" );

void FSlAiCourceModule::StartupModule()
{
	//*��ʼ����ʽ
		//**���ص�ʱ����ȡ��ע��
	FSlateStyleRegistry::UnRegisterSlateStyle(SlAiStyle::GetStyleSetName());
	SlAiStyle::Initialize();
}

void FSlAiCourceModule::ShutdownModule()
{
	SlAiStyle::ShutDown();
}
