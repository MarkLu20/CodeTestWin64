// Fill out your copyright notice in the Description page of Project Settings.

#include "AliBlueprintFunctionLibrary.h"
#include "Http.h"



UMessage* UAliBlueprintFunctionLibrary::InitAliMessage(FAliMessageSystemParam SystemParam)
{
	if (!SystemParam.IsAliMessageSystemParamValid())
	{
		UE_LOG(LogTemp, Error, TEXT("SystemParam is not valid!"));
		return nullptr;
	}
	UMessage* AliMessage = NewObject<UMessage>();
	AliMessage->init(
		SystemParam.AccessKeyId,
		SystemParam.AccessSecret,
		SystemParam.SignName,
		SystemParam.TemplateCode
	);
	return AliMessage;
}

