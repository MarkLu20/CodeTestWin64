// Fill out your copyright notice in the Description page of Project Settings.

#include "PrivateChat.h"
#include "OpenFireChatAPI.h"
#include "Runtime/Online/XMPP/Public/XmppChat.h"
#include "Engine.h"




UPrivateChat::UPrivateChat(const FObjectInitializer &ObjetInitializer):UObject(ObjetInitializer)
{
	OpenFireAPIInstance = GetDefault<UOpenFireChatAPI>();
	OpenFireAPIInstance->GetXmpptr.AddUObject(this,&UPrivateChat::GetXmppChatPtr);
	MucSym = FString(L"B82137CB4410705988D6FCB2C43EBBB4 8fec252d4D9E7F56009C8C9Da669ad9A");
	

}

UPrivateChat::~UPrivateChat()
{
	//JoindeRoom.Empty();
}



void UPrivateChat::SendPrivateChatMessage(const FString& FromUser, const FString& ToUser, const FString& Message)
{   
	FXmppChatMessage ChatMessage;
	ChatMessage.FromJid.Id = FromUser;
	ChatMessage.ToJid.Id = ToUser;
	ChatMessage.Body = Message;
	FDateTime DTime = FDateTime::Now();
	DTime -= (FTimespan(8, 0, 0));
	ChatMessage.Timestamp = DTime;
	XmppChatPtr->SendChat(ToUser, ChatMessage);

}

void UPrivateChat::InviteJoinRoom(const FString &FromUserName, const FString &ToUserName, const FString &RoomName)
{
	FXmppChatMessage ChatMessge;
	ChatMessge.FromJid.Id = FromUserName;
	ChatMessge.ToJid.Id = ToUserName;
	ChatMessge.Body = FString(L"jifasdf");
	XmppChatPtr->SendChat(FromUserName,ChatMessge);
}

void UPrivateChat::RequsetBeFriend(const FString &FromUser, const FString &ToUser, const FString)
{

}

void UPrivateChat::GetXmppChatPtr(const IXmppChatPtr& xmppChatPtr)
{
	XmppChatPtr = xmppChatPtr;
	XmppChatPtr->OnReceiveChat().AddUObject(this,&UPrivateChat::OnReceiveChat);
}

void UPrivateChat::OnReceiveChat(const TSharedRef<IXmppConnection>& Connection, const FXmppUserJid& FromJid, const TSharedRef<FXmppChatMessage>& ChatMsg)
{
	//OpenFireAPIInstance->fff
	    
	
		
		FString Msg;
		FString TypeS;
		FString Time;
		JoindeRoom.Empty();
		
		Time = ChatMsg->Timestamp.ToString(TEXT("%Y年%m月%d日 %H:%M:%S"));
		if (ChatMsg->Body.Contains(MucSym)&&!Connection->GetUserJid().Id.Equals(ChatMsg->ToJid.Id)&&OpenFireAPIInstance->JoinedRoomArray.Num()>0)
		{
			ChatMsg->Body.Split(MucSym, &Msg, &TypeS, ESearchCase::CaseSensitive);
			
			JoindeRoom = *(OpenFireAPIInstance->JoinedRoomArray.Find(TypeS));
			OpenFireAPIInstance->ReceiveMucChatMsg.Broadcast(ChatMsg->FromJid.Id, Msg, TypeS, Time);
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Purple, FString(ChatMsg->FromJid.Id + "/" + ChatMsg->ToJid.Id + "/" + Msg + "/" + "MucChat" + Time));
			
			
		
			
			
		}
		
		else if(!ChatMsg->Body.Contains(MucSym))
		{   
			OpenFireAPIInstance->ReceiveChatMsg.Broadcast(ChatMsg->FromJid.Id, ChatMsg->ToJid.Id, ChatMsg->Body, TypeS, Time);
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Purple, FString(ChatMsg->FromJid.Id + "/" + ChatMsg->ToJid.Id + "/" + ChatMsg->Body + "PrvateChat" "/" + Time));
		}
	
}
