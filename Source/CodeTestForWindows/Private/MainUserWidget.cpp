// Fill out your copyright notice in the Description page of Project Settings.

#include "MainUserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Engine.h"




UMainUserWidget::UMainUserWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}



UMainUserWidget::~UMainUserWidget()
{

}

bool UMainUserWidget::Initialize()
{
	//Super::Initialize();
	
	
	return true;
}

void UMainUserWidget::NativePreConstruct()
{
	
}
void UMainUserWidget::NativeConstruct()
{
	TestText = Cast<UTextBlock>(GetWidgetFromName(FName("SSS")));
	FLinearColor testColor(0.164567f, 1.0f, 0.0f, 1.0f);
	//TestButton->BackgroundColor = testColor;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString("NativePreConstruct"));
	//TestButton->OnClicked.AddDynamic(this, &UMainUserWidget::TestButtonClicked);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString("NativeConstruct"));
}

void UMainUserWidget::NativeDestruct()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString("NativeDestruct"));
}

void UMainUserWidget::TestButtonClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString("TestButtonClicked"));
}
