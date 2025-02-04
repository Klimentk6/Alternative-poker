#include <iostream>
#include <fstream>

#include "Constants.h"
#include "Setup.h"
#include "Cards.h"
#include "Bet.h"
#include "EndGame.h"
#include "Game.h"

using namespace std;

int main()
{
    unsigned playersCount = 0;
    unsigned roundsCount = 0;
    int* chipStacks = nullptr;
    Card deck[CARDS_COUNT];

    initializeGame(playersCount, roundsCount, chipStacks, deck);

    while (true)
    {
        playRound(playersCount, roundsCount, chipStacks, deck);
        
        if (isGameOver(chipStacks, playersCount))
        {
            printGameOver(chipStacks, playersCount);
            deleteFile();
            break;
        }

        if (!areGoingToPlayNewRound())
        {
            saveInfoInAFile(chipStacks, playersCount, roundsCount);
            break;
        }
        system("cls");
    }

    delete[] chipStacks;

    return 0;
}
