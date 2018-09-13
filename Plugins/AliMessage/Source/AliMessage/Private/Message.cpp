// Fill out your copyright notice in the Description page of Project Settings.

#include "Message.h"
#include "Http.h"
#include "Misc/SecureHash.h"
#include "Misc/Base64.h"
#include "Misc/Guid.h"
#include "Misc/DateTime.h"
#include "Json.h"

#define ALI_URL_STR											TEXT("https://dysmsapi.aliyuncs.com/")							//阿里云短消息服务器地址
#define ALI_PARAM_FORMAT								TEXT("JSON")																	
#define ALI_PARAM_SIGNTURE_METHOD			TEXT("HMAC-SHA1")														//加密格式
#define ALI_PARAM_SIGNTURE_VERSION			TEXT("1.0")																		
#define ALI_PARAM_ACTION								TEXT("SendSms")																
#define ALI_PARAM_VERSION							TEXT("2017-05-25")															
#define ALI_PARAM_REGIONID							TEXT("cn-hangzhou")														


void UMessage::init(FString AccessKeyId, FString AccessSecret, FString SignName, FString TemplateCode)
{
	m_AccessKeyId = AccessKeyId;
	m_AccessSecret = AccessSecret;
	m_AccessSecret += TEXT("&");
	m_SignName = SignName;
	m_TemplateCode = TemplateCode;
}

bool UMessage::getSmsString(FAliMessageRequiredParam RequiredParam, FString &resuStr)
{
	if (!RequiredParam.IsAliMessageRequiredParamValid())
	{
		UE_LOG(LogTemp, Error, TEXT("RequiredParam is not valid!"));
		return false;
	}

	//把int32验证码转化成Json格式的FString
	FString JsonStr;
	TSharedRef< TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR> > > JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR> >::Create(&JsonStr);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue(TEXT("code"), FString::FromInt(RequiredParam.SMSVerificationCode));
	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();

	//添加参数到smsMap，按照Key排序
	TMap<FString, FString> smsMap;
	smsMap.Add(TEXT("AccessKeyId"), m_AccessKeyId);
	smsMap.Add(TEXT("Action"), ALI_PARAM_ACTION);
	smsMap.Add(TEXT("Format"), ALI_PARAM_FORMAT);
	smsMap.Add(TEXT("OutId"), FString::FromInt(RequiredParam.OutId));
	smsMap.Add(TEXT("PhoneNumbers"), RequiredParam.phoneNum);
	smsMap.Add(TEXT("RegionId"), ALI_PARAM_REGIONID);
	smsMap.Add(TEXT("SignName"), m_SignName);
	smsMap.Add(TEXT("SignatureMethod"), ALI_PARAM_SIGNTURE_METHOD);
	smsMap.Add(TEXT("SignatureNonce"), createGuId());
	smsMap.Add(TEXT("SignatureVersion"), ALI_PARAM_SIGNTURE_VERSION);
	smsMap.Add(TEXT("TemplateCode"), m_TemplateCode);
	smsMap.Add(TEXT("TemplateParam"), JsonStr);
	smsMap.Add(TEXT("Timestamp"), getTims());
	smsMap.Add(TEXT("Version"), ALI_PARAM_VERSION);

	//遍历Map组合含有参数信息且URLEncode之后的FString并且替换特定字符，这个阿里文档要求的
	bool SetValue = false;
	FString sortedQueryString = "";
	for (auto& itr : smsMap)
	{
		if (SetValue)
		{
			sortedQueryString += "&";
		}
		SetValue = true;
		FString key = FGenericPlatformHttp::UrlEncode(itr.Key);
		FString value = FGenericPlatformHttp::UrlEncode(itr.Value);
		key = key.Replace(TEXT("+"), TEXT("%20"));
		key = key.Replace(TEXT("*"), TEXT("%2A"));
		key = key.Replace(TEXT("%7E"), TEXT("~"));
		sortedQueryString += key;
		sortedQueryString += TEXT("=");
		value = value.Replace(TEXT("+"), TEXT("%20"));
		value = value.Replace(TEXT("*"), TEXT("%2A"));
		value = value.Replace(TEXT("%7E"), TEXT("~"));
		sortedQueryString += value;
	}

	//HMAC和Base64加密
	FString strToSign = TEXT("");
	strToSign += TEXT("GET&");
	strToSign += FGenericPlatformHttp::UrlEncode(TEXT("/"));
	strToSign += TEXT("&");
	strToSign += FGenericPlatformHttp::UrlEncode(sortedQueryString);

	TCHAR* cKey = m_AccessSecret.GetCharArray().GetData();
	TCHAR* cContent = strToSign.GetCharArray().GetData();

	uint8 * buffSign = (uint8 *)FMemory::Malloc(sizeof(uint8) * 20);

	FSHA1::HMACBuffer(
		(unsigned char*)TCHAR_TO_ANSI(cKey),
		m_AccessSecret.Len(),
		(unsigned char*)TCHAR_TO_ANSI(cContent),
		strToSign.Len(),
		buffSign
	);

	FString sign = FBase64::Encode(buffSign, 20);
	FMemory::Free(buffSign);

	//组装最终需要发送的URL字符串-resuStr
	resuStr = ALI_URL_STR;
	resuStr += TEXT("?Signature=");
	FString temp = FGenericPlatformHttp::UrlEncode(sign);
	resuStr += temp;
	resuStr += TEXT("&");
	resuStr += sortedQueryString;

	return true;
}

bool UMessage::SendHttpRequest(FString URL)
{
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb(TEXT("GET"));
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UMessage::HttpCompleteCallback);
	return HttpRequest->ProcessRequest();
}

void UMessage::HttpCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FString MessageBody = "";

	// If HTTP fails client-side, this will still be called but with a NULL shared pointer!
	if (!Response.IsValid())
	{
		MessageBody = "{\"success\":\"Error: Unable to process HTTP Request!\"}";
	}
	else if (EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		MessageBody = Response->GetContentAsString();
	}
	else
	{
		MessageBody = FString::Printf(TEXT("{\"success\":\"HTTP Error: %d\"}"), Response->GetResponseCode());
	}
	OnMessageCallback.Broadcast(MessageBody);
}

FString UMessage::createGuId()
{
	return FGuid::NewGuid().ToString();
}

FString UMessage::getTims()
{
	FString Time;
	FDateTime DTime = FDateTime::Now();
	DTime -= (FTimespan(8, 0, 0));
	Time = DTime.ToString(TEXT("%Y-%m-%dT%H:%M:%SZ"));//%d-%02d-%02dT%02d:%02d:%02dZ
	return	Time;
}



