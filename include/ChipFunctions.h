#pragma once

using namespace std;

unsigned getNextPlayerIndex(unsigned playerIndex, unsigned playersCount, const bool* inGamePlayers, const int* chipStacks)
{
    do
    {
        playerIndex++;
        if (playerIndex >= playersCount)
        {
            playerIndex = 0;
        }
    } while (inGamePlayers[playerIndex] == false || chipStacks[playerIndex] == 0);

    return playerIndex;
}

bool onePlayerLeft(const bool* inGamePlayers, unsigned playersCount)
{
    unsigned playersStillInGame = 0;
    for (int i = 0; i < playersCount; i++)
    {
        if (inGamePlayers[i])
        {
            playersStillInGame++;
        }
    }
    if (playersStillInGame == 1)
    {
        return true;
    }
    return false;
}
void oneWinnerEveryoneFolded(unsigned playersCount, const bool* inGamePlayers, int* chipStacks, unsigned& pot)
{
    for (int i = 0; i < playersCount; i++)
    {
        if (inGamePlayers[i])
        {
            cout << "Player" << i + 1 << " wins " << pot << endl;
            cout << endl;

            chipStacks[i] += pot;
            pot = 0;
            break;
        }
    }
}

bool hasEveryneCalled(const bool* playersCalled, const bool* inGamePlayers, unsigned playersCount)
{
    for (int i = 0; i < playersCount; i++)
    {
        if (inGamePlayers[i] && !playersCalled[i])
        {
            return false;
        }
    }
    return true;
}

void initializeWinners(bool* winners, unsigned playersCount)
{
    for (int i = 0; i < playersCount; i++)
    {
        winners[i] = false;
    }
}
void getWinners(bool* inGamePlayers, unsigned* points, bool* winners, unsigned& winnersCount, unsigned playersCount)
{
    unsigned maxPoints = 0;
    for (int i = 0; i < playersCount; i++)
    {
        if (inGamePlayers[i] && points[i] > maxPoints)
        {
            maxPoints = points[i];
            winnersCount = 1;
            initializeWinners(winners, playersCount);
            winners[i] = true;
        }
        else if (points[i] == maxPoints)
        {
            winnersCount++;
            winners[i] = true;
        }
    }
}
void oneWinner(unsigned playersCount, const bool* winners, unsigned& pot, int* chipStacks)
{
    for (int i = 0; i < playersCount; i++)
    {
        if (winners[i])
        {
            cout << "Player" << i + 1 << " wins " << pot << endl;
            cout << endl;

            chipStacks[i] += pot;
            pot = 0;
            break;
        }
    }
}
void addChipsIfNotEnough(unsigned playersCount, const bool* inGamePlayers, int* chipStacks)
{
    for (int i = 0; i < playersCount; i++)
    {
        if (inGamePlayers[i] && chipStacks[i] == 0)
        {
            chipStacks[i] = 50;
        }
    }
}
void multipleWinners(unsigned playersCount, unsigned &pot, const bool* winners, int* chipStacks, bool* inGamePlayers)
{
    cout << "IT IS A TIE!" << endl;
    cout << endl;
    unsigned tieEntryFee = pot / 2;
    for (int i = 0; i < playersCount; i++)
    {
        if (!winners[i] && tieEntryFee <= chipStacks[i])
        {
            cout << "Player" << i + 1 << " do you want to join the TIE? You have to pay " << tieEntryFee << ". (y/n)" << endl;
            char answer;
            while (true)
            {
                cin >> answer;
                if (answer == 'y')
                {
                    chipStacks[i] -= tieEntryFee;
                    pot += tieEntryFee;
                    inGamePlayers[i] = true;
                    cout << endl;
                    break;
                }
                else if (answer == 'n')
                {
                    inGamePlayers[i] = false;
                    cout << endl;
                    break;
                }
                else
                {
                    cout << "Invalid input! Please enter 'y' for yes or 'n' for no." << endl;
                }
            }
        }
        else if(!winners[i] && tieEntryFee > chipStacks[i])
        {
            cout << "Player" << i + 1 << "does not have enougth chips to join the TIE." << endl;
            inGamePlayers[i] = false;
        }
        else if(winners[i])
        {
            inGamePlayers[i] = true;
        }
    }
    addChipsIfNotEnough(playersCount, inGamePlayers, chipStacks);
}

bool hasEveryoneNullChips(unsigned playersCount, const bool* inGamePlayers, const int* chipStacks)
{
    unsigned notNullChipStacks = 0;
    for (int i = 0; i < playersCount; i++)
    {
        if (inGamePlayers[i] && chipStacks[i] > 0)
        {
            notNullChipStacks++;
        }
    }
    if (notNullChipStacks == 0 || notNullChipStacks == 1)
    {
        return true;
    }
    return false;
}

bool isGameOver(const int* chipStacks, unsigned playersCount)
{
    unsigned notNullChips = 0;
    for (int i = 0; i < playersCount; i++)
    {
        if (chipStacks[i] != 0)
        {
            notNullChips++;
        }
    }

    if (notNullChips == 1)
    {
        return true;
    }
    return false;
}
unsigned getWinnerIndex(const int* chipStacks, unsigned playersCount)
{
    unsigned winnerIndex = 0;
    for (int i = 0; i < playersCount; i++)
    {
        if (chipStacks[i] > 0)
        {
            winnerIndex = i;
        }
    }
    return winnerIndex;
}
void printGameOver(const int* chipStacks, unsigned playersCount)
{
    cout << "Game over" << endl;
    cout << endl;
    cout << "Player" << getWinnerIndex(chipStacks, playersCount) + 1 << " wins" << endl;
}
