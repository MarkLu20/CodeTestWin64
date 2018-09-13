// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ReflectionStudyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CODETESTFORWINDOWS_API AReflectionStudyGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, Category = "AReflectionStudyGameMode")
		float Score;

	UFUNCTION(BlueprintCallable, Category = "AReflectionStudyGameMode")
		void CallableFuncTest();

	UFUNCTION(BlueprintNativeEvent, Category = "AReflectionStudyGameMode")
		void NavtiveFuncTest(const FString &Test);

	UFUNCTION(BlueprintImplementableEvent, Category = "AReflectionStudyGameMode")
		void ImplementableFuncTest(const FString &Test);
	
	
};
