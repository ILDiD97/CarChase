// Fill out your copyright notice in the Description page of Project Settings.


#include "GarbComponent/SteeringWheelActorClass.h"

// Sets default values
ASteeringWheelActorClass::ASteeringWheelActorClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Configura il componente del volante
	SteeringWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SteeringWheel"));
	SteeringWheel->SetupAttachment(RootComponent);
}

void ASteeringWheelActorClass::RotateTowardsHand(const FVector& HandPosition)
{
	// Ottieni la posizione del volante
	FVector WheelPosition = SteeringWheel->GetComponentLocation();

	// Calcola la direzione dalla posizione del volante alla posizione della mano
	FVector DirectionToHand = HandPosition - WheelPosition;
	DirectionToHand.Z = 0; // Ignora l'asse Z per mantenere il volante sul piano orizzontale
	DirectionToHand.Normalize();

	// Calcola l'angolo Yaw tra il volante e la mano
	FRotator TargetRotation = DirectionToHand.Rotation();
	TargetRotation.Pitch = 0.0f;
	TargetRotation.Roll = 0.0f;

	// Limita la rotazione del volante tra -MaxSteeringAngle e MaxSteeringAngle
	float DeltaYaw = TargetRotation.Yaw - InitialRotation.Yaw;
	float ClampedYaw = FMath::Clamp(DeltaYaw, -MaxSteeringAngle, MaxSteeringAngle);

	// Imposta la nuova rotazione del volante
	FRotator NewRotation = InitialRotation;
	NewRotation.Yaw += ClampedYaw;
	SteeringWheel->SetWorldRotation(NewRotation);
}

void ASteeringWheelActorClass::OnHeld()
{
	IsHeld = true;
}

void ASteeringWheelActorClass::OnDeHeld()
{
	IsHeld = false;
}

// Called when the game starts or when spawned
void ASteeringWheelActorClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASteeringWheelActorClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

