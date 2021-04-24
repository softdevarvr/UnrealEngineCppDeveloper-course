// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) 
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    
    HUD->RemoveFromViewport();

    UUserWidget* ScreenToShow = nullptr;

    if (bIsWinner)
    {
        ScreenToShow = CreateWidget(this, WinScreenClass);
    }
    else
    {
        ScreenToShow = CreateWidget(this, LoseScreenClass);
    }

    if (ScreenToShow != nullptr)
    {
        ScreenToShow->AddToViewport();
    }

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

float AShooterPlayerController::GetRestartDelay() const
{
    return RestartDelay;
}

void AShooterPlayerController::BeginPlay() 
{
    Super::BeginPlay();

    HUD = CreateWidget(this, HUDClass);

    if (HUD != nullptr)
    {
        HUD->AddToViewport();
    }
}
