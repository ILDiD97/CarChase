// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum ERoadTypes : int64
{
	None = 0,
	Piazza   = 1 << 0, // 000...0001
	Bivio    = 1 << 1, // 000...0010
	Incrocio = 1 << 2, // 000...0100
	Strada   = 1 << 3  // 000...1000
	// Aggiungi altri tipi di strada se necessario
};
/**
 * 
 */
class CARCHASE_API Roads
{
public:
	
};
