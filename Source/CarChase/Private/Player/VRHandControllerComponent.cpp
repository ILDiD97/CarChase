// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/VRHandControllerComponent.h"
#include "MotionControllerComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UVRHandControllerComponent::UVRHandControllerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Controller"));
	HandPivot = CreateDefaultSubobject<UArrowComponent>(TEXT("HandPivot"));
	HandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandMesh"));
	// ...
}


// Called when the game starts
void UVRHandControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UVRHandControllerComponent::Grab()
{
	FVector ControllerLoc = MotionController->GetComponentLocation();
	TArray<AActor*> ActorToIgnore;
	TArray<FHitResult> HitResults;
	UKismetSystemLibrary::SphereTraceMulti(GetWorld(), ControllerLoc, ControllerLoc,
		GrabRadius, TraceTypeQuery1, false, ActorToIgnore,
		EDrawDebugTrace::ForDuration, HitResults,false,
		FLinearColor::Red, FLinearColor::Green, 1.f);

	TArray<AGrabItemComponent*> GrabsItems;
	if(HitResults.Num() > 0)
	{
		for (auto HitResult : HitResults)
		{
			AGrabItemComponent* controlActor;
			controlActor = Cast<AGrabItemComponent>(HitResult.GetActor());
			if(controlActor)
			{
				GrabsItems.Add(controlActor);
			}
		}
	}
	else
	{
		return;
	}

	if(GrabsItems.Num() > 0)
	{
		GrabbedActor = GrabsItems[0];
	}
	else
	{
		return;
	}

	GrabbedActor->OnGrip(MotionController);
}

void UVRHandControllerComponent::Release()
{
	GrabbedActor->OnLeave(MotionController);
	GrabbedActor = nullptr;
}

bool UVRHandControllerComponent::IsGrabbing() const
{
	return GrabbedActor == nullptr;
}

// Called every frame
void UVRHandControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(GrabbedActor)
		HandCaseAttach();
	else
		Free();
	// ...
}

void UVRHandControllerComponent::HandCaseAttach()
{
	switch (GrabbedActor->GrabType)
	{
	case EGrabType::Free:
		break;
	case EGrabType::GripTo:
		GrabPointTo();
		GripTo();
		break;
	case EGrabType::ToGrip:
		break;
	default:
		break;
	}
}

void UVRHandControllerComponent::GripTo()
{
	USceneComponent* CurrentPosition = MotionController->MotionSource == "Right" ?
		GrabbedActor->RightHandPivot :
		GrabbedActor->LeftHandPivot;
	HandPivot->AttachToComponent(CurrentPosition, FAttachmentTransformRules::KeepWorldTransform);
}

void UVRHandControllerComponent::GrabPointTo()
{
	FVector TraceStart = MotionController->GetComponentLocation();
	FVector TraceEnd = GrabbedActor->GetActorLocation();

	FHitResult HitResult;

	// Effettua il line trace senza parametri aggiuntivi
	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility))
	{
		// Controlla se il colpo è sulla mesh del volante
		if (HitResult.GetActor() == GrabbedActor)
		{
			// Punto di impatto sulla mesh del volante
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 12, FColor::Blue, false, 1.0f);
			GrabbedActor->GrabPoint(MotionController, HitResult.ImpactPoint);
		}
	}
}

void UVRHandControllerComponent::ToGrip()
{
	
}

void UVRHandControllerComponent::Free()
{
	HandPivot->AttachToComponent(MotionController, FAttachmentTransformRules::KeepWorldTransform);
}



