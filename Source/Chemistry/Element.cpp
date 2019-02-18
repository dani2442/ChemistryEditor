// Fill out your copyright notice in the Description page of Project Settings.

#include "Element.h"
#include "DrawDebugHelpers.h"


// Sets default values
AElement::AElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 1
	TArray<FRotator> help;
	help.Add(FRotator(0, 0, 0));
	angles.Add(help);

	//2
	help.Empty();
	help.Add(FRotator(0,180, 0));
	help.Add(FRotator(0, 0, 0));
	angles.Add(help);

	//3
	help.Empty();
	help.Add(FRotator(0, 180, 0));
	help.Add(FRotator(0, 60, 0));
	help.Add(FRotator(0, -60, 0));
	angles.Add(help);

	//4
	help.Empty();
	help.Add(FRotator(-30, 180, 0));
	help.Add(FRotator(90, 0, 0));
	help.Add(FRotator(-30, 60.5, 0));
	help.Add(FRotator(-30, -60.5, 0));
	angles.Add(help);

	//5
	help.Empty();
	help.Add(FRotator(0, 0, 0));
	help.Add(FRotator(0, 180, 0));
	help.Add(FRotator(0, 180, 0));
	help.Add(FRotator(0, 180, 0));
	help.Add(FRotator(0, 180, 0));
	angles.Add(help);

	//6
	help.Empty();
	help.Add(FRotator(0, 0, 0));
	help.Add(FRotator(0, 180, 0));
	help.Add(FRotator(0, 180, 0));
	help.Add(FRotator(0, 180, 0));
	help.Add(FRotator(0, 180, 0));
	help.Add(FRotator(0, 180, 0));
	angles.Add(help);

	//PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/Assets/PS_Laser.PS_Laser'"));
	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	PSC->SetTemplate(PS.Object);
	//PSC->bHiddenInGame = true;
}

// Called when the game starts or when spawned
void AElement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Draw(DeltaTime);
}

void AElement::Add(int attachId,Property& prop,int type) {
	for (int i = 0; i < matrix.size(); i++) {
		matrix[i].push_back(0);
	}
	matrix.push_back(std::vector<int>(matrix[0].size()));
	matrix[attachId].back() = type;
	LaserParticles.Add(UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),PSC->Template, FTransform::Identity, false));

	int newposition = matrix.size() - 1;
	components.Add(GetWorld()->SpawnActorDeferred<AComponent>(AComponent::StaticClass(), FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn));
	components[newposition]->position = newposition;
	components[newposition]->compProperty = prop;
	components[newposition]->FinishSpawning(FTransform(FRotator::ZeroRotator, FVector::ZeroVector));
	Recalculate();
}

void AElement::Create(Property& prop) {
	matrix.push_back({ 0 });
	components.Add(GetWorld()->SpawnActorDeferred<AComponent>(AComponent::StaticClass(), FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn));
	components[0]->position = 0;
	components[0]->compProperty = prop;
	components[0]->FinishSpawning(FTransform(FRotator::ZeroRotator, FVector::ZeroVector));
	components[0]->OurVisibleActor->SetRenderCustomDepth(true);
}

void AElement::Delete()
{
	matrix.clear();
	for (int i = 0; i < components.Num(); i++) {
		components[i]->Destroy();
	}
	components.Empty();
}

void AElement::Draw(float DeltaTime)
{
	
}

void AElement::Recalculate() {
	int count = 0;
	for (int i = 0; i < matrix.size(); i++) {
		count += matrix[0][i];
	}
	int count2 = 0;
	for (int i = 0; i < matrix.size(); i++) {
		if (0 != matrix[0][i]) {
			FRotator newrotator = angles[count-1][count2] + components[0]->GetActorRotation();
			components[i]->SetActorLocation(components[0]->GetActorLocation() + 200 * newrotator.Vector());
			components[i]->SetActorRotation(newrotator);
			RecalculateRecursive(i);
			count2++;
		}
	}
	int a = 0;
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = matrix.size()-1; j > i; j--) {
			if (matrix[i][j] != 0) {
				LaserParticles[a]->SetBeamSourcePoint(0, components[i]->GetActorLocation(), 0);
				LaserParticles[a]->SetBeamEndPoint(0, components[j]->GetActorLocation());
				a++;
				//DrawDebugLine(GetWorld(), components[i]->GetActorLocation(), components[j]->GetActorLocation(), FColor::Blue, false, DeltaTime+0.01, 0, 20);
			}
			
			//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),BeamParticle)
			//ULineBatchComponent* LineBatcher;
			//LineBatcher->DrawLine(components[i]->GetActorLocation(), components[j]->GetActorLocation(), FColor::Blue, false, 20, DeltaTime + 0.01);
		}
	}
}

void AElement::RecalculateRecursive(int a)
{
	int count = 0;
	for (int i = 0; i < matrix.size(); i++) {
		count += matrix[a][i];
	}
	int count2 = 0;
	for (int i = 0; i < matrix.size(); i++) {
		if (0 != matrix[a][i]) {
			FRotator newrotator = angles[count][count2+1] + components[a]->GetActorRotation();
			components[i]->SetActorLocation(components[a]->GetActorLocation() + 200 * newrotator.Vector());
			components[i]->SetActorRotation(newrotator);
			RecalculateRecursive(i);
			count2++;
		}
	}
}
