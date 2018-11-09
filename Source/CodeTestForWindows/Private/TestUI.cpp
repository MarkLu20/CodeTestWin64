// Fill out your copyright notice in the Description page of Project Settings.

#include "TestUI.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Engine.h"



UTestUI::UTestUI(const FObjectInitializer &ObjectInitializer):Super(ObjectInitializer)
{
	TestButton = nullptr;
}

bool UTestUI::Initialize()
{
	Super::Initialize();
	return true;
}

void UTestUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	 if (UButton *btn= Cast<UButton>(GetWidgetFromName(FName("TestButton"))))
	 {
		 TestButton = btn;
	 }
	
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString("TestButton"));
}
