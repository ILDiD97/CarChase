// Fill out your copyright notice in the Description page of Project Settings.


#include "StreetBuild/WayActorClass.h"

// Sets default values
AWayActorClass::AWayActorClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(Pivot);
	
	StartArrowComponent = CreateDefaultSubobject<UArrowComponent>("Start Arrow");

	StartBoxComponent = CreateDefaultSubobject<UStartWayEventBoxComponent>("Start Box");
}

// Called when the game starts or when spawned
void AWayActorClass::BeginPlay()
{
	Super::BeginPlay();

}

void AWayActorClass::OnStartBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AWayActorClass::AddPossibleWay(ERoadTypes type)
{
	PossibleWays |= static_cast<int64>(type);
}

void AWayActorClass::RemovePossibleWay(ERoadTypes type)
{
	PossibleWays &= ~static_cast<int64>(type);
}

// Called every frame
void AWayActorClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

