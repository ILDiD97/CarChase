// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MotionControllerComponent.h"
#include "GameFramework/Actor.h"
#include "GrabItemComponent.generated.h"

UENUM(Blueprintable)
enum class EGrabType : uint8
{
	None UMETA(DisplayName = "None"),
	ToGrip UMETA(DisplayName = "ToGrip"),
	GripTo UMETA(DisplayName = "GripTo"),
	Free UMETA(DisplayName = "Free"),
};

UCLASS()
class CARCHASE_API AGrabItemComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrabItemComponent();
	UPROPERTY(EditAnywhere, Category = "Held")
	EGrabType GrabType;
	
	UPROPERTY(VisibleAnywhere, Category = "Held")
	bool IsGrip;
	
	UPROPERTY(VisibleAnywhere, Category = "Held")
	bool IsAction;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* LeftHandPivot;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* RightHandPivot;

	UPROPERTY(VisibleAnywhere, Category = "Held")
	UMotionControllerComponent* RightController;
	
	UPROPERTY(VisibleAnywhere, Category = "Held")
	UMotionControllerComponent* LeftController;
	
	UPROPERTY(VisibleAnywhere, Category = "Held")
	UMotionControllerComponent* PrimaryController;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
	virtual void OnGrip(UMotionControllerComponent* controller);

	UFUNCTION(BlueprintCallable)
	virtual void OnLeave(UMotionControllerComponent* controller);

	UFUNCTION(BlueprintCallable)
	virtual void OnAction();

	UFUNCTION(BlueprintCallable)
	virtual void Action();
	
	UFUNCTION(BlueprintCallable)
	virtual void GrabPoint(UMotionControllerComponent* controller,FVector position);

	UFUNCTION(BlueprintPure)
	virtual bool IsRightControlled();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
