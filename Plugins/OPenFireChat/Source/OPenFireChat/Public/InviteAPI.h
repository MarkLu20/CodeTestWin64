// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InviteAPI.generated.h"

/**
 * 
 */
UCLASS()
class OPENFIRECHAT_API UInviteAPI : public UObject
{
	GENERATED_BODY()
public:
		UInviteAPI(const FObjectInitializer &ObjectInitializer);
		~UInviteAPI();
		void InviteJoinRoom(const FString &UserName,const FString &RoomName);
		void RequsetBeFriend(const FString &FromUser,const FString &ToUser,const FString );
	
};
