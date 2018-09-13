// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

class FXmppModule;
class IXmppConnection;
class FXmppUserJid;
class IXmppMultiUserChat;
class FXmppRoomConfig;
class FXmppChatMember;
class FXmppRoomInfo;
class IXmppPresence;
class FXmppChatMessage;
class IXmppChat;
typedef FString FXmppRoomId;
typedef TSharedRef<FXmppChatMember, ESPMode::ThreadSafe> FXmppChatMemberRef;
typedef TSharedPtr<IXmppMultiUserChat, ESPMode::ThreadSafe> IXmppMultiUserChatPtr;
typedef TSharedPtr<IXmppPresence, ESPMode::ThreadSafe> IXmppPresencePtr;
typedef TSharedPtr<IXmppChat, ESPMode::ThreadSafe> IXmppChatPtr;
typedef TSharedPtr<class IHttpRequest> FHttpRequestPtr;
typedef TSharedPtr<class IHttpResponse, ESPMode::ThreadSafe> FHttpResponsePtr;
class OPENFIRECHAT_API XMPPType
{
public:
	XMPPType();
	~XMPPType();
};
