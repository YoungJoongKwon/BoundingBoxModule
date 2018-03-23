// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"



AMyPlayerController::AMyPlayerController()
{

}

void AMyPlayerController::BeginPlay()
{
	HUDPtr = Cast<AMyHUD>(GetHUD());
	
	

}

void AMyPlayerController::SetShowHUD(bool doShowHUD) {

	HUDPtr->SetShowHUD(doShowHUD);
	UE_LOG(LogTemp, Warning, TEXT("MyPC: ShowHUD true\n"));
}

void AMyPlayerController::SetObjList(TArray<AActor*> DefaultObjList) {

	HUDPtr->SetObjList(DefaultObjList);
	UE_LOG(LogTemp, Warning, TEXT("MyPC: Set ObjList On.\n"));
}

void AMyPlayerController::SetFrameNum(int32 num)
{
	HUDPtr->SetFrameNumber(num);
}
