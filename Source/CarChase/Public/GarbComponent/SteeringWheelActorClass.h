// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SteeringWheelActorClass.generated.h"

UCLASS()
class CARCHASE_API ASteeringWheelActorClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASteeringWheelActorClass();

	UFUNCTION(BlueprintCallable)
	void RotateTowardsHand(const FVector& HandPosition);

	UFUNCTION(BlueprintCallable)
	void OnHeld();

	UFUNCTION(BlueprintCallable)
	void OnDeHeld();
	
	UPROPERTY(VisibleAnywhere, Category = "Held")
	bool IsHeld;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* SteeringWheel;

	UPROPERTY(VisibleAnywhere, Category = "WheelStats")
	FRotator InitialRotation;

	UPROPERTY(VisibleAnywhere, Category = "WheelStats")
	float MaxSteeringAngle = 90.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
