// Fill out your copyright notice in the Description page of Project Settings.

#include "TestObject.h"
#include "Engine.h"
#include "ScopeLock.h"
#include "LevelGameInstance.h"
UTestObject *UTestObject::TestInstance = nullptr;
UTestObject::UTestObject(const FObjectInitializer &ObjectInitializer):UObject(ObjectInitializer)
{
	//GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,FString("init TestObject"));
	
		//UE_LOG(LogTemp, Error, TEXT("TestUobject init"))
	
	

}
UTestObject * UTestObject::GetTestInstance()
{
	FCriticalSection SynchronizationObject;
	
  
	
	if (TestInstance == nullptr)
	{
		FScopeLock Lock(&SynchronizationObject);
		if (TestInstance == nullptr)
		{
			TestInstance = NewObject<UTestObject>();
			TestInstance->AddToRoot();
		}
	
    }
	
	return TestInstance;
}

void UTestObject::Test(int a, float b)
{
	//if (Cast<ULevelGameInstance>(gameinstance))
	//{
	//	//Cast<ULevelGameInstance>(gameinstance)->PassFunction<UTestObject>(TestInstance);
	//}
	float c = static_cast<float>(a);
	float d = c + b;
	UE_LOG(LogTemp, Error, TEXT("%f floattotal"), d);
}

FString UTestObject::DisPlayEnumName(EChatType ChatType)
{



	const FString Name = "EChatType";
	const UEnum* enumptr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
	if (enumptr == nullptr)
	{
		return TEXT("no find enum");
	}
	else
	{
		return enumptr->GetDisplayNameTextByValue((int64)ChatType).ToString();
	}
}
