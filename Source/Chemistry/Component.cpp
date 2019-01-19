// Fill out your copyright notice in the Description page of Project Settings.

#include "Component.h"


// Sets default values
AComponent::AComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OurVisibleActor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Our mesh"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	OurVisibleActor->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("Material'/Game/Assets/Color.Color'"));
	StoredMaterial = FoundMaterial.Object;

	//static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial2(TEXT("Material'/Game/AutomotiveMaterials/Materials/Metal/M_Metal.M_Metal'"));
	//StoredMaterial2 = FoundMaterial2.Object;
	
}

// Called when the game starts or when spawned
void AComponent::BeginPlay()
{
	Super::BeginPlay();
	
	mesh = AComponent::LoadObjFromPath<UStaticMesh>("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'");
	OurVisibleActor->SetStaticMesh(mesh);
	float scala = compProperty.Radius / 80;
	//UE_LOG(LogTemp, Warning, TEXT("%f"),scala);
	OurVisibleActor->SetRelativeScale3D(FVector(scala,scala,scala));

	DynamicMaterialInst = UMaterialInstanceDynamic::Create(StoredMaterial, OurVisibleActor);
	DynamicMaterialInst->SetVectorParameterValue("Color", compProperty.Color);
	//DynamicMaterialInst2 = UMaterialInstanceDynamic::Create(StoredMaterial2, OurVisibleActor);

	OurVisibleActor->SetMaterial(0, DynamicMaterialInst);
}

// Called every frame
void AComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

template<typename ObjClass>
ObjClass * AComponent::LoadObjFromPath(const FName & Path)
{
	return Cast<ObjClass>(StaticLoadObject( ObjClass::StaticClass(), NULL,*Path.ToString()));
}


int AComponent::getPosition() { return position; }