// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Message.h"
#include "AliBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ALIMESSAGE_API UAliBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "AliMessage")
	static UMessage* InitAliMessage(FAliMessageSystemParam SystemParam);
	
};
