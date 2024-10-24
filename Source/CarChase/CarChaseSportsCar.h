// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CarChasePawn.h"
#include "CarChaseSportsCar.generated.h"

/**
 *  Sports car wheeled vehicle implementation
 */
UCLASS(abstract)
class CARCHASE_API ACarChaseSportsCar : public ACarChasePawn
{
	GENERATED_BODY()
	
public:

	ACarChaseSportsCar();
};
