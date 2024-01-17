// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include <GameplayEffectTypes.h>
#include "AbilitySystemInterface.h"
#include "RetroFpsCharacter.generated.h"

UCLASS()
class RETROFPS_API ARetroFpsCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilites, meta = (AllowPrivateAccess = "true")) class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
		class URetroFPSAttributeSet* Attributes;

public:
	// Sets default values for this character's properties
	ARetroFpsCharacter();

	// OVerriden from IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int MaxHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int MaxArmor = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int MaxBullets = 250;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int MaxRockets = 20;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Effect that initializes our default attributes
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "RetroFps") TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	// Array of starting abilites
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "RetroFps") TArray<TSubclassOf<class UGameplayAbility>> DefaultAbilites;

	
};
