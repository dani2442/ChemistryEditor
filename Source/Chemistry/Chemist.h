// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Chemist.generated.h"

UCLASS()
class CHEMISTRY_API AChemist : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AChemist();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		UCameraComponent *OurCamera;
	
	void Move_Right(float AxisValue);
	void Move_Forward(float AxisValue);
	void Move_Up(float AxisValue);
	FVector LVelocity;

	void Click();
	bool bClick;

	void Rotate_XAxis(float AxisValue);
	void Rotate_YAxis(float AxisValue);
	FRotator RVelocity;
};
