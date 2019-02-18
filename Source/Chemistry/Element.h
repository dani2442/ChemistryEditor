// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"
#include "Component.h"
#include <vector>

#include "ParticleHelper.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Element.generated.h"

UCLASS()
class CHEMISTRY_API AElement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	std::vector<std::vector<int>> matrix;
	TArray<AComponent*> components;
	TArray<UParticleSystemComponent*> LaserParticles;

	//ConstructorHelpers::FObjectFinder<UParticleSystem> PS;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "AI Controller")
		TSubclassOf<class UParticleSystem> comp1;

	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* PSC;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Controller")
		//UParticleSystemComponent *comp2;

	//UPROPERTY(EditDefaultsOnly)
		//UParticleSystemComponent *comp3;

	TArray<TArray<FRotator>> angles;

	void Add(int attachId,Property& prop,int type=1);
	//void AddComponent(int attach1, int attach2);
	void Create(Property& prop);
	void Delete();

	void Draw(float DeltaTime);
	void Recalculate();

private:
	void RecalculateRecursive(int i);
};
