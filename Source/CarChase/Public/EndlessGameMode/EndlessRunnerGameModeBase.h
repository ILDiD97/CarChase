// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WaysSpawnerActor.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CARCHASE_API AEndlessRunnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	AEndlessRunnerGameModeBase();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWaysSpawnerActor> SpawnerClass;

	UPROPERTY(VisibleAnywhere)
	AWaysSpawnerActor* Spawner;
	
protected:
	
	virtual void BeginPlay() override;
	
};
