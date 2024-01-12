// Fill out your copyright notice in the Description page of Project Settings.
#include "RetroFpsCharacter.h"
#include "AbilitySystemComponent.h"
#include "RetroFPSAttributeSet.h"

// Sets default values
ARetroFpsCharacter::ARetroFpsCharacter() {
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");
	Attributes = CreateDefaultSubobject<URetroFPSAttributeSet>("Attributes");


} // ARetroFpsCharacter

UAbilitySystemComponent* ARetroFpsCharacter::GetAbilitySystemComponent() const {
	return AbilitySystemComponent;

} // GetAbilitySystemComponent

// Called when the game starts or when spawned
void ARetroFpsCharacter::BeginPlay() {
	Super::BeginPlay();
	if (AbilitySystemComponent) {
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		// apply default effects
		if (DefaultAttributeEffect) {
			FGameplayEffectContextHandle effectContext = AbilitySystemComponent->MakeEffectContext();
			effectContext.AddSourceObject(this);
			FGameplayEffectSpecHandle specHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, effectContext);

			if (specHandle.IsValid())
				FActiveGameplayEffectHandle getHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*specHandle.Data.Get());


		} // if

		// give attributes
		if (HasAuthority()) {
			for (TSubclassOf<UGameplayAbility> StartupAbility : DefaultAbilites)
				AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility.GetDefaultObject(), 1, 0));

		} // if

	} // if
	
} // BeginPlay

