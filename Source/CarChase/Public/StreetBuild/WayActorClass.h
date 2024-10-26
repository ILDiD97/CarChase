// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "EndlessGameMode/Roads.h"
#include "GameFramework/Actor.h"
#include "WayActorClass.generated.h"

UCLASS()
class CARCHASE_API AWayActorClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWayActorClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USceneComponent* Pivot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Start", DisplayName = "Start Arrow")
	UArrowComponent* StartArrowComponent;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ways", DisplayName = "Possible Ways")
	//TArray<TSubclassOf<AWayActorClass>> PossibleWays;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ways", DisplayName = "Possible Ways")
	TMap<int64, TEnumAsByte<ERoadTypes>> PossibleWays;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
