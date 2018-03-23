// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyHUD.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Engine/PostProcessVolume.h"
#include "Runtime/Engine/Classes/Matinee/MatineeActor.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEST2_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
		AMyPlayerController();
		void SetShowHUD(bool);
		void SetObjList(TArray<AActor*>);
		void SetFrameNum(int32);

		AMyHUD* HUDPtr;
		
protected: 
	virtual void BeginPlay() override;

private:

	TArray<AActor*> Objects;
	
};
