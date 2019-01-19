// Fill out your copyright notice in the Description page of Project Settings.

#include "ChemistLab.h"


// Sets default values
AChemistLab::AChemistLab()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Our Camera"));
	OurCamera->SetupAttachment(RootComponent);

	CreateTable();
}

// Called when the game starts or when spawned
void AChemistLab::BeginPlay()
{
	OurPlayer = UGameplayStatics::GetPlayerController(this, 0);
	Super::BeginPlay();
	FindAllActors(GetWorld(), element);
}

// Called every frame
void AChemistLab::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector newPosition = GetActorLocation() +
		DeltaTime * LVelocity.X*GetActorForwardVector() +
		DeltaTime * LVelocity.Y*GetActorRightVector();
	newPosition.Z += DeltaTime * LVelocity.Z;
	if (bShift) {
		SetActorLocation(newPosition);
		FRotator rotator = GetActorRotation() + DeltaTime * RVelocity;
		//GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Blue, FString::Printf(TEXT("local:%s"),*RVelocity.ToString()));
		//GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Blue, FString::Printf(TEXT("total:%s"),*rotator.ToString()));
		SetActorRotation(rotator);
	}
}

// Called to bind functionality to input
void AChemistLab::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Click",IE_Pressed,this,&AChemistLab::Click);
	InputComponent->BindAction("Add",IE_Pressed,this,&AChemistLab::ClickAdd);
	InputComponent->BindAction("Shift",IE_Pressed,this,&AChemistLab::Shift);
	InputComponent->BindAction("Shift",IE_Released,this,&AChemistLab::ShiftOff);
	//InputComponent->BindAction("Train",IE_Pressed,this,&AChemist::PlayTraining);
	//InputComponent->BindAction("NextTrain",IE_Pressed,this,&AChemist::NextTraining);

	InputComponent->BindAxis("Right",this,&AChemistLab::Move_Right);
	InputComponent->BindAxis("Forward",this,&AChemistLab::Move_Forward);
	InputComponent->BindAxis("Up",this,&AChemistLab::Move_Up);
	InputComponent->BindAxis("LookUp",this,&AChemistLab::Rotate_YAxis);
	InputComponent->BindAxis("LookRight",this,&AChemistLab::Rotate_XAxis);
}

void AChemistLab::Create()
{
	element->Create(PeriodicTable[selElement-1]);
}

void AChemistLab::Delete()
{
	selected = 0;
	element->Delete();
}

void AChemistLab::SelectedElement(int32 n)
{
	selElement = n;
}

void AChemistLab::Shift() {
	OurPlayer->bShowMouseCursor = false;
	bShift = true;
}

void AChemistLab::ShiftOff() {
	bShift = false;
	OurPlayer->bShowMouseCursor = true;
}

void AChemistLab::addElement(int32 type)
{
	element->Add(selected,PeriodicTable[selElement-1], type);
}

void AChemistLab::Move_Right(float AxisValue)
{
	LVelocity.Y = FMath::Clamp(AxisValue, -1.f, 1.f)*300.f;
}

void AChemistLab::Move_Forward(float AxisValue)
{
	LVelocity.X = FMath::Clamp(AxisValue, -1.f, 1.f)*300.f;
}

void AChemistLab::Move_Up(float AxisValue)
{
	LVelocity.Z = FMath::Clamp(AxisValue, -1.f, 1.f)*300.f;
}

void AChemistLab::Click()
{
	FVector Start = GetActorLocation();
	FVector End = GetActorForwardVector() * 10000 + Start;

	//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, FString::Printf(TEXT("click!")));
	FCollisionQueryParams CollisionParams;
	//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0.1f, 0, 10);
	FHitResult OutHit;
	bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);

	if (isHit) {
		if (OutHit.bBlockingHit) {
			if (GEngine) {
				if (AComponent* getComponent = Cast<AComponent>(OutHit.GetActor())) {
					selected = getComponent->position;
					//Layer = neuron->getLayer();
					//Neuron = neuron->getNeuron();
					GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, FString::Printf(TEXT("selected: %i"),selected));
				}				
			}
		}
	}
}

void AChemistLab::ClickAdd() {
	element->Add(selected,PeriodicTable[selElement-1], 1);
}

void AChemistLab::Rotate_XAxis(float AxisValue)
{
	RVelocity.Yaw=FMath::Clamp(AxisValue, -1.f, 1.f)*100.f;
	
}

void AChemistLab::Rotate_YAxis(float AxisValue)
{
	RVelocity.Pitch=FMath::Clamp(AxisValue, -1.f, 1.f)*50.f;
}

template<typename T>
void AChemistLab::FindAllActors(UWorld * world, T*& Out)
{
	for (TActorIterator<AActor> It(world, T::StaticClass()); It; ++It)
     {
         T* Actor = Cast<T>(*It);
         if (Actor && !Actor->IsPendingKill())
         {
             Out=Actor;
			 GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, FString::Printf(TEXT("Found!")));
         }
     }
}

void AChemistLab::CreateTable() {
	Property temp;
	{
		temp.AtomicNumber = 1;
		temp.AtomicMass = 1;
		temp.Radius = 37;
		temp.Color = FColor::White;
		temp.Name = "Hidrogen";
		PeriodicTable.Add(temp);
	}
	PeriodicTable.Add(temp);
	PeriodicTable.Add(temp);
	PeriodicTable.Add(temp);
	{
		temp.AtomicNumber = 5;
		temp.AtomicMass = 10.81;
		temp.Radius = 80;
		temp.Color = FColor::Green;
		temp.Name = "Boron";
		PeriodicTable.Add(temp);
	}
	{
		temp.AtomicNumber = 6;
		temp.AtomicMass = 12;
		temp.Radius = 77;
		temp.Color = FColor::Cyan;
		temp.Name = "Carbon";
		PeriodicTable.Add(temp);
	}
	{
		temp.AtomicNumber = 7;
		temp.AtomicMass = 14;
		temp.Radius = 74;
		temp.Color = FColor::Purple;
		temp.Name = "Nitrogen";
		PeriodicTable.Add(temp);
	}
	{
		temp.AtomicNumber = 8;
		temp.AtomicMass = 16;
		temp.Radius = 77;
		temp.Color = FColor::Magenta;
		temp.Name = "Oxygen";
		PeriodicTable.Add(temp);
	}
	{
		temp.AtomicNumber = 9;
		temp.AtomicMass = 19;
		temp.Radius = 72;
		temp.Color = FColor::Emerald;
		temp.Name = "Fluor";
		PeriodicTable.Add(temp);
	}
}
