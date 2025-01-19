#include <iostream>
#include <iostream>
#include <fstream>

#include "Constants.h"
#include "InputAndOutputFunctions.h"
#include "CardFunctions.h"
#include "BetFunctions.h"
#include "EndGameFunctions.h"

using namespace std;

int main()
{
    unsigned playersCount = 0;
    unsigned roundsCount = 0;
    int* chipStacks = nullptr;

    ifstream inputFile;
    inputFile.open("score.txt");
    if(inputFile.is_open() && areGoingToContinue())
    {
        getInfoFromFile(inputFile, playersCount, chipStacks, roundsCount);
    }
    else
    {
        system("cls");
        playersCount = choosePlayersCount();
        chipStacks = new int[playersCount];
        initializeChipStacks(chipStacks, playersCount);
        roundsCount = 1;
    }
    inputFile.close();
    system("cls");
    
    Card deck[CARDS_COUNT];
    initializeDeck(deck);

    while (true)
    {
        shuffleDeck(deck);

        bool* inGamePlayers = new bool[playersCount];
        intitializeInGamePlayers(inGamePlayers, playersCount, chipStacks);

        bool* playersCalled = new bool[playersCount];
        initializePlayersCalled(playersCalled, playersCount);

        unsigned* points = new unsigned[playersCount];
        calculatePoints(points, deck, playersCount);

        unsigned* bets = new unsigned[playersCount];
        initializeBets(bets, playersCount);

        unsigned pot = 0;
        payEntryFee(chipStacks, playersCount, pot, inGamePlayers);

        unsigned playerIndex = (roundsCount - 1) % playersCount;
        if (!inGamePlayers[playerIndex])
        {
            playerIndex = getNextPlayerIndex(playerIndex, playersCount, inGamePlayers, chipStacks);
        }
        unsigned lastPlayerRaisedIndex = playersCount;
        unsigned lastRaise = 0;
        while (true)
        { 
            printPlayerInfo(roundsCount, chipStacks, playersCount, pot, bets, playerIndex, lastRaise, deck, points);
            
            raiseCallOrFold(inGamePlayers,chipStacks, bets, pot, lastRaise, playerIndex, lastPlayerRaisedIndex, playersCount, playersCalled);
            system("cls");

            if (onePlayerLeft(inGamePlayers, playersCount))
            {
                oneWinnerEveryoneFolded(playersCount, inGamePlayers, chipStacks, pot);
                printChipStacks(chipStacks, playersCount);
                cout << endl;
                break;
            }
            else if(hasEveryneCalled(playersCalled, inGamePlayers, playersCount))
            {
                unsigned winnersCount = 0;
                bool* winners = new bool[playersCount];
                initializeWinners(winners, playersCount);
                getWinners(inGamePlayers, points, winners, winnersCount, playersCount);

                if (winnersCount == 1)
                {
                    oneWinner(playersCount, winners, pot, chipStacks);
                }
                else
                {
                    multipleWinners(playersCount, pot, winners, chipStacks, inGamePlayers);
                    
                    system("cls");
                    initializePlayersCalled(playersCalled, playersCount);
                    initializeBets(bets, playersCount);
                    shuffleDeck(deck);
                    calculatePoints(points, deck, playersCount);

                    playerIndex = getNextPlayerIndex(playerIndex, playersCount, inGamePlayers, chipStacks);
                    lastPlayerRaisedIndex = playersCount;
                    lastRaise = 0;
                    continue;
                }
                delete[] winners;
                break;
            } 

            playerIndex = getNextPlayerIndex(playerIndex, playersCount, inGamePlayers, chipStacks);
        }
        
        delete[] points;
        delete[] inGamePlayers;
        delete[] bets;

        roundsCount++;
        
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
