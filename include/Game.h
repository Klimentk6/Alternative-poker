#pragma once

using namespace std;

void initializeGame(unsigned& playersCount, unsigned& roundsCount, int*& chipStacks, Card* deck)
{
    ifstream inputFile;
    inputFile.open("score.txt");
    if (inputFile.is_open() && areGoingToContinue())
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

    initializeDeck(deck);
}

void initializeRound(unsigned playersCount, int* chipStacks, Card* deck, bool* inGamePlayers, bool* playersCalled, unsigned* points, unsigned* bets, unsigned& pot, unsigned& playerIndex)
{
    shuffleDeck(deck);
    intitializeInGamePlayers(inGamePlayers, playersCount, chipStacks);
    initializePlayersCalled(playersCalled, playersCount);
    calculatePoints(points, deck, playersCount);
    initializeBets(bets, playersCount);
    payEntryFee(chipStacks, playersCount, pot, inGamePlayers);
    if (!inGamePlayers[playerIndex])
    {
        playerIndex = getNextPlayerIndex(playerIndex, playersCount, inGamePlayers, chipStacks);
    }
}

void betting(unsigned playersCount, int* chipStacks, Card* deck, bool* inGamePlayers, bool* playersCalled, unsigned* points, unsigned* bets, unsigned& pot, unsigned& playerIndex, unsigned& roundsCount, unsigned& lastRaise, unsigned& lastPlayerRaisedIndex)
{
    while (true)
    {
        printPlayerInfo(roundsCount, chipStacks, playersCount, pot, bets, playerIndex, lastRaise, deck, points);

        raiseCallOrFold(inGamePlayers, chipStacks, bets, pot, lastRaise, playerIndex, lastPlayerRaisedIndex, playersCount, playersCalled);

        if (onePlayerLeft(inGamePlayers, playersCount))
        {
            oneWinnerEveryoneFolded(playersCount, inGamePlayers, chipStacks, pot);
            printChipStacks(chipStacks, playersCount);
            cout << endl;
            break;
        }
        else if (hasEveryneCalled(playersCalled, inGamePlayers, playersCount))
        {
            unsigned winnersCount = 0;
            bool* winners = new bool[playersCount];
            initializeWinners(winners, playersCount);
            getWinners(inGamePlayers, points, winners, winnersCount, playersCount);

            if (winnersCount == 1)
            {
                oneWinner(playersCount, winners, pot, chipStacks);
                printChipStacks(chipStacks, playersCount);
                cout << endl;
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
}

void playRound(unsigned playersCount, unsigned& roundsCount, int*& chipStacks, Card* deck)
{
    bool* inGamePlayers = new bool[playersCount];
    bool* playersCalled = new bool[playersCount];
    unsigned* points = new unsigned[playersCount];
    unsigned* bets = new unsigned[playersCount];
    unsigned playerIndex = (roundsCount - 1) % playersCount;
    unsigned lastPlayerRaisedIndex = playersCount;
    unsigned lastRaise = 0;
    unsigned pot = 0;

    initializeRound(playersCount, chipStacks, deck, inGamePlayers, playersCalled, points, bets, pot, playerIndex);

    betting(playersCount, chipStacks, deck, inGamePlayers, playersCalled, points, bets, pot, playerIndex, roundsCount, lastRaise, lastPlayerRaisedIndex);

    delete[] points;
    delete[] inGamePlayers;
    delete[] bets;

    roundsCount++;
}
