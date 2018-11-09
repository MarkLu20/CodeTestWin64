// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUserWidget.generated.h"

/**
 *
 */
UCLASS()
class CODETESTFORWINDOWS_API UMainUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UMainUserWidget(const FObjectInitializer& ObjectInitializer);
	virtual ~UMainUserWidget();

	UPROPERTY(Meta=(BindWidget))
	class UButton *TestButton = nullptr;
	UPROPERTY()
		class UTextBlock *TestText = nullptr;




	virtual bool Initialize() override;

protected:
	virtual void NativePreConstruct() override;


	virtual void NativeConstruct() override;


	virtual void NativeDestruct() override;
	UFUNCTION()
	void TestButtonClicked();

};
