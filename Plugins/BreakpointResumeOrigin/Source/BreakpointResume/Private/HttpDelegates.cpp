// Fill out your copyright notice in the Description page of Project Settings.

#include "HttpDelegates.h"



UHttpDelegates* UHttpDelegates::HttpDelegates = nullptr;
UHttpDelegates::UHttpDelegates()
{

}

UHttpDelegates* UHttpDelegates::Get()
{
	if (IsInGameThread() && HttpDelegates == nullptr)
	{
		HttpDelegates = NewObject<UHttpDelegates>();
		HttpDelegates->AddToRoot();
	}
	return HttpDelegates;
}
