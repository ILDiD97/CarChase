// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VRCarChasePawn.h"
#include "ChaosWheeledVehicleMovementComponent.h"


AVRCarChasePawn::AVRCarChasePawn()
{
	
	 VROrigin = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerPivot"));
	 VROrigin->SetupAttachment(RootComponent);
	
	 FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	 FirstPersonCamera->SetupAttachment(VROrigin);
	
	 LeftHandController = CreateDefaultSubobject<UVRHandControllerComponent>(TEXT("LeftHandController"));
	
	 LeftHandController->MotionController->SetupAttachment(VROrigin);
	 LeftHandController->MotionController->MotionSource = FName("Left");
	
	 LeftHandController->HandMesh->SetupAttachment(LeftHandController->MotionController);
	 LeftHandController->HandMesh->SetRelativeRotation(
	 	FRotator(-25.000000,-179.999999,89.999999));
	
	 RightHandController = CreateDefaultSubobject<UVRHandControllerComponent>(TEXT("RightHandController"));
	
	 RightHandController->MotionController->MotionSource = FName("Right");
	 RightHandController->MotionController->SetupAttachment(VROrigin);
	
	 RightHandController->HandMesh->SetupAttachment(RightHandController->MotionController);
	 RightHandController->HandMesh->SetRelativeRotation(
	 	FRotator(25.000000,0.000000,89.999999));

	SteeringWheelComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("SteeringWheelComponent"));
	SteeringWheelComponent->SetupAttachment(VROrigin);
	SteeringWheelComponent->SetChildActorClass(SteeringWheelClass);
}

void AVRCarChasePawn::Steering(const FInputActionValue& Value)
{
	float SteeringValue = Value.Get<float>();
	
	ChaosVehicleMovement->SetSteeringInput(SteeringValue);
}

void AVRCarChasePawn::Throttle(const FInputActionValue& Value)
{
	if(ChaosVehicleMovement)
		UE_LOG(LogTemp, Warning, TEXT("Hello World"));
	// get the input magnitude for the throttle
	float ThrottleValue = Value.Get<float>();

	// add the input
	ChaosVehicleMovement->SetThrottleInput(ThrottleValue);
}

void AVRCarChasePawn::Brake(const FInputActionValue& Value)
{
	// get the input magnitude for the brakes
	float BreakValue = Value.Get<float>();

	// add the input
	ChaosVehicleMovement->SetBrakeInput(BreakValue);
}

void AVRCarChasePawn::StartBrake(const FInputActionValue& Value)
{
	Super::StartBrake(Value);
}

void AVRCarChasePawn::StopBrake(const FInputActionValue& Value)
{
	// call the Blueprint hook for the break lights
	BrakeLights(false);

	// reset brake input to zero
	ChaosVehicleMovement->SetBrakeInput(0.0f);
}

void AVRCarChasePawn::StartHandbrake(const FInputActionValue& Value)
{
	// add the input
	ChaosVehicleMovement->SetHandbrakeInput(true);
}

void AVRCarChasePawn::StopHandbrake(const FInputActionValue& Value)
{
	// add the input
	ChaosVehicleMovement->SetHandbrakeInput(false);
}

void AVRCarChasePawn::LookAround(const FInputActionValue& Value)
{
	// get the flat angle value for the input 
	float LookValue = Value.Get<float>();

	// add the input
	FirstPersonCamera->AddLocalRotation(FRotator(0.0f, LookValue, 0.0f));
}

void AVRCarChasePawn::ToggleCamera(const FInputActionValue& Value)
{
	Super::ToggleCamera(Value);
}

void AVRCarChasePawn::ResetVehicle(const FInputActionValue& Value)
{
	// reset to a location slightly above our current one
	FVector ResetLocation = GetActorLocation() + FVector(0.0f, 0.0f, 50.0f);

	// reset to our yaw. Ignore pitch and roll
	FRotator ResetRotation = GetActorRotation();
	ResetRotation.Pitch = 0.0f;
	ResetRotation.Roll = 0.0f;
	
	// teleport the actor to the reset spot and reset physics
	SetActorTransform(FTransform(ResetRotation, ResetLocation, FVector::OneVector), false, nullptr, ETeleportType::TeleportPhysics);

	GetMesh()->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	GetMesh()->SetPhysicsLinearVelocity(FVector::ZeroVector);

	UE_LOG(LogTemplateVehicle, Error, TEXT("Reset Vehicle"));
}

void AVRCarChasePawn::BeginPlay()
{
	Super::BeginPlay();
	SteeringWheel = Cast<ASteeringWheelItem>(SteeringWheelComponent->GetChildActor());
}

void AVRCarChasePawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// steering 
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &AVRCarChasePawn::Steering);
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Completed, this, &AVRCarChasePawn::Steering);

		// throttle 
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &AVRCarChasePawn::Throttle);
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &AVRCarChasePawn::Throttle);

		// break 
		EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &AVRCarChasePawn::Brake);
		EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Started, this, &AVRCarChasePawn::StartBrake);
		EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Completed, this, &AVRCarChasePawn::StopBrake);

		// handbrake 
		EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Started, this, &AVRCarChasePawn::StartHandbrake);
		EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Completed, this, &AVRCarChasePawn::StopHandbrake);

		// look around 
		EnhancedInputComponent->BindAction(LookAroundAction, ETriggerEvent::Triggered, this, &AVRCarChasePawn::LookAround);

		// toggle camera 
		EnhancedInputComponent->BindAction(ToggleCameraAction, ETriggerEvent::Triggered, this, &AVRCarChasePawn::ToggleCamera);

		// reset the vehicle 
		EnhancedInputComponent->BindAction(ResetVehicleAction, ETriggerEvent::Triggered, this, &AVRCarChasePawn::ResetVehicle);
	}
	else
	{
		UE_LOG(LogTemplateVehicle, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AVRCarChasePawn::Tick(float Delta)
{
	Super::Tick(Delta);
}
