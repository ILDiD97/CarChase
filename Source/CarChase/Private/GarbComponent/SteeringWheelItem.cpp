// Fill out your copyright notice in the Description page of Project Settings.


#include "GarbComponent/SteeringWheelItem.h"

#include "Kismet/KismetMathLibrary.h"

ASteeringWheelItem::ASteeringWheelItem()
{
	PrimaryActorTick.bCanEverTick = true;

	// Configura il componente del volante
	Pivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
	SetRootComponent(Pivot);
	
	SteeringWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SteeringWheel"));
	SteeringWheel->SetupAttachment(RootComponent);

	LeftHandPivot = CreateDefaultSubobject<USceneComponent>("LeftPivot");
	LeftHandPivot->SetupAttachment(SteeringWheel);
	
	RightHandPivot = CreateDefaultSubobject<USceneComponent>("RightPivot");
	RightHandPivot->SetupAttachment(SteeringWheel);
}

void ASteeringWheelItem::BeginPlay()
{
	Super::BeginPlay();
}

void ASteeringWheelItem::OnGrip(UMotionControllerComponent* controller)
{
	Super::OnGrip(controller);

	if (!controller)
	{
		return;
	}
	
	HeldRotation = Pivot->GetRelativeRotation();
	
	if(controller->MotionSource == "Right")
	{
		RightController = controller;
	}
	else
	{
		LeftController = controller;
	}
	
	if(!PrimaryController) PrimaryController = controller;
	
	InitialHandPosition = PrimaryController->GetRelativeLocation();
}

void ASteeringWheelItem::OnLeave(UMotionControllerComponent* controller)
{
	Super::OnLeave(controller);
	
	if (!controller)
	{
		return; // Assicura che il puntatore non sia nullo
	}

	// Controlla la sorgente del controller (FName e non FString)
	if (controller->MotionSource == FName("Right"))
	{
		RightController = nullptr;
	}
	else if (controller->MotionSource == FName("Left"))
	{
		LeftController = nullptr;
	}

	// Aggiorna il PrimaryController in base ai controller attualmente attivi
	if (RightController != nullptr && LeftController != nullptr)
	{
		PrimaryController = nullptr; // Nessun controller in uso
	}
	else
	{
		// Dai priorità al controller sinistro, se disponibile
		PrimaryController = LeftController == nullptr ? RightController : LeftController;
	}

	UE_LOG(LogTemp, Log, TEXT("PrimaryController: %s"), PrimaryController ? *PrimaryController->GetName() : TEXT("None"));
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
	// 1. Ottieni la posizione globale della mano (SteeringMC)
	// e del volante (SteeringWheel)
	FVector SteeringWheelLocation = SteeringWheel->
	GetComponentLocation();
	FVector SteeringMCLocation = PrimaryController->
	GetComponentLocation();

	// 2. Trova la rotazione necessaria per guardare il volante
	// dal punto di vista della mano
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation
	(SteeringMCLocation, SteeringWheelLocation);

	// 3. Converte la rotazione in un vettore
	FVector LookAt = LookAtRotation.Vector();

	// 4. Ottieni il vettore direzionale della
	// rotazione globale del volante
	FVector SteeringWheelDirection = SteeringWheel->GetRightVector();
	
	// 5. Calcola il Dot Product Tra i due vettori
	float DotProduct = FVector::DotProduct
	(LookAt, SteeringWheelDirection);
	
	// 6. Normalizza l'angolo usando NormalizeAxis
	float NormalizedAngle = UKismetMathLibrary::NormalizeAxis
	(DotProduct) * 50;

	// 7. Applica la rotazione calcolata localmente al volante
	FRotator DeltaRotation = FRotator
	(0.0f, NormalizedAngle, 0.0f);
	// Regola il moltiplicatore (10) per un comportamento realistico
	SteeringWheel->AddLocalRotation(DeltaRotation);
	
	// 8. Log per debug
	// FString DebugMessage = FString::Printf
	// (TEXT("Yaw: %f, Normalized Yaw: %f, Dot Yaw: %f"),
	// 	SteeringWheel->GetRelativeRotation().Yaw, NormalizedAngle, DotProduct);
	//
	// GEngine->AddOnScreenDebugMessage
	// (-1, 5.f, FColor::Green, DebugMessage);
}

void ASteeringWheelItem::RotateTowardsInit()
{
	FRotator targetRotation = SteeringWheel->GetRelativeRotation();
	float absYaw = FMath::Abs(targetRotation.Yaw);
	
	float alphaLerp = BackToInit->GetFloatValue(absYaw / MaxSteeringAngle);
    
	FRotator lerpedRotation = FMath::Lerp(targetRotation, InitialRotation, alphaLerp);
	lerpedRotation.Pitch = InitialRotation.Pitch;
	lerpedRotation.Roll = InitialRotation.Roll;
	
	Pivot->SetRelativeRotation(lerpedRotation); 
}

float ASteeringWheelItem::GetSteeringInput()
{
	float YawValue = SteeringWheel->GetRelativeRotation().Yaw;

	if(YawValue >= 0)
	{
		YawValue -= 180;
	}
	else
	{
		YawValue += 180;
	}
	// Mappatura del valore di yaw da [-180, 180] a [-1, 1]
	TRange<float> InputRange(-180.0f,180.0f);
	TRange<float> OutputRange(-1.0f, 1.0f);
	float ClampedRange = FMath::GetMappedRangeValueClamped(
		InputRange, OutputRange, YawValue);
	GEngine->AddOnScreenDebugMessage
	(-1, 5.f, FColor::Yellow,
		FString::Printf(
			TEXT("Yaw Value: %f, Normal: %f"),
			YawValue, ClampedRange));

	return ClampedRange;
}

void ASteeringWheelItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(PrimaryController != nullptr)
	{
		RotateTowardsHand();
	}
	else if(Pivot->GetRelativeRotation() != InitialRotation)
	{
		RotateTowardsInit();
	}
}

void ASteeringWheelItem::GrabPoint(UMotionControllerComponent* controller, FVector position)
{
	Super::GrabPoint(controller, position);

	if(controller->MotionSource == "Right")
	{
		RightHandPivot->SetWorldLocation(position);
	}
	else
	{
		LeftHandPivot->SetWorldLocation(position);
	}
}


