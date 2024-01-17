// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Delegates/DelegateCombinations.h" // Add this line
#include "PoolObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPooledObjectDespawn, APoolObject*, PoolActor);

UCLASS()
class RETROFPS_API APoolObject : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    APoolObject();
    FOnPooledObjectDespawn OnPooledObjectDespawn;

    UFUNCTION(BlueprintCallable, Category = "Pooled Object")
        void Deactivate();

    void SetActive(bool IsActive);
    void SetLifeSpan(float lifeTime);
    void SetPoolIndex(int index);

    bool isActive();
    int GetPoolIndex();

protected:
    bool Active;
    float LifeSpan = 0.0f;
    int PoolIndex = 0;

    FTimerHandle LifeSpanTimer;
};
