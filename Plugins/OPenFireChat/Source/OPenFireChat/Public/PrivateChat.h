// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XMPPType.h"
#include "PrivateChat.generated.h"

/**
 * 
 */

UCLASS()
class OPENFIRECHAT_API UPrivateChat : public UObject
{
	GENERATED_BODY()
public:
	UPrivateChat(const FObjectInitializer &ObjetInitializer);
	~UPrivateChat();

	void SendPrivateChatMessage(const FString& FromUser,const FString& ToUser, const FString& Message);
	
	void InviteJoinRoom(const FString &FromUserName, const FString &ToUserName, const FString &RoomName);
	void RequsetBeFriend(const FString &FromUser, const FString &ToUser, const FString);
	IXmppChatPtr XmppChatPtr;
	TWeakObjectPtr< UOpenFireChatAPI> OpenFireAPIInstance;
private:
	FString MucSym;
	FString JoindeRoom;
	void GetXmppChatPtr(const IXmppChatPtr& xmppChatPtr);
	void OnReceiveChat(const TSharedRef<IXmppConnection>& Connection, const FXmppUserJid& FromJid, const TSharedRef<FXmppChatMessage>& ChatMsg);
	
	
};
