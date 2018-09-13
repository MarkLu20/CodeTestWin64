// Fill out your copyright notice in the Description page of Project Settings.

#include "TCPObject.h"
#include <string>
//using namespace std;



UTCPObject::UTCPObject(const FObjectInitializer &ObjectInitializer):UObject(ObjectInitializer)
{

}

bool UTCPObject::StartTCPReceive(const FString & YourChosenSocketName, const FString & IP, const int32 ThePort)
{
	TSharedRef<FInternetAddr> TargetAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	FIPv4Address Addr;
	FIPv4Address::Parse(IP,Addr);
	int UiIp = (127 << 24) | 0 | 0 | 1;
	TargetAddress->SetIp(UiIp);
	FIPv4Endpoint Ipadd(TargetAddress);
	ListenSocket = FTcpSocketBuilder(TEXT("FTcpMessageTransport.RemoteConnection"));
	bool Succ = ListenSocket->Connect(Ipadd.ToInternetAddr().Get());
	/*if (ListenSocket&&Succ) {  }
	{

	}*/
	return Succ;
}

FString UTCPObject::StringFromBinaryArray(TArray<uint8> BinaryArray)
{   
    std::string cstr(reinterpret_cast<const char*>(BinaryArray.GetData()),BinaryArray.Num());
	FString FrameAsString = UTF8_TO_TCHAR(cstr.c_str());//cstr.c_str();
	return FrameAsString;
}

void UTCPObject::TCPSocketListener()
{
	if (ListenSocket==nullptr)
	{
		return;
	}
	TArray<uint8> ReceiveData;
	uint32 Size;
	while (ListenSocket->HasPendingData(Size))
	{
		ReceiveData.Init(FMath::Min<uint32>(Size,65507u),Size);
		int32 Read = 0;
		ListenSocket->Recv(ReceiveData.GetData(),ReceiveData.Num(),Read);

	}
	if (ReceiveData.Num()<=0)
	{
		return;
	}
	FString ReceivedUE4String = StringFromBinaryArray(ReceiveData);
	ReceiveDataEvent.Broadcast(ReceivedUE4String);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *ReceivedUE4String);
}

void UTCPObject::TCPSend(FString Message)
{

	TCHAR *SerializedChar = Message.GetCharArray().GetData();
	int32 Size = FCString::Strlen(SerializedChar);
	int32 Sent = 0;
	uint8 *ResultChars = (uint8*)TCHAR_TO_UTF8(SerializedChar);
	if (!ListenSocket->Send(ResultChars, Size, Sent)) {};
	{

	}
}

void UTCPObject::ListenerFunction()
{
	FReceiveThread *thread;
	thread = new FReceiveThread(this);
	thread->CreateThread(thread);
	delete thread;
	thread = nullptr;
	
}

uint32 FReceiveThread::Run()
{
	Object->TCPSocketListener();
	return 0;
}

void FReceiveThread::CreateThread(FReceiveThread * Thread)
{
	ManageThread = FRunnableThread::Create(Thread, TEXT("ReceiveThread"));
}
