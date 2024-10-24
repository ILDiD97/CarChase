// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StreetBuild/WayActorClass.h"
#include "StreetActorClass.generated.h"

/**
 * 
 */
UCLASS()
class CARCHASE_API AStreetActorClass : public AWayActorClass
{
	GENERATED_BODY()

public:
	AStreetActorClass();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "End Way", DisplayName = "End Arrow")
	UArrowComponent* EndArrowComponent;
	
public:
	virtual void Tick(float DeltaTime) override;
};
