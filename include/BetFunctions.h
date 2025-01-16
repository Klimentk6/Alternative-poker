#pragma once

void printGameStart()
{
    cout << "Game starts" << endl;
}
void printRoundStart(unsigned roundCount)
{
    cout << endl;
    cout << "Round " << roundCount << endl;
    cout << endl;
}

void intitializeInGamePlayers(bool* inGamePlayers, unsigned playersCount)
{
    for (int i = 0; i < playersCount; i++)
    {
        inGamePlayers[i] = true;
    }
}
void initializeBets(unsigned* bets, unsigned playersCount)
{
    for (int i = 0; i < playersCount; i++)
    {
        bets[i] = 0;
    }
}

bool isValidRaise(unsigned raiseValue, unsigned lastRaise, unsigned currentPlayerIndex, const int* chipStacks)
{
    if (raiseValue < lastRaise * 2)
    {
        return false;
    }
    else if (raiseValue % CHIP_VALUE != 0)
    {
        return false;
    }
    else if (raiseValue > chipStacks[currentPlayerIndex])
    {
        return false;
    }
}
void playerRaises(unsigned currentPlayerIndex, int* chipStacks, unsigned* bets, unsigned& pot, unsigned& lastRaise, unsigned& lastPlayerRaisedIndex, unsigned playersCount)
{
    unsigned raiseValue;
    while (true)
    {
        cout << "Raise: ";
        cin >> raiseValue;
        if (!isValidRaise(raiseValue, lastRaise, currentPlayerIndex, chipStacks))
        {
            cout << "Invalid input!" << endl;
            cout << "Enter a value beatween " << lastRaise * 2 << " and " << chipStacks[currentPlayerIndex] << " and divisible by " << CHIP_VALUE << "." << endl;
        }
        else
        {
            break;
        }
    }

    lastPlayerRaisedIndex = currentPlayerIndex;
    chipStacks[currentPlayerIndex] -= raiseValue;
    bets[currentPlayerIndex] += raiseValue;
    pot += raiseValue;
    lastRaise = raiseValue;

    cout << "Player" << currentPlayerIndex + 1 << " raises " << raiseValue << endl;
    cout << endl;
}
void playerCalls(unsigned currentPlayerIndex, unsigned lastPlayerRaisedIndex, int* chipStacks, unsigned* bets, unsigned& pot, unsigned lastRaise)
{
    unsigned callValue = bets[lastPlayerRaisedIndex] - bets[currentPlayerIndex];
    if (callValue > chipStacks[currentPlayerIndex])
    {
        bets[currentPlayerIndex] += chipStacks[currentPlayerIndex];
        
    }
    else
    {
        chipStacks[currentPlayerIndex] -= callValue;
        bets[currentPlayerIndex] += callValue;
        pot += callValue;
        cout << "Player" << currentPlayerIndex + 1 << " calls " << callValue << endl;
    }
    cout << endl;
}
void playerFolds(unsigned currentPlayerIndex, bool* inGamePlayers, unsigned& inGamePlayersCount)
{
    inGamePlayers[currentPlayerIndex] = false;
    inGamePlayersCount--;
    cout << "Player" << currentPlayerIndex + 1 << " folds" << endl;
    cout << endl;
}
void raiseCallOrFold(bool* inGamePlayers, int* chipStacks, unsigned& inGamePlayersCount, unsigned* bets, unsigned& pot, unsigned& lastRaise, unsigned currentPlayerIndex, unsigned& lastPlayerRaisedIndex, unsigned playersCount)
{
    char action;
    if (lastRaise == 0)
    {
        cout << "Raise or fold? (r/f)" << endl;
    }
    else
    {
        cout << "Raise, call or fold? (r/c/f)" << endl;
    }
    while (true)
    {
        cin >> action;
        if (action == 'f')
        {
            playerFolds(currentPlayerIndex, inGamePlayers, inGamePlayersCount);
            break;
        }
        else if (action == 'r')
        {
            playerRaises(currentPlayerIndex, chipStacks, bets, pot, lastRaise, lastPlayerRaisedIndex,playersCount);
            break;
        }
        else if ((action == 'c') && (lastRaise != 0))
        {
            playerCalls(currentPlayerIndex, lastPlayerRaisedIndex, chipStacks, bets, pot, lastRaise);
            break;
        }
        else if(lastRaise == 0)
        {
            cout << "Invalid input!" << endl;
            cout << "Please enter 'r' for raise or 'f' for fold." << endl;
        }
        else
        {
            cout << "Invalid input!" << endl;
            cout << "Please enter 'r' for raise, 'f' for fold or 'c' for call." << endl;
        }
    }
}

unsigned nextPlayerIndex(unsigned currentPlayerIndex, unsigned playersCount, const bool* inGamePlayers)
{
    do
    {
        currentPlayerIndex++;
        if (currentPlayerIndex == playersCount)
        {
            currentPlayerIndex = 0;
        }
    } while (inGamePlayers[currentPlayerIndex] == false);

    return currentPlayerIndex;
}
bool hasEveryneCalled(const unsigned* bets, const bool* inGamePlayers, unsigned playersCount, unsigned currentPlayerIndex)
{
    unsigned everyBet = bets[nextPlayerIndex(currentPlayerIndex, playersCount, inGamePlayers)];
    if (everyBet == ENTRY_CHIPS_COUNT * CHIP_VALUE)
    {
        return false;
    }
    for (unsigned i = 0; i < playersCount; i++)
    {
        if (bets[i] != everyBet && inGamePlayers[i])
        {
            return false;
        }
    }
    return true;
}
