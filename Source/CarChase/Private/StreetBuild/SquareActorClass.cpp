// Fill out your copyright notice in the Description page of Project Settings.


#include "StreetBuild/SquareActorClass.h"

ASquareActorClass::ASquareActorClass()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Pivot = CreateDefaultSubobject<USceneComponent>("Pivot");
	SetRootComponent(Pivot);
	
	StartArrowComponent->SetupAttachment(Pivot);

	StartBoxComponent->SetupAttachment(Pivot);
	
	F_EndArrowComponent = CreateDefaultSubobject<UArrowComponent>("End Forward Arrow");
	F_EndArrowComponent->SetupAttachment(Pivot);
	
	F_EndWayBoxComponent = CreateDefaultSubobject<UEndWayEventBoxComponent>("End Forward Box");
	F_EndWayBoxComponent->SetupAttachment(Pivot);
	
	R_EndArrowComponent = CreateDefaultSubobject<UArrowComponent>("End Right Arrow");
	R_EndArrowComponent->SetupAttachment(Pivot);
	
	R_EndWayBoxComponent = CreateDefaultSubobject<UEndWayEventBoxComponent>("End Right Box");
	R_EndWayBoxComponent->SetupAttachment(Pivot);
	
	L_EndArrowComponent = CreateDefaultSubobject<UArrowComponent>("End Left Arrow");
	L_EndArrowComponent->SetupAttachment(Pivot);
	
	L_EndWayBoxComponent = CreateDefaultSubobject<UEndWayEventBoxComponent>("End Left Box");
	L_EndWayBoxComponent->SetupAttachment(Pivot);
}
