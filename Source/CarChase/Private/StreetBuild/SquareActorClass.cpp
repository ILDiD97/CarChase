// Fill out your copyright notice in the Description page of Project Settings.


#include "StreetBuild/SquareActorClass.h"

ASquareActorClass::ASquareActorClass()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	F_EndArrowComponent = CreateDefaultSubobject<UArrowComponent>("End Forward Arrow");

	F_EndWayBoxComponent = CreateDefaultSubobject<UEndWayEventBoxComponent>("End Forward Box");

	R_EndArrowComponent = CreateDefaultSubobject<UArrowComponent>("End Right Arrow");

	R_EndWayBoxComponent = CreateDefaultSubobject<UEndWayEventBoxComponent>("End Right Box");

	L_EndArrowComponent = CreateDefaultSubobject<UArrowComponent>("End Left Arrow");

	L_EndWayBoxComponent = CreateDefaultSubobject<UEndWayEventBoxComponent>("End Left Box");
}
