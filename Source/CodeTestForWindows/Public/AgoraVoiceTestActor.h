// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AgoraVoiceTestActor.generated.h"
class UAgoraVoiceManager;
UCLASS()
class CODETESTFORWINDOWS_API AAgoraVoiceTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAgoraVoiceTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	TWeakObjectPtr<class UWebSocketTest> testWeb;
	UAgoraVoiceManager *AvManager ;
	TWeakObjectPtr<UAgoraVoiceManager> Mangager;
	
public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	/** Does the thing. */
	UFUNCTION(BlueprintCallable, Category = Test)
		void DoThing();
	UFUNCTION(BlueprintCallable, Category = QuitGame)
		void CacheString(const FString &Content);
	UFUNCTION(BlueprintCallable, Category = QuitGame)
		const TArray<FString>& GetCacheString();
	
	bool SHA256(const FString &data,FSHA256Signature &Out);

};
void GTC(FString fasdfasdf);
