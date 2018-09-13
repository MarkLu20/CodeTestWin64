// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PanelWidget.h"
#include "RichText.h"
#include "ITextDecorator.h"
#include "RTPanelWidget.generated.h"

/**
 * 
 */
UCLASS()
class CODETESTFORWINDOWS_API URTPanelWidget : public UWidget
{
	GENERATED_BODY()
	
public:
	URTPanelWidget(const FObjectInitializer &ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)
		FLinearColor Color;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)
		FSlateFontInfo Font;
	UPROPERTY(EditAnywhere, Instanced, Category = Decorators)
		class URichTextBlockDecorator* Decorators;
protected:
	


	virtual TSharedRef<SWidget> RebuildWidget() override;

public:
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	UFUNCTION(BlueprintCallable)
		void SetText(const FText& InTextAttr);


protected:
	TSharedPtr<SRichTextBlock> MyRichTextBlock;
};
