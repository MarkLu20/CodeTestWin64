// Fill out your copyright notice in the Description page of Project Settings.

#include "ReplicateCharacter.h"
#include "UnrealNetWork.h"
#include "Engine.h"


// Sets default values
AReplicateCharacter::AReplicateCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

}

// Called when the game starts or when spawned
void AReplicateCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AReplicateCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AReplicateCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



bool AReplicateCharacter::IsNetRelevantFor(const AActor * RealViewer, const AActor * ViewTarget, const FVector & SrcLocation) const
{
	return true;
}

void AReplicateCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AReplicateCharacter,NotiyVarbleTest);
	DOREPLIFETIME(AReplicateCharacter, ReplicateVar);

}

void AReplicateCharacter::CollectPickups(float value)
{
	if (this->Role == ENetRole::ROLE_AutonomousProxy)
	{
		SeverCollectPickups(value);
	}

}
void AReplicateCharacter::Rep_Func()
{
	GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,FString(TEXT("NotiyVarbleTest is changed")));
}
float AReplicateCharacter::GetReplicateVar()
{
	return ReplicateVar;
}
void AReplicateCharacter::NetMulticastFunction_Implementation()
{
	if (this->Role == ENetRole::ROLE_AutonomousProxy)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString(TEXT("NetMutiClient")));
	}
	if (this->Role == ENetRole::ROLE_Authority)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString(TEXT("NetMutiAuthority")));
	}
}
//void AReplicateCharacter::ClientRPCFunction_Implementation()
//{   
//	if (this->Role == ENetRole::ROLE_AutonomousProxy)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString(TEXT("ClientRPCFunction")));
//	}
//	
//}
bool AReplicateCharacter::SeverCollectPickups_Validate(float value)
{
	return true;
	
}
void AReplicateCharacter::SeverCollectPickups_Implementation(float value)
{
	
		NotiyVarbleTest = value;
		ReplicateVar = value;
	
	if (this->Role==ENetRole::ROLE_Authority)
	{
		NetMulticastFunction();
	}
}