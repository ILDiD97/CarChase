// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CarChase/CarChasePawn.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "InputTriggers.h"
#include "GarbComponent/SteeringWheelItem.h"
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

protected:
	
	virtual void Steering(const FInputActionValue& Value) override;
	
	virtual void Throttle(const FInputActionValue& Value) override;
	
	virtual void Brake(const FInputActionValue& Value) override;
	
	virtual void StartBrake(const FInputActionValue& Value) override;
	
	virtual void StopBrake(const FInputActionValue& Value) override;
	
	virtual void StartHandbrake(const FInputActionValue& Value) override;
	
	virtual void StopHandbrake(const FInputActionValue& Value) override;
	
	virtual void LookAround(const FInputActionValue& Value) override;
	
	virtual void ToggleCamera(const FInputActionValue& Value) override;
	
	virtual void ResetVehicle(const FInputActionValue& Value) override;

public:
	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	
	virtual void Tick(float Delta) override;

	UPROPERTY(VisibleAnywhere, Category = "VR")
	USceneComponent* VROrigin;
	
	UPROPERTY(VisibleAnywhere, Category = "VR")
	UVRHandControllerComponent* LeftHandController;
	
	UPROPERTY(VisibleAnywhere, Category = "VR")
	UVRHandControllerComponent* RightHandController;

	UPROPERTY(EditAnywhere, Category="SteeringWheel")
	TSubclassOf<ASteeringWheelItem> SteeringWheelClass;

	UPROPERTY(VisibleAnywhere, Category="SteeringWheel")
	ASteeringWheelItem* SteeringWheel;
	
	UPROPERTY(EditAnywhere, Category="SteeringWheel")
	UChildActorComponent* SteeringWheelComponent;

	UPROPERTY(VisibleAnywhere, Category = "Grab")
	AGrabItemComponent* GrabbedActor;
	
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
