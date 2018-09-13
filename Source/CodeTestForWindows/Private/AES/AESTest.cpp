// Fill out your copyright notice in the Description page of Project Settings.
#include "AESTest.h"
#include "AES.h"
#include "string"
FString UAESTest::GetKeys(FString RawDataNum)
{
	return FString();
}
FString UAESTest::CreateKey(FString Keys)
{
	return FString();
}
FString UAESTest::CreateStaticKey()
{
	return FString();
}
FString UAESTest::FStringToBase64(FString RawData)
{
	return FString();
}
FString UAESTest::Base64ToFString(FString Base64Data, FString Keys)
{
	return FString();
}
FString UAESTest::Encrypt(FString Data, FString Keys)
{
	return FString();
}
FString UAESTest::Decrypt(FString Aes, FString Keys)
{
	return FString();
}
FString UAESTest::ConvertCode(FString CodeData, bool isEncryption)
{
	return FString();
}
UAESTest * UAESTest::GetAesInstance()
{
	return nullptr;
}
void UAESTest::EncryDataStatic(FString RawData, FString & Aes, int & RawDataUseLen)
{
}
void UAESTest::EncryptData(FString RawData, FString & AES, FString & Keys)
{
}
void UAESTest::DecryptData(FString Aes, FString Keys, FString & RawData)
{
}
FString UAESTest::Encrypt(FString Contents)
{
	//FString content = TEXT("eeeee");
	//std::string stdstr = "走啊资源啊afsadf";
	//FString fstr = UTF8_TO_TCHAR(stdstr.data());
	//Contents.Append(Sysmpol);
	//uint8* Blob = nullptr;
	//uint32 Size;
	//Size = Contents.Len();
	//Size = Size + (FAES::AESBlockSize - (Size % FAES::AESBlockSize));
	//Blob = new uint8[Size];
	//StringToBytes(Contents,Blob,Size);
	////加密
	//FAES::EncryptData(Blob,Size,TCHAR_TO_ANSI(*PrivateKey));
	//FString EncryptString = FString::FromHexBlob(Blob,Size);
	//return EncryptString;
	return FString();
}

FString UAESTest::Decrypt(FString Contents)
{
	return FString();
}
