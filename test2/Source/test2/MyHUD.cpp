// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "Runtime/Core/Public/HAL/PlatformFilemanager.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformFile.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Engine/Engine.h".

// GetOwningPlayerController()->

void AMyHUD::BeginPlay() {

	
	
}

void AMyHUD::DrawHUD() {
	
	if (showHUD) {

		FString OutputTXT = "";
		int32 ObjIndex = 0;

		for (AActor* object : Objects) {

			FString ObjName = *object->GetName();

			//UE_LOG(LogTemp, Warning, TEXT("Drawing object name: %s\n"), *ObjName);

			// Build 2D bounding box of actor in screen space
			//FBox2D ActorBox2D = FBox2D();

			//TODO: print out the origin and extent of this object in "txt" file format

			//Get Actor Bounds                
			const FBox EachActorBounds = object->GetComponentsBoundingBox(true); //All Components 
			
			//Center
			const FVector BoxCenter = EachActorBounds.GetCenter();

			//Extents
			const FVector BoxExtents = EachActorBounds.GetExtent();

			float minX = 0.0f, minY = 0.0f, maxX= 0.0f, maxY= 0.0f;

			for (uint8 BoundsPointItr = 0; BoundsPointItr < 8; BoundsPointItr++)
			{

				const FVector WorldLocation = BoxCenter + (BoundsPointMapping[BoundsPointItr] * BoxExtents);
				
				FVector2D ScreenLocation;
				GetWorld()->GetFirstPlayerController()->ProjectWorldLocationToScreen(WorldLocation, ScreenLocation, false);
				//ActorBox2D += FVector2D(ScreenLocation.X, ScreenLocation.Y);
				
				//UE_LOG(LogTemp, Warning, TEXT("screen location x is : %f\n"), ScreenLocation.X);
				//UE_LOG(LogTemp, Warning, TEXT("screen location y is : %f\n"), ScreenLocation.Y);

				if (BoundsPointItr == 0) {

					minX = ScreenLocation.X;
					maxX = ScreenLocation.X;

					minY = ScreenLocation.Y;
					maxY = ScreenLocation.Y;
				}
				else {
					if (ScreenLocation.X < minX) minX = ScreenLocation.X;
					if (ScreenLocation.X > maxX) maxX = ScreenLocation.X;
					if (ScreenLocation.Y < minY) minY = ScreenLocation.Y;
					if (ScreenLocation.Y > maxY) maxY = ScreenLocation.Y;
				}
			}

			float width = maxX - minX;
			float height = maxY - minY;

			FVector2D Center2D = FVector2D((minX+maxX)/2.0f, (minY+maxY)/2.0f);
			FVector2D Extent2D = FVector2D(width/2.0f, height/2.0f);

			bool ToRender = false;

			// check if this object is inside the camera view
			for (uint8 BoundsPointItr = 0; BoundsPointItr < 4; BoundsPointItr++) 
			{
				const FVector2D ScreenLocation = Center2D + (BoundsPointMapping2D[BoundsPointItr]*Extent2D);

			}


			// render bounding box
			DrawRect(FLinearColor(255, 0, 0, .30f), minX, minY, width, height);

			// index of object, origin x, origin y, width, height
			OutputTXT.AppendInt(ObjIndex);
			OutputTXT += (" " + FString::SanitizeFloat(minX) + " " + FString::SanitizeFloat(minY) + " " + FString::SanitizeFloat(width) + " " + FString::SanitizeFloat(height) + "\r\n");

			ObjIndex++;
		}

		// output to txt file
		
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

		if (PlatformFile.CreateDirectoryTree(*SaveDirectory))
		{
			// Get absolute file path
			FString AbsoluteFilePath = SaveDirectory + "/" + FileName;

			// Allow overwriting or file doesn't already exist
			if (AllowOverwriting || !FPaths::FileExists(*AbsoluteFilePath))
			{
				FFileHelper::SaveStringToFile(OutputTXT, *AbsoluteFilePath);
			}
		}
	}

}

void AMyHUD::SetObjList(TArray<AActor*> DefaultObjList) {
	
	Objects = DefaultObjList;

}

void AMyHUD::SetShowHUD(bool DoShowHUD) {
	
	showHUD = DoShowHUD;

}

void AMyHUD::SetFrameNumber(int32 num) {
	
	FrameNum = num;

}