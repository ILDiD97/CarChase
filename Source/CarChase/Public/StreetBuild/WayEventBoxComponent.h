// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "WayEventBoxComponent.generated.h"

/**
 * 
 */
UCLASS()
class CARCHASE_API UWayEventBoxComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UWayEventBoxComponent();

	UFUNCTION(BlueprintCallable)
	virtual void GenerateWayEvent();
	
};
