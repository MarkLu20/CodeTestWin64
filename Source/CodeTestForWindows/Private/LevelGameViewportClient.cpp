// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelGameViewportClient.h"
#include "Engine.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Slider.h"
#include "MainUserWidget.h"
#include "TestUI.h"


ULevelGameViewportClient::ULevelGameViewportClient()
{

}

void ULevelGameViewportClient::BeginDestroy()
{
	Super::BeginDestroy();

}

void ULevelGameViewportClient::AddViewportWidgetContent(TSharedRef<class SWidget> ViewportContent, const int32 ZOrder /*= 0*/)
{
	
}

void ULevelGameViewportClient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ULevelGameViewportClient::Init(struct FWorldContext& WorldContext, UGameInstance* OwningGameInstance, bool bCreateNewAudioDevice /*= true*/)
{
	Super::Init(WorldContext, OwningGameInstance, bCreateNewAudioDevice);
	/*StartingWidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("WidgetBlueprint'/Game/TestUI.TestUI_C'"));
	if (StartingWidgetClass != nullptr)
	{
		UWorld *world = GetWorld();
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), StartingWidgetClass);
		CurrentWidget->AddToViewport();
	}*/
	//TSharedPtr<SSlider> TestSlider = StaticCastSharedPtr<SSlider>(CurrentWidget->GetSlateWidgetFromName(FName("SliderTest"))) ;
	//TestSlider->SetValue(0.5f);
	//UTextBlock *Text = Cast<UTextBlock>(CurrentWidget->GetWidgetFromName(FName("TestText")));
	
	 //FText testtext= Text->TextDelegate.Execute();

	 FString Teststr;
	  //test= MakeShareable(TestSlider);
	 //test->SetValue(0.54f);

}

void ULevelGameViewportClient::BindText(FText text)
{

}
