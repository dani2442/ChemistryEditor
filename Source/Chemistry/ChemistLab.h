// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine.h"
#include "GameFramework/PlayerController.h"

#include "Element.h"
#include "Component.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ChemistLab.generated.h"



UCLASS()
class CHEMISTRY_API AChemistLab : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AChemistLab();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	int selected = 0;
	AElement* element;

	UFUNCTION(BlueprintCallable, Category = "Chemistry")
	void Create();

	UFUNCTION(BlueprintCallable, Category = "Chemistry")
	void Delete();

	UFUNCTION(BlueprintCallable, Category = "Chemistry")
	void SelectedElement(int32 n);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		int32 selElement = 6;

	UFUNCTION(BlueprintCallable, Category = "Chemistry")
	void addElement(int32 type=1);

	TArray<Property> PeriodicTable;

	APlayerController* OurPlayer;
	
public:
	template<typename T>
	void FindAllActors(UWorld * world, T*& Out);

	UPROPERTY(EditAnywhere)
		UCameraComponent *OurCamera;
	
	void Move_Right(float AxisValue);
	void Move_Forward(float AxisValue);
	void Move_Up(float AxisValue);
	FVector LVelocity;

	void ClickAdd();
	void Click();
	bool bClick;

	void Shift();
	void ShiftOff();
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Chemistry")
		bool bShift;

	void Rotate_XAxis(float AxisValue);
	void Rotate_YAxis(float AxisValue);
	FRotator RVelocity;
	
	void CreateTable();
};

