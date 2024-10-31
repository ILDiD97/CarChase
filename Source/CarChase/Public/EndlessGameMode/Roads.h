// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Roads.generated.h"

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum ERoadTypes : int64
{
	None = 0,
	Strada   = 1 << 0, // 000...0001
	Piazza    = 1 << 1, // 000...0010
	Incrocio = 1 << 2, // 000...0100
	Bivio   = 1 << 3  // 000...1000
	// Aggiungi altri tipi di strada se necessario
};
ENUM_CLASS_FLAGS(ERoadTypes);

namespace Roads
{
	
}


