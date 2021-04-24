// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    TArray<FString> Words;
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);
    Isograms = GetValidWords(Words);
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {  
       ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    PrintLine(TEXT("Welcome to Bull & Cow game!"));

    int32 Position = FMath::RandRange(0, Isograms.Num() - 1);
    HiddenWord = Isograms[Position];
    Lives = HiddenWord.Len();
 
    PrintLine(TEXT("Guess the %d letters word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %d lives."), Lives);
    PrintLine(TEXT("Type in your guess.\nPress enter to continue..."));

    bGameOver = false;  
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString & Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have Won!"));
        EndGame();
        return;
    }

    if (not IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again."));
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The Hidden Word is %d letters long."), HiddenWord.Len());
        return;
    }

    PrintLine(TEXT("Lost a life!"));
    --Lives;

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have not lives left!"));
        PrintLine(TEXT("The Hidden Word was: %s."), *HiddenWord);
        EndGame();
        return;
    }
    
    FBullCowCount Counter = GetBullCows(Guess);
    PrintLine(TEXT("You have %d Bulls and %d Cows."), Counter.Bulls, Counter.Cows);
    PrintLine(TEXT("Guess again, you have %d lives left."), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString & Word) const
{
    for (int32 Index = 0; Index < Word.Len() - 1; ++Index)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); ++Comparison)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }

    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString> & Words) const
{
    TArray<FString> ValidWords;

    for (const FString & Word: Words)
    {
        if (Word.Len() >= 4 and Word.Len() <= 8 and IsIsogram(Word))
        {
            ValidWords.Add(Word);
        }
    }

    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString & Guess) const
{
    FBullCowCount Counter;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); ++GuessIndex)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            ++Counter.Bulls;
            continue;
        }

        for (int32 HiddenWordIndex = 1; HiddenWordIndex < HiddenWord.Len(); ++HiddenWordIndex)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenWordIndex])
            {
                ++Counter.Cows;
                break;
            }
        }
    }

    return Counter;
}