// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MotionControllerComponent.h"
#include "Components/ActorComponent.h"
#include "VRHandControllerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CARCHASE_API UVRHandControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVRHandControllerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	
	// Motion controller per il tracciamento
	UPROPERTY(VisibleAnywhere, Category = "VR")
	UMotionControllerComponent* MotionController;

	// Mesh della mano o del controller
	UPROPERTY(VisibleAnywhere, Category = "VR")
	USkeletalMeshComponent* HandMesh;
	
	// Variabili per tracciare lo stato di afferramento
	UPROPERTY(VisibleAnywhere, Category = "VR")
	bool bIsLeftHandGrabbing = false;
	
	UPROPERTY(VisibleAnywhere, Category = "VR")
	bool bIsRightHandGrabbing = false;

	// Funzioni per gestire lo stato di afferramento
	UFUNCTION(BlueprintCallable)
	void Grab(bool bIsRightHand);
	
	UFUNCTION(BlueprintCallable)
	void Release(bool bIsRightHand);
	
	UFUNCTION(BlueprintCallable)
	bool IsGrabbing() const;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

	UFUNCTION()
	void SetHand(EControllerHand Hand);
};
