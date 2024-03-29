// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PoolObject.h"
#include "ObjectPools.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RETROFPS_API UObjectPools : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectPools();
	UFUNCTION(BlueprintCallable, Category = "Object Pool")
		APoolObject* SpawnPooledObject();
	
	UPROPERTY(EditAnywhere, Category = "Object Pool")
		TSubclassOf<class APoolObject> PooledObjectSubclass;

	UPROPERTY(EditAnywhere, Category = "Object Pool")
		int PoolSize = 20;

	UPROPERTY(EditAnywhere, Category = "Object Pool")
		float PooledObjectLifeSpan = 0.0f;

	UFUNCTION()
		void OnPooledObjectDespawn(APoolObject* PoolActor);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TArray<APoolObject*> ObjectPool;
	TArray<int> SpawnedPoolIndexes;

		
};
