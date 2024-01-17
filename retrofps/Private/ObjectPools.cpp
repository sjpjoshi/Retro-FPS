// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPools.h"

// Sets default values for this component's properties
UObjectPools::UObjectPools() {

} // UObjectPools

// Called when the game starts
void UObjectPools::BeginPlay() {
	Super::BeginPlay();
	if (PooledObjectSubclass != nullptr) {
		UWorld* const World = GetWorld();

		if (World != nullptr) {
			
			for (int i = 0; i < PoolSize; i++) {
				APoolObject* PoolableActor = World->SpawnActor<APoolObject>(PooledObjectSubclass, FVector().ZeroVector, FRotator().ZeroRotator);

				if (PoolableActor != nullptr) {
					PoolableActor->SetActive(false);
					PoolableActor->SetPoolIndex(i);
					PoolableActor->OnPooledObjectDespawn.AddDynamic(this, &UObjectPools::OnPooledObjectDespawn);
					ObjectPool.Add(PoolableActor);

				} // if

			} // for

		} // if

	} // if

} // BeginPlay

APoolObject* UObjectPools::SpawnPooledObject() {
	for (APoolObject* PoolableActor : ObjectPool) {
		if (PoolableActor != nullptr && !PoolableActor->isActive()) {
			PoolableActor->SetActorLocation(FVector(0, 0, 0));
			PoolableActor->SetActorRotation(FRotator(0, 0, 0));
			PoolableActor->SetLifeSpan(PooledObjectLifeSpan);
			PoolableActor->SetActive(true);
			SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());
			return PoolableActor;

		} // if

	} // for
	
	if (SpawnedPoolIndexes.Num() > 0) {
		int PoolObjectIndex = SpawnedPoolIndexes[0];
		SpawnedPoolIndexes.Remove(PoolObjectIndex);
		APoolObject* PoolableActor = ObjectPool[PoolObjectIndex];
		if(PoolableActor != nullptr) {
			PoolableActor->SetActive(false);
			PoolableActor->SetActorLocation(FVector(0, 0, 0));
			PoolableActor->SetActorRotation(FRotator(0, 0, 0));
			PoolableActor->SetLifeSpan(PooledObjectLifeSpan);
			PoolableActor->SetActive(true);
			SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());
			return PoolableActor;

		} // if

	} // if

	return nullptr;

} // SpawnPooledObject

void UObjectPools::OnPooledObjectDespawn(APoolObject* PoolActor) {
	SpawnedPoolIndexes.Remove(PoolActor->GetPoolIndex());

} // OnPooledObjectDespawn
