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
	UStaticMeshComponent* SteeringWheel;
	
	UPROPERTY(VisibleAnywhere, Category = "Init")
	FRotator InitialRotation;
	
	UPROPERTY(VisibleAnywhere, Category = "Init")
	FRotator HeldRotation;

	UPROPERTY(EditAnywhere, Category = "WheelStats")
	UCurveFloat* BackToInit;
	
	UPROPERTY(VisibleAnywhere, Category = "WheelStats")
	float MaxSteeringAngle = 179.0f;
	
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
	virtual void Tick(float DeltaTime) override;
};
