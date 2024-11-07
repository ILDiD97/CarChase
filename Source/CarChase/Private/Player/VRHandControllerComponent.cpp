// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/VRHandControllerComponent.h"
#include "MotionControllerComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UVRHandControllerComponent::UVRHandControllerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Controller"));
	HandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandMesh"));
	// ...
}


// Called when the game starts
void UVRHandControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// FQuat UVRHandControllerComponent::GetControllerRotation(bool bIsRightHand) const
// {
// 	return bIsRightHand ? RightController->GetComponentQuat()
// 		: LeftController->GetComponentQuat();
// }

void UVRHandControllerComponent::Grab(bool bIsRightHand)
{
	if (bIsRightHand)
	{
		bIsRightHandGrabbing = true;
		bIsLeftHandGrabbing = false;
	}
	else
	{
		bIsRightHandGrabbing = false;
		bIsLeftHandGrabbing = true;
	}
}

void UVRHandControllerComponent::Release(bool bIsRightHand)
{
	if (bIsRightHand)
	{
		bIsRightHandGrabbing = true;
		bIsLeftHandGrabbing = false;
	}
	else
	{
		bIsRightHandGrabbing = false;
		bIsLeftHandGrabbing = true;
	}
}

bool UVRHandControllerComponent::IsGrabbing() const
{
	return bIsLeftHandGrabbing || bIsRightHandGrabbing;
}

// Called every frame
void UVRHandControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UVRHandControllerComponent::SetHand(EControllerHand Hand)
{
	MotionController->SetTrackingSource(Hand);

	// Carica una mesh specifica per la mano sinistra o destra
	FString HandMeshPath = Hand == EControllerHand::Left ?
		TEXT("/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_left") :
		TEXT("/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right");

	USkeletalMesh* MeshAsset = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, *HandMeshPath));
	if (MeshAsset)
	{
		HandMesh->SetSkeletalMesh(MeshAsset);
	}
}

