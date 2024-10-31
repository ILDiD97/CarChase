// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EndWayEventBoxComponent.h"
#include "StreetBuild/WayActorClass.h"
#include "SquareActorClass.generated.h"

/**
 * 
 */
UCLASS()
class CARCHASE_API ASquareActorClass : public AWayActorClass
{
	GENERATED_BODY()

public:

	ASquareActorClass();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "End Way", DisplayName = "End Forward Arrow")
	UArrowComponent* F_EndArrowComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "End Way", DisplayName = "End Forward Box")
	UEndWayEventBoxComponent* F_EndWayBoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "End Way", DisplayName = "End Right Arrow")
	UArrowComponent* R_EndArrowComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "End Way", DisplayName = "End Right Box")
	UEndWayEventBoxComponent* R_EndWayBoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "End Way", DisplayName = "End Left Arrow")
	UArrowComponent* L_EndArrowComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "End Way", DisplayName = "End Left Box")
	UEndWayEventBoxComponent* L_EndWayBoxComponent;
};
