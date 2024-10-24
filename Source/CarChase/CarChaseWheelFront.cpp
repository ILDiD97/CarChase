// Copyright Epic Games, Inc. All Rights Reserved.

#include "CarChaseWheelFront.h"
#include "UObject/ConstructorHelpers.h"

UCarChaseWheelFront::UCarChaseWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;
}