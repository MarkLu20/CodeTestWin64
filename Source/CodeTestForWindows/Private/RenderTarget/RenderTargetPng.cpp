// Fill out your copyright notice in the Description page of Project Settings.

#include "RenderTargetPng.h"
#include "Runtime/Engine/Public/ImageUtils.h"
#include "FileHelper.h"
URenderTargetPng *URenderTargetPng::TargetInstance = nullptr;

URenderTargetPng::URenderTargetPng(const FObjectInitializer &ObjectInitializer) :UObject(ObjectInitializer)
{
	Texture2D = LoadObject<UTextureRenderTarget2D>(nullptr,TEXT("TextureRenderTarget2D'/Game/RenderTarget/RenderTest.RenderTest'"));
}

URenderTargetPng * URenderTargetPng::GetRenderTarget()
{
	if (TargetInstance ==nullptr)
	{
		TargetInstance = NewObject<URenderTargetPng>();
		TargetInstance->AddToRoot();
	}
	return TargetInstance;
}

void URenderTargetPng::SaveTargetToPng(const FString &FileName)
{
	FString FilePath=FPaths::ProjectDir() / *FileName;
	FTextureRenderTargetResource *Resourece = Texture2D->GameThread_GetRenderTargetResource();
	FReadSurfaceDataFlags ReadPixelFlags(RCM_UNorm);
	TArray<FColor> OutBMP;
	OutBMP.AddUninitialized(Texture2D->GetSurfaceWidth()* Texture2D->GetSurfaceHeight());
	Resourece->ReadPixels(OutBMP,ReadPixelFlags);
	FIntPoint DestSize(Texture2D->GetSurfaceWidth(),Texture2D->GetSurfaceHeight());
	TArray<uint8> CompressBitmap;
	FImageUtils::CompressImageArray(DestSize.X,DestSize.Y,OutBMP,CompressBitmap);
	FFileHelper::SaveArrayToFile(CompressBitmap,*FilePath);
}
