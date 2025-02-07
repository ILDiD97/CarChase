// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "Player/VRHandControllerComponent.h"
#include "CarChasePawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UChaosWheeledVehicleMovementComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateVehicle, Log, All);

/**
 *  Vehicle Pawn class
 *  Handles common functionality for all vehicle types,
 *  including input handling and camera management.
 *  
 *  Specific vehicle configurations are handled in subclasses.
 */
UCLASS(abstract)
class ACarChasePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

protected:
	/** Spring Arm for the front camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* FrontSpringArm;
	
	/** Front Camera component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FrontCamera;

	/** Spring Arm for the back camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* BackSpringArm;

	/** Back Camera component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* BackCamera;

	/** Cast pointer to the Chaos Vehicle movement component */
	TObjectPtr<UChaosWheeledVehicleMovementComponent> ChaosVehicleMovement;

	/** Steering Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SteeringAction;

	/** Throttle Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ThrottleAction;

	/** Brake Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* BrakeAction;

	/** Handbrake Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* HandbrakeAction;

	/** Look Around Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAroundAction;

	/** Toggle Camera Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ToggleCameraAction;

	/** Reset Vehicle Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ResetVehicleAction;

	/** Keeps track of which camera is active */
	bool bFrontCameraActive = false;

public:
	ACarChasePawn();

	// Begin Pawn interface

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	// End Pawn interface

	// Begin Actor interface

	virtual void Tick(float Delta) override;

	// End Actor interface

protected:

	/** Handles steering input */
	virtual void Steering(const FInputActionValue& Value);

	/** Handles throttle input */
	virtual void Throttle(const FInputActionValue& Value);

	/** Handles brake input */
	virtual void Brake(const FInputActionValue& Value);

	/** Handles brake start/stop inputs */
	virtual void StartBrake(const FInputActionValue& Value);
	virtual void StopBrake(const FInputActionValue& Value);

	/** Handles handbrake start/stop inputs */
	virtual void StartHandbrake(const FInputActionValue& Value);
	virtual void StopHandbrake(const FInputActionValue& Value);

	/** Handles look around input */
	virtual void LookAround(const FInputActionValue& Value);

	/** Handles toggle camera input */
	virtual void ToggleCamera(const FInputActionValue& Value);

	/** Handles reset vehicle input */
	virtual void ResetVehicle(const FInputActionValue& Value);

	/** Called when the brake lights are turned on or off */
	UFUNCTION(BlueprintImplementableEvent, Category="Vehicle")
	void BrakeLights(bool bBraking);

public:
	/** Returns the front spring arm subobject */
	FORCEINLINE USpringArmComponent* GetFrontSpringArm() const { return FrontSpringArm; }
	/** Returns the front camera subobject */
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FrontCamera; }
	/** Returns the back spring arm subobject */
	FORCEINLINE USpringArmComponent* GetBackSpringArm() const { return BackSpringArm; }
	/** Returns the back camera subobject */
	FORCEINLINE UCameraComponent* GetBackCamera() const { return BackCamera; }
	/** Returns the cast Chaos Vehicle Movement subobject */
	FORCEINLINE const TObjectPtr<UChaosWheeledVehicleMovementComponent>& GetChaosVehicleMovement() const { return ChaosVehicleMovement; }

	//Custom
	// UPROPERTY(VisibleAnywhere, Category = "VR")
	// USceneComponent* VROrigin;
	//
	// UPROPERTY(VisibleAnywhere, Category = "VR")
	// UVRHandControllerComponent* LeftHandController;
	//
	// UPROPERTY(VisibleAnywhere, Category = "VR")
	// UVRHandControllerComponent* RightHandController;
	//
	// // Camera per la visuale VR
	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VR")
	// UCameraComponent* FirstPersonCamera;
	//
	// // Stato di afferramento del volante
	// UPROPERTY(VisibleAnywhere, Category = "VR")
	// bool bIsGrabbingWheel = false;
	//
	// UPROPERTY(VisibleAnywhere, Category = "VR")
	// bool bIsUsingRightHand = true;  // Specifica quale mano sta afferrando
	//
	// // Rotazione iniziale della mano e del volante
	// UPROPERTY(VisibleAnywhere, Category = "VR")
	// FQuat InitialHandRotation;
	//
	// UPROPERTY(VisibleAnywhere, Category = "VR")
	// FQuat InitialWheelRotation;

	// Funzione per ottenere la rotazione corrente del controller VR attivo
	// UFUNCTION(BlueprintCallable)
	// FQuat GetControllerRotation(bool bIsRightHand) const;
	
	// Funzioni per gestire l'interazione con il volante
	// UPROPERTY(BlueprintCallable)
	// void GrabWheel(bool bUseRightHand);
	//
	// UPROPERTY(BlueprintCallable)
	// void ReleaseWheel(bool bUseRightHand);
	//
	// UPROPERTY(BlueprintCallable)
	// void UpdateSteeringWheelRotation();
	//
	// UPROPERTY(BlueprintCallable)
	// void ReturnSteeringWheelToCenter(float DeltaTime);
	
};
