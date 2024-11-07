// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CarChase/CarChasePawn.h"
#include "Camera/CameraComponent.h"
#include "VRCarChasePawn.generated.h"

/**
 * 
 */
UCLASS()
class CARCHASE_API AVRCarChasePawn : public ACarChasePawn
{
	GENERATED_BODY()
public:

	AVRCarChasePawn();
	
	UPROPERTY(VisibleAnywhere, Category = "VR")
	USceneComponent* VROrigin;
	
	UPROPERTY(VisibleAnywhere, Category = "VR")
	UVRHandControllerComponent* LeftHandController;
	
	UPROPERTY(VisibleAnywhere, Category = "VR")
	UVRHandControllerComponent* RightHandController;
	
	// Camera per la visuale VR
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VR")
	UCameraComponent* FirstPersonCamera;
	
	// Stato di afferramento del volante
	UPROPERTY(VisibleAnywhere, Category = "VR")
	bool bIsGrabbingWheel = false;
	
	UPROPERTY(VisibleAnywhere, Category = "VR")
	bool bIsUsingRightHand = true;  // Specifica quale mano sta afferrando
	
	// Rotazione iniziale della mano e del volante
	UPROPERTY(VisibleAnywhere, Category = "VR")
	FQuat InitialHandRotation;
	
	UPROPERTY(VisibleAnywhere, Category = "VR")
	FQuat InitialWheelRotation;
};
