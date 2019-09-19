﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/SlAiPlayerAnim.h"
#include "SlAiThirdPlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class SLATEAICOURSE_API USlAiThirdPlayerAnim : public USlAiPlayerAnim
{
	GENERATED_BODY()
	
public:
	USlAiThirdPlayerAnim();

public:
	//重写更新属性方法
	virtual void UpdateParameter() override;
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		float Direction;
};
