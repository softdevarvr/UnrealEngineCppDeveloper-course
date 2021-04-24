// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTurret.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (not PlayerPawn or GetDistanceToPlayer() > FireRange)
	{
		return;
	}

	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::HandleDestruction() 
{
	Super::HandleDestruction();
	Destroy();
}

void APawnTurret::CheckFireCondition() 
{
	if (not PlayerPawn or not PlayerPawn->GetIsPlayerAlive() or GetDistanceToPlayer() > FireRange)
	{
		return;
	}

	Fire();
}

float APawnTurret::GetDistanceToPlayer() const
{
	if (not PlayerPawn)
	{
		return 0.0f;
	}

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}
