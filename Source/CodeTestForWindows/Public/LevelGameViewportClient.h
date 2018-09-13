// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "LevelGameViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class CODETESTFORWINDOWS_API ULevelGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
	
	
	
	
public:
	virtual void BeginDestroy() override;


	virtual void AddViewportWidgetContent(TSharedRef<class SWidget> ViewportContent, const int32 ZOrder = 0) override;


	virtual void Tick(float DeltaTime) override;

};
