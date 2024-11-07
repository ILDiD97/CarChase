// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VRCarChasePawn.h"

AVRCarChasePawn::AVRCarChasePawn()
{
	
	 VROrigin = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerPivot"));
	 VROrigin->SetupAttachment(RootComponent);
	
	 FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	 FirstPersonCamera->SetupAttachment(VROrigin);
	 FirstPersonCamera->bUsePawnControlRotation = true;
	
	 LeftHandController = CreateDefaultSubobject<UVRHandControllerComponent>(TEXT("LeftHandController"));
	
	 //LeftHandController->MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
	 LeftHandController->MotionController->SetupAttachment(VROrigin);
	 LeftHandController->MotionController->MotionSource = FName("Left");
	
	 //LeftHandController->HandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHandMesh"));
	 LeftHandController->HandMesh->SetupAttachment(LeftHandController->MotionController);
	 LeftHandController->HandMesh->SetRelativeRotation(
	 	FRotator(-25.000000,-179.999999,89.999999));
	
	 RightHandController = CreateDefaultSubobject<UVRHandControllerComponent>(TEXT("RightHandController"));
	
	 //RightHandController->MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
	 RightHandController->MotionController->MotionSource = FName("Right");
	 RightHandController->MotionController->SetupAttachment(VROrigin);
	
	 //RightHandController->HandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHandMesh"));
	 RightHandController->HandMesh->SetupAttachment(RightHandController->MotionController);
	 RightHandController->HandMesh->SetRelativeRotation(
	 	FRotator(25.000000,0.000000,89.999999));
}
