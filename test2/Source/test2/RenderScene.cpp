// Fill out your copyright notice in the Description page of Project Settings.

#include "RenderScene.h"
#include "Runtime/Engine/Classes/Engine/World.h"
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

	MyPC = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	MyPC->SetObjList(Objects);
	MyPC->SetShowHUD(true);
	
}


// Called every frame
void URenderScene::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

