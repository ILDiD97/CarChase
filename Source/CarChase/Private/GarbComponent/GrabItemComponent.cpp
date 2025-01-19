// Fill out your copyright notice in the Description page of Project Settings.


#include "GarbComponent/GrabItemComponent.h"

// Sets default values
AGrabItemComponent::AGrabItemComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGrabItemComponent::OnGrip(UMotionControllerComponent* controller)
{
}

void AGrabItemComponent::OnLeave(UMotionControllerComponent* controller)
{
}

void AGrabItemComponent::OnAction()
{
}

void AGrabItemComponent::Action()
{
}

void AGrabItemComponent::GrabPoint(UMotionControllerComponent* controller, FVector position)
{
}

bool AGrabItemComponent::IsRightControlled()
{
	return PrimaryController->MotionSource == "Right";		
}

// Called when the game starts or when spawned
void AGrabItemComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrabItemComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

