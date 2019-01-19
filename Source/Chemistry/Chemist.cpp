// Fill out your copyright notice in the Description page of Project Settings.

#include "Chemist.h"


// Sets default values
AChemist::AChemist()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Our Camera"));
	OurCamera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AChemist::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChemist::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector newPosition = GetActorLocation() +
		DeltaTime * LVelocity.X*GetActorForwardVector() +
		DeltaTime * LVelocity.Y*GetActorRightVector();
	newPosition.Z += DeltaTime * LVelocity.Z;

	SetActorLocation(newPosition);
	FRotator rotator = GetActorRotation() + DeltaTime * RVelocity;
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Blue, FString::Printf(TEXT("local:%s"),*RVelocity.ToString()));
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Blue, FString::Printf(TEXT("total:%s"),*rotator.ToString()));
	SetActorRotation(rotator);
}

// Called to bind functionality to input
void AChemist::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Click",IE_Pressed,this,&AChemist::Click);
	//InputComponent->BindAction("Train",IE_Pressed,this,&AChemist::PlayTraining);
	//InputComponent->BindAction("NextTrain",IE_Pressed,this,&AChemist::NextTraining);

	InputComponent->BindAxis("Right",this,&AChemist::Move_Right);
	InputComponent->BindAxis("Forward",this,&AChemist::Move_Forward);
	InputComponent->BindAxis("Up",this,&AChemist::Move_Up);
	InputComponent->BindAxis("LookUp",this,&AChemist::Rotate_YAxis);
	InputComponent->BindAxis("LookRight",this,&AChemist::Rotate_XAxis);
}


void AChemist::Move_Right(float AxisValue)
{
	LVelocity.Y = FMath::Clamp(AxisValue, -1.f, 1.f)*300.f;
}

void AChemist::Move_Forward(float AxisValue)
{
	LVelocity.X = FMath::Clamp(AxisValue, -1.f, 1.f)*300.f;
}

void AChemist::Move_Up(float AxisValue)
{
	LVelocity.Z = FMath::Clamp(AxisValue, -1.f, 1.f)*300.f;
}

void AChemist::Click()
{
}

void AChemist::Rotate_XAxis(float AxisValue)
{
	RVelocity.Yaw=FMath::Clamp(AxisValue, -1.f, 1.f)*100.f;
	
}

void AChemist::Rotate_YAxis(float AxisValue)
{
	RVelocity.Pitch=FMath::Clamp(AxisValue, -1.f, 1.f)*50.f;
}

