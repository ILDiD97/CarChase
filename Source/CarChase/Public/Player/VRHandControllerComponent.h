// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MotionControllerComponent.h"
#include "Components/ActorComponent.h"
#include "Components/ArrowComponent.h"
#include "GarbComponent/GrabItemComponent.h"
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
	UArrowComponent* HandPivot;
	
	UPROPERTY(VisibleAnywhere, Category = "VR")
	USkeletalMeshComponent* HandMesh;

	UPROPERTY(VisibleAnywhere, Category = "Grab")
	AGrabItemComponent* GrabbedActor;
	
	UPROPERTY(VisibleAnywhere, Category = "Grab")
	float GrabRadius = 5.f;

	// Funzioni per gestire lo stato di afferramento
	UFUNCTION(BlueprintCallable)
	void Grab();
	
	UFUNCTION(BlueprintCallable)
	void Release();
	
	UFUNCTION(BlueprintCallable)
	bool IsGrabbing() const;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void HandCaseAttach();

	UFUNCTION(BlueprintCallable)
	void GripTo();

	UFUNCTION(BlueprintCallable)
	void GrabPointTo();
	
	UFUNCTION(BlueprintCallable)
	void ToGrip();

	UFUNCTION(BlueprintCallable)
	void Free();

};
