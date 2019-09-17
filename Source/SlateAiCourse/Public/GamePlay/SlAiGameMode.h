﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SlAiGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SLATEAICOURSE_API ASlAiGameMode : public AGameModeBase
{
	GENERATED_BODY()

	ASlAiGameMode();
	//重写帧函数
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
};
