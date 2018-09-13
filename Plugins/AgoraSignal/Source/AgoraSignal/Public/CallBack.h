// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "agora_sig.h"
#include "UObject/NoExportTypes.h"
#include "CallBack.generated.h"
using namespace agora_sdk_win;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSaveLog, FString, log, FString, path);
UCLASS(Blueprintable)
class AGORASIGNAL_API UCallBack : public UObject,public ICallBack
{
	GENERATED_BODY()
public :
	
	

	//TArray<FString> JoinedRoom;
	UCallBack(const FObjectInitializer &ObjectInitializer);
	~UCallBack();
	UFUNCTION(BlueprintCallable, Category = "AgoraCallBack")
		static UCallBack *GetCallBackInstance();
	UFUNCTION(BlueprintCallable, Category = "AgoraCallBack")
		void SaveLog();
	virtual void onReconnecting(uint32_t nretry) override;
	virtual void onReconnected(int fd) override;
	virtual void onLoginSuccess(uint32_t uid, int fd) override;
	virtual void onLogout(int ecode)override;
	virtual void onLoginFailed(int ecode) override;
	virtual void onChannelJoined(char const * channelID, size_t channelID_size) override;
	virtual void onChannelJoinFailed(char const * channelID, size_t channelID_size, int ecode) override;
	virtual void onChannelLeaved(char const * channelID, size_t channelID_size, int ecode) override;
	virtual void onChannelUserJoined(char const * account, size_t account_size, uint32_t uid) override;
	virtual void onChannelUserLeaved(char const * account, size_t account_size, uint32_t uid) override;
	virtual void onChannelUserList(int n, char** accounts, uint32_t* uids) override;
	virtual void onChannelQueryUserNumResult(char const * channelID, size_t channelID_size, int ecode, int num) override;
	virtual void onChannelQueryUserIsIn(char const * channelID, size_t channelID_size, char const * account, size_t account_size, int isIn) override;
	virtual void onChannelAttrUpdated(char const * channelID, size_t channelID_size, char const * name, size_t name_size, char const * value, size_t value_size, char const * type, size_t type_size)override;
	virtual void onInviteReceived(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size) override;
	virtual void onInviteReceivedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid) override;
	virtual void onInviteAcceptedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size) override;
	virtual void onInviteRefusedByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size) override;
	virtual void onInviteFailed(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, int ecode, char const * extra, size_t extra_size) override;
	virtual void onInviteEndByPeer(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * extra, size_t extra_size) override;
	virtual void onInviteEndByMyself(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid) override;
	virtual void onInviteMsg(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * msgType, size_t msgType_size, char const * msgData, size_t msgData_size, char const * extra, size_t extra_size)override;
	virtual void onMessageSendError(char const * messageID, size_t messageID_size, int ecode) override;
	virtual void onMessageSendProgress(char const * account, size_t account_size, char const * messageID, size_t messageID_size, char const * type, size_t type_size, char const * info, size_t info_size) override;
	virtual void onMessageSendSuccess(char const * messageID, size_t messageID_size) override;
	virtual void onMessageAppReceived(char const * msg, size_t msg_size) override;
	virtual void onMessageInstantReceive(char const * account, size_t account_size, uint32_t uid, char const * msg, size_t msg_size) override;
	virtual void onMessageChannelReceive(char const * channelID, size_t channelID_size, char const * account, size_t account_size, uint32_t uid, char const * msg, size_t msg_size)override;
	virtual void onLog(char const * txt, size_t txt_size) override;
	virtual void onInvokeRet(char const * callID, size_t callID_size, char const * err, size_t err_size, char const * resp, size_t resp_size) override;
	virtual void onMsg(char const * from, size_t from_size, char const * t, size_t t_size, char const * msg, size_t msg_size) override;
	virtual void onUserAttrResult(char const * account, size_t account_size, char const * name, size_t name_size, char const * value, size_t value_size) override;
	virtual void onUserAttrAllResult(char const * account, size_t account_size, char const * value, size_t value_size) override;
	virtual void onError(char const * name, size_t name_size, int ecode, char const * desc, size_t desc_size) override;
	virtual void onQueryUserStatusResult(char const * name, size_t name_size, char const * status, size_t status_size) override;
	virtual void onDbg(char const * a, size_t a_size, char const * b, size_t b_size)override;
	virtual void onBCCall_result(char const * reason, size_t reason_size, char const * json_ret, size_t json_ret_size, char const * callID, size_t callID_size) override;
	
private:
	class UUnrealSignal *SignalInstance;
	class UAgoraSDKManager *AgoraSDKManagerInstance;
	static UCallBack *CallBackInstance;

	
};
