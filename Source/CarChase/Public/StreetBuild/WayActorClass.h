// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StartWayEventBoxComponent.h"

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

	UPROPERTY(EditAnywhere, Category = "Start",
		DisplayName = "Pivot")
	USceneComponent* Pivot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Start", DisplayName = "Start Arrow")
	UArrowComponent* StartArrowComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Start", DisplayName = "Start Box")
	UStartWayEventBoxComponent* StartBoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Ways", DisplayName = "Possible Ways",
		meta = (Bitmask, BitmaskEnum = ERoadTypes))
	int64 PossibleWays;

	UFUNCTION()
	virtual void OnStartBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable)
	void AddPossibleWay(ERoadTypes type);
	
	UFUNCTION(BlueprintCallable)
	void RemovePossibleWay(ERoadTypes type);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
