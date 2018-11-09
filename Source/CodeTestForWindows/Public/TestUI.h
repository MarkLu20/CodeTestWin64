// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestUI.generated.h"

/**
 * 
 */
UCLASS()
class CODETESTFORWINDOWS_API UTestUI : public UUserWidget
{
	GENERATED_BODY()
	
	public:
		UTestUI(const FObjectInitializer &ObjectInitializer);
	
			

	



		virtual bool Initialize() override;

protected:
	virtual void NativeConstruct() override;
private:
	class UButton *TestButton ;
};
