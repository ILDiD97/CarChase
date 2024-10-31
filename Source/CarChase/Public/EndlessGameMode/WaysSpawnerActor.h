// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Roads.h"
#include "GameFramework/Actor.h"
#include "StreetBuild/WayActorClass.h"
#include "WaysSpawnerActor.generated.h"

USTRUCT(BlueprintType)
struct FWaysContainer
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AWayActorClass>> WayClasses;
};


UCLASS()
class CARCHASE_API AWaysSpawnerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaysSpawnerActor();

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<ERoadTypes>, FWaysContainer>  SelectableWays;
	
	UPROPERTY(EditAnywhere, Category = "Possible Ways")
	TArray<TSubclassOf<AWayActorClass>> WayClasses;

	UPROPERTY(VisibleAnywhere, Category = "Path")
	TArray<AWayActorClass*> CurrentWays;

	UFUNCTION(BlueprintCallable)
    void GenerateNextWay(int64 Roadtype, FTransform NextTransform);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
