// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "SRichTextBlock.h"
#include "SCompoundWidget.h"
/**
 * 
 */
class  RichText :public SCompoundWidget
{
public:
	
	SLATE_BEGIN_ARGS(RichText) {}
	SLATE_END_ARGS()
		void Construct(const FArguments &InArgs)
	{
		ChildSlot
			[

				SNew(SRichTextBlock)
                



			];
	}
};
