// Fill out your copyright notice in the Description page of Project Settings.

#include "RTPanelWidget.h"
#include "RichTextBlockDecorator.h"


URTPanelWidget::URTPanelWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	
		
		Decorators = ObjectInitializer.CreateOptionalDefaultSubobject<URichTextBlockDecorator>(this, FName("DefaultDecorator"));
		
	

}
TSharedRef<SWidget> URTPanelWidget::RebuildWidget()
{
	MyRichTextBlock = SNew(SRichTextBlock);
	if (Font.HasValidFont()&&Decorators!=nullptr)
	{
		MyRichTextBlock->Decorator(Decorators->CreateDecorator(Font, Color));
	}
	
	return MyRichTextBlock.ToSharedRef();

}

void URTPanelWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	
	Super::ReleaseSlateResources(bReleaseChildren);
	MyRichTextBlock.Reset();
}

void URTPanelWidget::SetText(const FText& InTextAttr)
{
	MyRichTextBlock->SetText(InTextAttr);
}


