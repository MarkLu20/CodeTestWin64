// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "AESTest.generated.h"

/**
 *
 */
UCLASS()
class CODETESTFORWINDOWS_API UAESTest : public UObject
{
	GENERATED_BODY()
private:
	/*密钥 加密解密的密钥 加密和解密需要用同样的密钥（对称加密）*/
	/*需要32位以上字符*/
	static FString PrivateKey;
	/*切割字符串标识符 最后一个是空格*/
     FString Sysmpol;
	static UAESTest *AESInstance;
	/*获取时间戳和随机数*/
	FString GetKeys(FString RawDataNum);
	/*生成秘钥*/
	FString CreateKey(FString Keys);
	/*生成静态秘钥*/
	FString CreateStaticKey();
	/*转换FString到Base64//先转成Tarray<uint8>*/
	FString FStringToBase64(FString RawData);
	/*转换Base64到FString//先转成Tarray<uint8>*/
	FString Base64ToFString(FString Base64Data, FString Keys);
	FString Encrypt(FString Data, FString Keys);
	/*解密*/
	FString Decrypt(FString Aes, FString Keys);
	/*添加分隔符/使用分隔符获取源数据*/
	FString ConvertCode(FString CodeData, bool isEncryption);
public:
	/*获取单例*/
	UFUNCTION(BlueprintCallable, Category = AES)
		static UAESTest *GetAesInstance();
	/*静态加密*/
	UFUNCTION(BlueprintCallable)
		void EncryDataStatic(FString RawData,FString &Aes,int&RawDataUseLen);
	/*加密*/
	UFUNCTION(BlueprintCallable)
		void EncryptData(FString RawData,FString &AES,FString &Keys);
	/*解密*/
	UFUNCTION(BlueprintCallable)
		void DecryptData(FString Aes,FString Keys,FString &RawData);
	UFUNCTION(BlueprintCallable)
		static FString Encrypt(FString Contents);
	FString Decrypt(FString Contents);
	FString teststr = "eeeeee";

};
