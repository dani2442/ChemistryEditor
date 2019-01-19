// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "Runtime/CoreUObject//Public/UObject/ConstructorHelpers.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Component.generated.h"

struct Property {
public:
	int AtomicNumber;
	float AtomicMass;
	float Radius;

	FString Name;
	FColor Color;

};


UCLASS()
class CHEMISTRY_API AComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* OurVisibleActor;

	UPROPERTY(EditAnywhere)
		UStaticMesh* mesh;
	
	template<typename ObjClass>
	ObjClass *LoadObjFromPath(const FName & Path);

	UMaterial* StoredMaterial;
	UMaterialInstanceDynamic* DynamicMaterialInst;

	//UMaterial* StoredMaterial2;
	//UMaterialInstanceDynamic* DynamicMaterialInst2;

	Property compProperty;
public:
	int position;
	int getPosition();
};
