// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenFireChatAPI.h"
#ifndef XMPPMODULE__H__
#define XMPPMODULE__H__
#include "Runtime/Online/XMPP/Public/XmppModule.h"
#include "Engine.h"
#include "PrivateChat.h"
#include "MucChat.h"
#include "ModuleManager.h"
#endif


//UOpenFireChatAPI *UOpenFireChatAPI::OpenFireInstance = nullptr;
UOpenFireChatAPI::UOpenFireChatAPI(const FObjectInitializer &ObjectInitializer):UObject(ObjectInitializer)
{

	XmppModule = &FXmppModule::Get();
	
	

	
	
	
	
	
}

UOpenFireChatAPI::~UOpenFireChatAPI()
{
	JoinedRoomArray.Empty();
}

//UOpenFireChatAPI * UOpenFireChatAPI::GetOpenFireInstance()
//{
//	if (OpenFireInstance ==nullptr)
//	{
//		OpenFireInstance = NewObject<UOpenFireChatAPI>();
//
//		OpenFireInstance->AddToRoot();
//	}
//	
//	 return OpenFireInstance;
//}

void UOpenFireChatAPI::Login(FString ServerAddr, int32 ServerPort,bool bUseSSL,bool bUsePlainTextAuth,float PingInterval,float PingTimeOut,int32 MaxPingRetries,bool bPrivateChatFriendsOnly, const FString  &UserID, const FString &Auth)
{   
	PrivateChat = GetDefault<UPrivateChat>();
	MucChat = GetDefault<UMucChat>();
	OpenFireInstance = GetDefault<UOpenFireChatAPI>();
	TSharedRef<IXmppConnection> XmppConnection = XmppModule->CreateConnection(UserID);
	xmppConnectionPtr = XmppConnection->AsShared();
	PrivateChatPtr = xmppConnectionPtr->PrivateChat();
	XmppConnection->OnLoginComplete().AddUObject(this, &UOpenFireChatAPI::OnXmppLoginComplete);
	OpenFireInstance->JoinRoomDel.AddUObject(this,&UOpenFireChatAPI::JoinRoomCall);
	XmppPresencePtr = xmppConnectionPtr->Presence();
	FXmppServer xmppserver;
	xmppserver.ServerAddr = ServerAddr;
	xmppserver.ServerPort = ServerPort;
	xmppserver.bUseSSL = bUseSSL;
	xmppserver.bUsePlainTextAuth = bUsePlainTextAuth;
	xmppserver.PingTimeout = PingTimeOut;
	xmppserver.PingInterval = PingInterval;
	xmppserver.bPrivateChatFriendsOnly = bPrivateChatFriendsOnly;
	xmppserver.Domain = "192.168.2.200";
	xmppConnectionPtr->SetServer(xmppserver);
	xmppConnectionPtr->Login(UserID,Auth);
	OpenFireInstance->GetXmpptr.Broadcast(PrivateChatPtr);
	
	
	
}

void UOpenFireChatAPI::OnXmppLoginComplete(const FXmppUserJid &UserJid, bool bWasSuccess, const FString &error)
{
	
	FXmppUserPresence Presence= XmppPresencePtr->GetPresence();
	Presence.Status = EXmppPresenceStatus::Online;
	XmppPresencePtr->UpdatePresence(Presence);
	
}

void UOpenFireChatAPI::RemoveConnection()
{
	if (xmppConnectionPtr.IsValid())
	{
		xmppConnectionPtr->Logout();
		XmppModule->RemoveConnection(xmppConnectionPtr.ToSharedRef());
	}
	
}

void UOpenFireChatAPI::SendPrivateMessage(const FString &FromUser, const FString &ToUser, const FString &Msg)
{
	PrivateChat->SendPrivateChatMessage(FromUser,ToUser,Msg);
}

void UOpenFireChatAPI::CreatePublicRoom(const FString &UserName, const FString &RoomId, const FString &Passworld)
{
	TSharedPtr<IXmppConnection> Connection = XmppModule->GetConnection(UserName);
	if (Connection->MultiUserChat().IsValid())
	{
		FXmppRoomConfig RoomConfig;
		RoomConfig.RoomName = RoomId;
		RoomConfig.bIsPrivate = false;
		RoomConfig.bIsPersistent = false;
		RoomConfig.Password = Passworld;
		Connection->MultiUserChat()->CreateRoom(RoomId,UserName,RoomConfig);
	}

}

void UOpenFireChatAPI::JoinRoom( const FString &Room)
{
	MucChat->JoinMucRoom(Room);
	
}

void UOpenFireChatAPI::RoomChat(const FString &UserName, const FString &RoomId, const FString &Body,const FString &ExtraInfo)
{
	TSharedPtr<IXmppConnection> Connection = XmppModule->GetConnection(UserName);
	MucChatDelegate = Connection->MultiUserChat()->OnRoomChatReceived().AddUObject(this,&UOpenFireChatAPI::OnRoomChatReceived);
	if (Connection->MultiUserChat().IsValid())
	{
		Connection->MultiUserChat()->SendChat(RoomId, Body, ExtraInfo);
	}
}

void UOpenFireChatAPI::OnRoomChatReceived(const TSharedRef<IXmppConnection>& Connection, const FXmppRoomId& RoomId, const FXmppUserJid& UserJid, const TSharedRef<FXmppChatMessage>& ChatMsg)
{
	
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Purple, FString( ChatMsg->Body ));
	Connection->MultiUserChat()->OnRoomChatReceived().Remove(MucChatDelegate);
}

void UOpenFireChatAPI::MucSendMessage(const FString& FromUser, const FString& Message, const FString &RoomName)
{
	MucChat->MucSendMessage(FromUser, Message, RoomName);
}

void UOpenFireChatAPI::JoinRoomCall(const FString &RoomName)
{
	JoinedRoomArray.Add(RoomName,RoomName);
	
}

