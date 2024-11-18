// Fill out your copyright notice in the Description page of Project Settings.


#include "GarbComponent/SteeringWheelItem.h"

ASteeringWheelItem::ASteeringWheelItem()
{
	PrimaryActorTick.bCanEverTick = true;

	// Configura il componente del volante
	SteeringWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SteeringWheel"));
	SteeringWheel->SetupAttachment(RootComponent);
}

void ASteeringWheelItem::BeginPlay()
{
	Super::BeginPlay();
	InitialRotation = SteeringWheel->GetComponentRotation();
}

void ASteeringWheelItem::OnGrip(UMotionControllerComponent* controller)
{
	Super::OnGrip(controller);
	
	HeldRotation = SteeringWheel->GetComponentRotation();
	
	if(controller->MotionSource == "Right")
	{
		RightController = controller;
	}
	else
	{
		LeftController = controller;
	}
	if(!PrimaryController) PrimaryController = controller;
}


void ASteeringWheelItem::OnLeave(UMotionControllerComponent* controller)
{
	Super::OnLeave(controller);
	
	if(controller->MotionSource == "Right")
	{
		RightController = nullptr;
	}
	else
	{
		LeftController = nullptr;
	}

	if(!RightController && !LeftController)
	{
		PrimaryController = nullptr;
	}
	else if(!RightController)
	{
		PrimaryController = LeftController;
	}
	else
	{
		PrimaryController = RightController;
	}
}

void ASteeringWheelItem::OnAction()
{
	Super::OnAction();
	IsAction = !IsAction;
}

void ASteeringWheelItem::Action()
{
	Super::Action();
}

void ASteeringWheelItem::RotateTowardsHand()
{
	// Ottieni la posizione del volante
	FVector WheelPosition = SteeringWheel->GetComponentLocation();

	// Calcola la direzione dalla posizione del volante alla posizione della mano
	FVector DirectionToHand = PrimaryController->GetComponentLocation() - WheelPosition;
	//DirectionToHand.Z = 0; // Ignora l'asse Z per mantenere il volante sul piano orizzontale
	DirectionToHand.Normalize();

	// Calcola l'angolo Yaw tra il volante e la mano
	FRotator TargetRotation = DirectionToHand.Rotation();
	TargetRotation.Pitch = InitialRotation.Pitch;
	TargetRotation.Roll = InitialRotation.Roll;

	// Limita la rotazione del volante tra -MaxSteeringAngle e MaxSteeringAngle
	float DeltaYaw = TargetRotation.Yaw - HeldRotation.Yaw;
	float ClampedYaw = FMath::Clamp(DeltaYaw, -MaxSteeringAngle, MaxSteeringAngle);
    TargetRotation.Yaw = ClampedYaw;

	SteeringWheel->SetWorldRotation(TargetRotation);
}

void ASteeringWheelItem::RotateTowardsInit()
{
	FRotator targetRotation = SteeringWheel->GetComponentRotation();
	float absYaw = FMath::Abs(targetRotation.Yaw);
	
	float alphaLerp = BackToInit->GetFloatValue(absYaw / MaxSteeringAngle);
    
	FRotator lerpedRotation = FMath::Lerp(targetRotation, InitialRotation, alphaLerp);
	// lerpedRotation.Pitch = InitialRotation.Pitch;
	// lerpedRotation.Roll = InitialRotation.Roll;
	
	SteeringWheel->SetWorldRotation(lerpedRotation);
}

void ASteeringWheelItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(PrimaryController)
	{
		RotateTowardsHand();
	}
	else
	{
		RotateTowardsInit();
	}
}
