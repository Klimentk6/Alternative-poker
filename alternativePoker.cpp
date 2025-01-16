#include <iostream>
#include <iostream>
#include <fstream>

#include "Constants.h"
#include "InputAndOutputFunctions.h"
#include "CardFunctions.h"
#include "ChipFunctions.h"
#include "BetFunctions.h"

using namespace std;

int main()
{
    unsigned playersCount = 0;
    int* chipStacks = nullptr;
    unsigned roundsCount = 0;

    ifstream inputFile;
    inputFile.open("score.txt");
    if(inputFile.is_open() && areGoingToContinue())
    {
        getInfoFromFile(inputFile, playersCount, chipStacks, roundsCount);
    }
    else
    {
        playersCount = choosePlayersCount();
        chipStacks = new int[playersCount];
        initializeChipStacks(chipStacks, playersCount);
        roundsCount = 1;
    }
    inputFile.close();
    
    Card deck[CARDS_COUNT];
    initializeDeck(deck);

    printGameStart();

    while (true)
    {
        printRoundStart(roundsCount);

        shuffleDeck(deck);

        unsigned inGamePlayersCount = playersCount;
        bool* inGamePlayers = new bool[playersCount];
        intitializeInGamePlayers(inGamePlayers, playersCount);

        unsigned* points = new unsigned[playersCount];
        calculatePoints(points, deck, playersCount);

        unsigned* bets = new unsigned[playersCount];
        initializeBets(bets, playersCount);

        unsigned pot = 0;

        payEntryFee(chipStacks, bets, playersCount, pot);
        printChipStacks(chipStacks, playersCount);

        unsigned lastPlayerRaisedIndex = 0;
        unsigned currentPlayerIndex = 0;
        unsigned lastRaise = 0;
        while (true)
        { 
            printPot(pot);
            printPlayerBet(bets, currentPlayerIndex);
            printLastRaise(lastRaise);
            printPlayerChipStack(chipStacks, currentPlayerIndex);
            printPlayersCardsAndPoints(deck, points, currentPlayerIndex);
            
            raiseCallOrFold(inGamePlayers,chipStacks,inGamePlayersCount, bets, pot, lastRaise, currentPlayerIndex, lastPlayerRaisedIndex, playersCount);

            if (inGamePlayersCount == 1)
            {
                for (int i = 0; i < playersCount; i++)
                {
                    if (inGamePlayers[i])
                    {
                        cout << "Player" << i + 1 << " wins " << pot << endl;
                        chipStacks[i] += pot;
                        pot = 0;
                        break;
                    }
                }
                break;
            }
            else if(hasEveryneCalled(bets, inGamePlayers, playersCount, currentPlayerIndex))
            {
                unsigned maxPoints = 0;
                unsigned winnerIndex = 0;
                for (int i = 0; i < playersCount; i++)
                {
                    if (inGamePlayers[i] && points[i] > maxPoints)
                    {
                        maxPoints = points[i];
                        winnerIndex = i;
                    }
                }
                cout << "Player" << winnerIndex + 1 << " wins " << pot << endl;
                chipStacks[winnerIndex] += pot;
                pot = 0;
                break;
            }
            
            currentPlayerIndex = nextPlayerIndex(currentPlayerIndex, playersCount, inGamePlayers);
        }
        
        delete[] points;
        delete[] inGamePlayers;
        delete[] bets;

        roundsCount++;

        if (!areGoingToPlayNewRound())
        {
            break;
        }
    }

    saveInfoInAFile(chipStacks, playersCount, roundsCount);

    delete[] chipStacks;

    return 0;
}
