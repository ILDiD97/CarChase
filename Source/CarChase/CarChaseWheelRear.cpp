// Copyright Epic Games, Inc. All Rights Reserved.

#include "CarChaseWheelRear.h"
#include "UObject/ConstructorHelpers.h"

UCarChaseWheelRear::UCarChaseWheelRear()
{
	AxleType = EAxleType::Rear;
	bAffectedByHandbrake = true;
	bAffectedByEngine = true;
}