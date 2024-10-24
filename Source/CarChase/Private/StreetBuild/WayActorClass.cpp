// Fill out your copyright notice in the Description page of Project Settings.


#include "StreetBuild/WayActorClass.h"

// Sets default values
AWayActorClass::AWayActorClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StartArrowComponent = CreateDefaultSubobject<UArrowComponent>("Start Arrow");
}

// Called when the game starts or when spawned
void AWayActorClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWayActorClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

