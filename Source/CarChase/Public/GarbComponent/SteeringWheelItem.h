// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GarbComponent/GrabItemComponent.h"
#include "SteeringWheelItem.generated.h"

/**
 * 
 */
UCLASS()
class CARCHASE_API ASteeringWheelItem : public AGrabItemComponent
{
	GENERATED_BODY()
	
public:
	ASteeringWheelItem();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* Pivot;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* SteeringWheel;
	
	UPROPERTY(EditAnywhere, Category = "Init")
	FRotator InitialRotation;
	
	// Ultima posizione del controller
	UPROPERTY(VisibleAnywhere, Category = "Init")
	FVector LastControllerPosition;

	// Sensibilità della rotazione
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR")
	float RotationSensitivity = 10.0f;
	
	UPROPERTY(VisibleAnywhere, Category = "Init")
	FVector InitialHandPosition;
	
	UPROPERTY(VisibleAnywhere, Category = "Init")
	FRotator HeldRotation;

	UPROPERTY(EditAnywhere, Category = "WheelStats")
	UCurveFloat* BackToInit;
	
	UPROPERTY(VisibleAnywhere, Category = "WheelStats")
	double MaxSteeringAngle = 179.0f;
	
protected:
	
	virtual void BeginPlay() override;
	
	virtual void OnGrip(UMotionControllerComponent* controller) override;
	
	virtual void OnLeave(UMotionControllerComponent* controller) override;
	
	virtual void OnAction() override;
	
	virtual void Action() override;

	UFUNCTION(BlueprintCallable)
	virtual void RotateTowardsHand();
	
	UFUNCTION(BlueprintCallable)
	virtual void RotateTowardsInit();

public:
	UFUNCTION(BlueprintCallable)
	float GetSteeringInput();

	virtual void Tick(float DeltaTime) override;
	
	virtual void GrabPoint(UMotionControllerComponent* controller, FVector position) override;
};
