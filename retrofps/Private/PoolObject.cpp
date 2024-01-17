#include "PoolObject.h"
// Fill out your copyright notice in the Description page of Project Settings.

// Sets default values
APoolObject::APoolObject() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

} // APoolObject

void APoolObject::Deactivate() {
	SetActive(false);
	GetWorldTimerManager().ClearAllTimersForObject(this);
	OnPooledObjectDespawn.Broadcast(this);

} // Deactivate

void APoolObject::SetActive(bool IsActive) {
	Active = IsActive;
	SetActorHiddenInGame(!IsActive);
	GetWorldTimerManager().SetTimer(LifeSpanTimer, this, &APoolObject::Deactivate, LifeSpan, false);

} // SetActive


void APoolObject::SetLifeSpan(float lifeTime) {
	LifeSpan = lifeTime;

} // SetLifeSpan

void APoolObject::SetPoolIndex(int index) {
	PoolIndex = index;

} // SetPoolIndex

bool APoolObject::isActive() {
	return Active;

} // isActive

int APoolObject::GetPoolIndex() {
	return PoolIndex;

} // GetPoolIndex

