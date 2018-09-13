// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Message.generated.h"

typedef TSharedPtr<class IHttpRequest> FHttpRequestPtr;
typedef TSharedPtr<class IHttpResponse, ESPMode::ThreadSafe> FHttpResponsePtr;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAliMessageResponse, FString, ResponseString);
/**
* 消息服务系统参数（除固定参数）
*/
USTRUCT(BlueprintType, Category = "AliMessage")
struct ALIMESSAGE_API FAliMessageSystemParam
{
	GENERATED_USTRUCT_BODY();

	//用户头像-AccessKey管理-AccessKey管理-AccessKeyID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AliMessage")
		FString AccessKeyId;

	//创建AccessKeyID时一同下载的AccessSecret
	UPROPERTY(BlueprintReadWrite, Category = "AliMessage")
		FString AccessSecret;

	//消息服务-签名管理-签名名称，例：阿里云短信测试专用
	UPROPERTY(BlueprintReadWrite, Category = "AliMessage")
		FString SignName;

	//消息服务-模板管理-模板名称，例：SMS_128535144
	UPROPERTY(BlueprintReadWrite, Category = "AliMessage")
		FString TemplateCode;

	bool IsAliMessageSystemParamValid() const
	{
		return !AccessKeyId.IsEmpty() && !AccessSecret.IsEmpty() && !SignName.IsEmpty() && !TemplateCode.IsEmpty();
	}
};

/**
* 消息服务请求参数（除固定参数）
*/
USTRUCT(BlueprintType, Category = "AliMessage")
struct ALIMESSAGE_API FAliMessageRequiredParam
{
	GENERATED_USTRUCT_BODY();

	//接收短消息的11位电话号码
	UPROPERTY(BlueprintReadWrite, Category = "AliMessage")
	FString phoneNum;

	//应用或服务端生成的验证码
	UPROPERTY(BlueprintReadWrite, Category = "AliMessage")
	int32 SMSVerificationCode;

	//应用创建短消息发送流水号
	UPROPERTY(BlueprintReadWrite, Category = "AliMessage")
	int32 OutId;

	bool IsAliMessageRequiredParamValid() const
	{
		return !phoneNum.IsEmpty() && SMSVerificationCode != 0;
	}
};


/**
 * 
 */
UCLASS(BlueprintType, Category = "AliMessage")
class ALIMESSAGE_API UMessage : public UObject
{
	GENERATED_BODY()
	
public:
	void init(FString AccessKeyId, FString AccessSecret, FString SignName, FString TemplateCode);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "get Sms String", Keywords = "AliMessage getSmsString"), Category = "AliMessage")
	bool getSmsString(FAliMessageRequiredParam RequiredParam, FString &resuStr);

	UFUNCTION(BlueprintCallable, Category = "AliMessage")
	 bool SendHttpRequest(FString URL);

	void HttpCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	//Delegates
	UPROPERTY(BlueprintAssignable, Category = "AliMessage")
	FAliMessageResponse OnMessageCallback;

private:
	FString createGuId();

	FString getTims();

	UPROPERTY()
	FString m_AccessKeyId;

	UPROPERTY()
	FString m_AccessSecret;

	UPROPERTY()
	FString m_SignName;

	UPROPERTY()
	FString m_TemplateCode;
	
};
