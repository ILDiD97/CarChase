// Fill out your copyright notice in the Description page of Project Settings.


#include "StreetBuild/StreetActorClass.h"

AStreetActorClass::AStreetActorClass()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Pivot = CreateDefaultSubobject<USceneComponent>("Pivot");
	SetRootComponent(Pivot);
	
	EndArrowComponent = CreateDefaultSubobject<UArrowComponent>("End Arrow");

	EndWayBoxComponent = CreateDefaultSubobject<UEndWayEventBoxComponent>("End Box");
}

void AStreetActorClass::BeginPlay()
{
	Super::BeginPlay();
}

void AStreetActorClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
