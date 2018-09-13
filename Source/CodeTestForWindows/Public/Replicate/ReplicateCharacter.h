// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ReplicateCharacter.generated.h"

UCLASS()
class CODETESTFORWINDOWS_API AReplicateCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AReplicateCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	/**
	* @param RealViewer - is the "controlling net object" associated with the client for which network relevancy is being checked (typically player controller)
	* @param ViewTarget - is the Actor being used as the point of view for the RealViewer
	* @param SrcLocation - is the viewing location
	*
	* @return bool - true if this actor is network relevant to the client associated with RealViewer
	*/
	/*重写父类的函数 该函数可以判断观察者 即为viewtarget*/
	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;
	/*重写基类函数，同步变量 */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	/*ROLE_AutonomousProxy的角色调用，ROLE_Authority的角色执行 实现体_Implementation在cpp*/
	UFUNCTION(Reliable, Server, WithValidation)
		void SeverCollectPickups(float value);
	UFUNCTION(BlueprintCallable, Category = "Pickups")
		void CollectPickups(float value);
	/*NotiyVarbleTest 改变的回调函数(NotiyVarbleTest 改变则调用)*/
	UFUNCTION()
		void Rep_Func();

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = Rep_Func)
		float NotiyVarbleTest;

	UPROPERTY(BlueprintReadOnly, Replicated)
		float ReplicateVar;
	UFUNCTION(BlueprintCallable)
		float GetReplicateVar();
//ROLE_Authority的角色调用，所有的客户端的ROLE_AutonomousProxy的角色执行,实现体_Implementation在cpp
	/*UFUNCTION(BlueprintCallable,Client,Unreliable)
		void ClientRPCFunction();*/  /*没什么用处*/




	//OLE_Authority的角色调用并执行 所有的客户端的ROLE_AutonomousProxy,或者 ROLE_SimulatedProxy 的角色执行，实现体_Implementation在cpp
	UFUNCTION(NetMulticast, Reliable)
		void NetMulticastFunction();



	// 网络复制是 服务器和客户端都一个一模一样的物体 所以客户端发生什么服务器发生什么
	//（除了外界输入等情况 在客户端发生输入服务器没有发生输入） 只是物体的角色的属性不同 
	//即 是ROLE_None，ROLE_SimulatedProxy，ROLE_AutonomousProxy，ROLE_Authority，还是ROLE_MAX
	/*网络同步服务器上是ROLE_Authority即拥有与绝对控制权 客户端是ROLE_SimulatedProxy（非玩家角色）无法调用rpc只能被动接受复制的信息被动同步无法修改server上的物体的属性
		玩家角色是ROLE_AutonomousProxy 不仅有ROLE_SimulatedProxy的网络复制功能 可以利用 rpc的宏 server 修改server上物体的属性 同样server也可以利用client修改client上物体的属性*/
	//RPC函数的实现函数名末尾加_Impementation


	//OLE_NONE表示这个对象不扮演网络角色，不参与同步
	//ROLE_None,

	/*ROLE_SimulatedProxy表示它是一个远程机器上的一个复制品，它没有权利来改变一个对象的状态，也不能调用RPC（现在先把RPC理解为下命令让别人去执行）。
		无法使用server（Server函数就是ROLE_AutonomousProxy的角色调用，ROLE_Authority的角色执行） Client（Client函数就是ROLE_Authority的角色调用，ROLE_AutonomousProxy的角色执行）,NetMulticast,等rpc宏，只能被动接受同步信息 */
	//	ROLE_SimulatedProxy,

	//	表示它既可以完成ROLE_SimulatedProxy的工作（做一个复制品），又可以通过RPC来修改真正Actor的状态。
	//	ROLE_AutonomousProxy,
	//	/** Authoritative control over the actor. */
	//	ROLE_Authority,
	//	ROLE_MAX,

	// 一般玩家Player是ROLE_AutonomousProxy（可调用rpc） 其余的是ROLE_SimulatedProxy（只有复制功能） 
};
