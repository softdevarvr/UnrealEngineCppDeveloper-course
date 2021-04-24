#include <iostream>

int Sum(int A, int B, int C)
{
    return A + B + C;
}

int Prod(int A, int B, int C)
{
    return A * B * C;
}

void PrintIntroduction(int Difficulty)
{
    std::cout << "You are a secret agent breaking into a level " << Difficulty
              << " secure server room...\nEnter the correct code to continue..."
              << "\n\n;
}

bool PlayGame(int Difficulty)
{
    PrintIntroduction(Difficulty);

    const int CodeA = rand() % Difficulty + 1;
    const int CodeB = rand() % Difficulty + 1;
    const int CodeC = rand() % Difficulty + 1;
    
    const int CodeSum = Sum(CodeA, CodeB, CodeC);
    const int CodeProduct = Prod(CodeA, CodeB, CodeC);
    
    std::cout << "+ There are 3 numbers in the code\n"
              << "+ The codes add-up to: " << CodeSum << std::endl
              << "+ The codes multiply to give: " << CodeProduct << "\n\n";
              
    
    int GuessA, GuessB, GuessC;
    std::cin >> GuessA >> GuessB >> GuessC;
    
    int GuessSum = Sum(GuessA, GuessB, GuessC);
    int GuessProduct = Prod(GuessA, GuessB, GuessC);
    
    if (GuessSum == CodeSum and GuessProduct == CodeProduct)
    {
        std::cout << "You win!\n";
        return true;
    }
    else
    {
        std::cout << "You lose!\n";
        return false;
    }
}

int main()
{
    srand(time(NULL));
    int LevelDifficulty = 1;
    const int MaxDifficulty = 5;

    while (LevelDifficulty <= MaxDifficulty)
    {
        bool bLevelComplete = PlayGame(LevelDifficulty);
        std::cin.clear();
        std::cin.ignore();
        
        if (bLevelComplete)
        {
            ++LevelDifficulty;
        }
    }
    return 0;
}

