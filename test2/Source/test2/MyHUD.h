// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class TEST2_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
	void SetObjList(TArray<AActor*>);
	void SetShowHUD(bool DoShowHUD);
	void SetFrameNumber(int32);

private:

	//APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	//APlayerController* PlayerController = GetOwningPlayerController();

	bool showHUD = false;

	TArray<AActor*> Objects;

	const FVector BoundsPointMapping[8] =
	{
		FVector(1, 1, 1),
		FVector(1, 1, -1),
		FVector(1, -1, 1),
		FVector(1, -1, -1),
		FVector(-1, 1, 1),
		FVector(-1, 1, -1),
		FVector(-1, -1, 1),
		FVector(-1, -1, -1)
	};

	const FVector2D BoundsPointMapping2D[4] =
	{
		FVector2D(-1,-1),
		FVector2D(1,-1),
		FVector2D(-1,1),
		FVector2D(1,1)
	};

	FVector2D ViewportSize = FVector2D(1, 1);

	FString SaveDirectory = FString("C:/Users/user/Documents/BoundingBoxResult");
	//FString FileName = FString("BoundingBox_");
	FString FileName = FString("BoundingBox.txt");
	bool AllowOverwriting = false;
	
	int32 FrameNum = 0;


	
};
