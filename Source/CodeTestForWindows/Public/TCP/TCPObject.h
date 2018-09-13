// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Runtime/Sockets/Public/Sockets.h"
#include "Runnable.h"
#include "RunnableThread.h"
#include "TCPObject.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FreceiveData,const FString&,Data);
UCLASS()
class CODETESTFORWINDOWS_API UTCPObject : public UObject
{
	GENERATED_BODY()

		UTCPObject(const FObjectInitializer &ObjectInitializer);
public:
	FSocket *ListenSocket;
	UFUNCTION(BlueprintCallable, Category = "TCP")
		bool StartTCPReceive(const FString &YourChosenSocketName,const FString &IP,const int32 ThePort);
	FString StringFromBinaryArray(TArray<uint8> BinaryArray);
	UFUNCTION(BlueprintCallable, Category = "TCP")
		void TCPSocketListener();
	UFUNCTION(BlueprintCallable, Category = "TCP")
		void TCPSend(FString Message);
	UPROPERTY(BlueprintAssignable, Category = "TCP")
		FreceiveData ReceiveDataEvent;
	UFUNCTION(BlueprintCallable, Category = "TCP")
		void ListenerFunction();
};
class FReceiveThread : public FRunnable
{

public:
	FRunnableThread *ManageThread;
	UTCPObject *Object = nullptr;
	FReceiveThread(UTCPObject *object)
	{
		Object = object;
	
	}
	~FReceiveThread()
	{
	
		ManageThread->WaitForCompletion();
		delete ManageThread;
		ManageThread = nullptr;
	
	}
	virtual uint32 Run() override;
	void CreateThread(FReceiveThread *Thread);



};