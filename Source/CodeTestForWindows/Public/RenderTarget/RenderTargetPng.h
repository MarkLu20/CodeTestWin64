// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Engine/Classes/Engine/TextureRenderTarget2D.h"
#include "RenderTargetPng.generated.h"


/**
 * 
 */
UCLASS()
class CODETESTFORWINDOWS_API URenderTargetPng : public UObject
{
	GENERATED_BODY()
	
public:
	URenderTargetPng(const FObjectInitializer &ObjectInitializer);
	UFUNCTION(BlueprintCallable, Category = RenderTarget)
	static URenderTargetPng *GetRenderTarget();
	UFUNCTION(BlueprintCallable,Category =RenderTarget)
	void SaveTargetToPng(const FString &FileName);
	UTextureRenderTarget2D *Texture2D;
private:
	static URenderTargetPng *TargetInstance;
	
};
