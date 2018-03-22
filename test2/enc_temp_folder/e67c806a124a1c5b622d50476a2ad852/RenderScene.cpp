// Fill out your copyright notice in the Description page of Project Settings.

#include "RenderScene.h"
#include "GameFramework/Actor.h"
#include "Engine/PostProcessVolume.h"
#include "Components/ActorComponent.h"
#include "Runtime/Core/Public/Math/Vector.h"
#include "Runtime/Engine/Public/UnrealClient.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"
#include "Runtime/Engine/Classes/Matinee/MatineeActor.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "MyPlayerController.h"

// Sets default values for this component's properties
URenderScene::URenderScene()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URenderScene::BeginPlay()
{
	Super::BeginPlay();

	// controlling mode
	mode = -2; 

	// for camera move
	//Matinee->Pause();

	// for segmentation
	Volume->bUnbound = false;
	SetStencilValue(); 

	// for bounding box
	bShowHud = false;
	MyPC = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	MyPC->SetObjList(Objects);
	MyPC->SetShowHUD(bShowHud);
	
	LastTime = GetWorld()->GetTimeSeconds();

}


// Called every frame
void URenderScene::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	float CurrentTime = GetWorld()->GetTimeSeconds();

	/*
	if (CurrentTime - LastTime > 1.0f) {

		MyPC->SetShowHUD(bShowHud);
		bShowHud = !bShowHud;

		LastTime = CurrentTime;
	}
	*/

	
	//if (GetWorld()->GetTimeSeconds() - LastTime > 1.0f) {
	if (CurrentTime - LastTime > 1.0f) {

		if (mode == -2) {
			Matinee->Pause();
			mode = -1;
		}
		else if (mode == -1) {
			mode = 0;
		}
		else if (mode == 0) { // original mode

			
			Volume->bUnbound = false;
			FScreenshotRequest::RequestScreenshot("original", false, true);

			mode = 1;
			
		}
		else if (mode == 1) { // bounding box mode
			
			MyPC->SetShowHUD(true);
			FScreenshotRequest::RequestScreenshot("boundingbox", false, true);
			mode = 2;
			
			
		}
		else if (mode == 2) { // segmentation mode
			
			MyPC->SetShowHUD(false);
			Volume->bUnbound = true;
			
			FScreenshotRequest::RequestScreenshot("segmentation", false, true);
			
			mode = 3;
			
		}
		else if (mode == 3) { // play video
			
			Matinee->Play();
			mode = 4;
		}
		else if (mode == 4) {
			mode = 5;
		}
		else if (mode == 5) {
			Matinee->Pause();
			mode = 0;
		}



		LastTime = CurrentTime;
	}
	
}

void URenderScene::SetStencilValue()
{
	int32 i = 1;

	for (AActor* object : Objects) {

		AStaticMeshActor* a = Cast<AStaticMeshActor>(object);
		UStaticMeshComponent* b = a->GetStaticMeshComponent();

		b->SetRenderCustomDepth(true);
		b->SetCustomDepthStencilValue(i);
		i++;
	}
}

