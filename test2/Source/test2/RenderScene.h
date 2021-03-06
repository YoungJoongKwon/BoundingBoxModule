// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "MyPlayerController.h"
#include "RenderScene.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEST2_API URenderScene : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URenderScene();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
private:

	void SetStencilValue();

	UPROPERTY(EditAnywhere)
	TArray<AActor*> Objects;

	UPROPERTY(EditAnywhere)
		APostProcessVolume* Volume;

	UPROPERTY(EditAnywhere)
		AMatineeActor* Matinee;
	
	AMyPlayerController* MyPC;
	
	bool bShowHud;
	
	float LastTime;

	int32 Mode;

	int32 FrameNum;

	FString OriginalImage = "o";
	FString SegmentedImage = "s";
	FString BoundingBoxImage = "b";

};
