#pragma once

using namespace std;

void initializeChipStacks(int* chipsArray, unsigned playersCount)
{
    for (unsigned player = 0; player < playersCount; player++)
    {
        chipsArray[player] = START_CHIPS_COUNT * CHIP_VALUE;
    }
}
void intitializeInGamePlayers(bool* inGamePlayers, unsigned playersCount, const int* chipStacks)
{
    for (int i = 0; i < playersCount; i++)
    {
        if (chipStacks[i] == 0)
        {
            inGamePlayers[i] = false;
        }
        else
        {
            inGamePlayers[i] = true;
        }
    }
}
void initializeBets(unsigned* bets, unsigned playersCount)
{
    for (int i = 0; i < playersCount; i++)
    {
        bets[i] = 0;
    }
}
void initializePlayersCalled(bool* playersCalled, unsigned playersCount)
{
    for (int i = 0; i < playersCount; i++)
    {
        playersCalled[i] = false;
    }
}

void printRoundStart(unsigned roundCount)
{
    cout << "Round " << roundCount << endl;
}
void printChipStacks(const int* chipStacks, unsigned playersCount)
{
    for (unsigned i = 0; i < playersCount; i++)
    {
        if (i % 3 == 0 && i != 0)
        {
            cout << endl;
        }
        cout << "Player" << i + 1 << ": " << chipStacks[i] << ' ';
    }
    cout << endl;
}
void printPot(unsigned pot)
{
    cout << "Pot: " << pot << endl;
}
void printPlayerBets(const unsigned* bets, unsigned playerIndex)
{
    cout << "You have given: " << bets[playerIndex] << endl;
}
void printLastRaise(unsigned lastRaise)
{
    cout << "Last raise: " << lastRaise << endl;
}
void printPlayerChipStack(const int* chipStacks, unsigned playerIndex)
{
    cout << "Player" << playerIndex + 1 << " - " << chipStacks[playerIndex] << endl;
}
void printCard(Card card)
{
    cout << RANK_SYMBOLS[card.rank] << SUIT_SYMBOLS[card.suit] << ' ';
}
void printPlayersCardsAndPoints(const Card* deck, const unsigned* points, unsigned playerIndex)
{
    for (int i = playerIndex * CARDS_PER_PLAYER; i < playerIndex * CARDS_PER_PLAYER + CARDS_PER_PLAYER; i++)
    {
        printCard(deck[i]);
    }
    cout << "- " << points[playerIndex] << " points" << endl;
}
void printPlayerInfo(unsigned roundsCount, const int* chipStacks, unsigned playersCount, unsigned pot, const unsigned* bets, unsigned playerIndex, unsigned lastRaise, const Card* deck, const unsigned* points)
{
    printRoundStart(roundsCount);
    cout << endl;
    printChipStacks(chipStacks, playersCount);
    cout << endl;
    printPot(pot);
    cout << endl;
    printPlayerBets(bets, playerIndex);
    printLastRaise(lastRaise);
    cout << endl;
    printPlayerChipStack(chipStacks, playerIndex);
    printPlayersCardsAndPoints(deck, points, playerIndex);
}

void payEntryFee(int* chipStacks, unsigned playersCount, unsigned& pot, bool* inGamePlayers)
{
    unsigned entryFee = ENTRY_CHIPS_COUNT * CHIP_VALUE;
    for (unsigned i = 0; i < playersCount; i++)
    {
        if (chipStacks[i] >= entryFee)
        {
            chipStacks[i] -= entryFee;
            pot += entryFee;
        }
        else
        {
            inGamePlayers[i] = false;
        }
    }
}



unsigned heighestPosibleRaise(const int* chipStacks, unsigned playersCount, unsigned playerIndex, const bool* inGamePlayers)
{
    unsigned result = START_CHIPS_COUNT * CHIP_VALUE * playersCount;
    for (int i = 0; i < playersCount; i++)
    {
        if (result > chipStacks[i] && inGamePlayers[i])
        {
            result = chipStacks[i];
        }
    }
    return result;
}
bool isRaiseAllowed(unsigned lastRaise, unsigned playerIndex, int* chipStacks, unsigned playersCount, const bool* inGamePlayers)
{
    if (heighestPosibleRaise(chipStacks, playersCount, playerIndex, inGamePlayers) < lastRaise + CHIP_VALUE)
    {
        return false;
    }
    return true;
}
bool isValidRaise(unsigned raiseValue, unsigned lastRaise, unsigned playerIndex, const int* chipStacks, unsigned playersCount, const bool* inGamePlayers)
{
    if (raiseValue < lastRaise + CHIP_VALUE)
    {
        return false;
    }
    else if (raiseValue > heighestPosibleRaise(chipStacks, playersCount, playerIndex, inGamePlayers))
    {
        return false;
    }
    return true;
}
void playerRaises(unsigned playerIndex, int* chipStacks, unsigned* bets, unsigned& pot, unsigned& lastRaise, unsigned& lastPlayerRaisedIndex, unsigned playersCount, const bool* inGamePlayers, bool* playersCalled)
{
    unsigned raiseValue;
    while (true)
    {
        cout << "Raise: ";
        cin >> raiseValue;
        if (!isValidRaise(raiseValue, lastRaise, playerIndex, chipStacks, playersCount, inGamePlayers))
        {
            cout << "Invalid input!" << endl;
            cout << "Please enter a number between " << lastRaise + CHIP_VALUE << " and " << heighestPosibleRaise(chipStacks, playersCount, playerIndex, inGamePlayers) << "." << endl;
        }
        else
        {
            break;
        }
    }

    lastPlayerRaisedIndex = playerIndex;
    chipStacks[playerIndex] -= raiseValue;
    bets[playerIndex] += raiseValue;
    pot += raiseValue;
    lastRaise = raiseValue;

    initializePlayersCalled(playersCalled, playersCount);
    playersCalled[playerIndex] = true;

    cout << "Player" << playerIndex + 1 << " raises " << raiseValue << endl;
    cout << endl;
}

bool isCallAllowed(unsigned lastRaise, const unsigned* bets, unsigned playerIndex)
{
    if (lastRaise > bets[playerIndex])
    {
        return true;
    }
    return false;
}
void playerCalls(unsigned playerIndex, unsigned lastPlayerRaisedIndex, int* chipStacks, unsigned* bets, unsigned& pot, unsigned lastRaise, bool* playersCalled)
{
    unsigned callValue = bets[lastPlayerRaisedIndex] - bets[playerIndex];
    bets[playerIndex] += callValue;
    pot += callValue;
    chipStacks[playerIndex] -= callValue;
    playersCalled[playerIndex] = true;
    cout << endl;
}

void playerFolds(unsigned playerIndex, bool* inGamePlayers)
{
    inGamePlayers[playerIndex] = false;
}

void raiseCallOrFold(bool* inGamePlayers, int* chipStacks, unsigned* bets, unsigned& pot, unsigned& lastRaise, unsigned playerIndex, unsigned& lastPlayerRaisedIndex, unsigned playersCount, bool* playersCalled)
{
    bool raiseAllowed = isRaiseAllowed(lastRaise, playerIndex, chipStacks, playersCount, inGamePlayers);
    bool callAllowed = isCallAllowed(lastRaise, bets, playerIndex);
    if (raiseAllowed && !callAllowed)
    {
        cout << "Raise or fold? (r/f)" << endl;
    }
    else if (!raiseAllowed && callAllowed)
    {
        cout << "Call or fold? (c/f)" << endl;
    }
    else if(raiseAllowed && callAllowed)
    {
        cout << "Raise, call or fold? (r/c/f)" << endl;
    }
    else
    {
        cout << "Fold? (f)" << endl;
    }

    char action;
    while (true)
    {
        cin >> action;
        if (action == 'f')
        {
            playerFolds(playerIndex, inGamePlayers);
            break;
        }
        else if ((action == 'r') && raiseAllowed)
        {
            playerRaises(playerIndex, chipStacks, bets, pot, lastRaise, lastPlayerRaisedIndex,playersCount, inGamePlayers, playersCalled);
            break;
        }
        else if ((action == 'c') && callAllowed)
        {
            playerCalls(playerIndex, lastPlayerRaisedIndex, chipStacks, bets, pot, lastRaise, playersCalled);
            break;
        }
        else if(!callAllowed && raiseAllowed)
        {
            cout << "Invalid input!" << endl;
            cout << "Please enter 'r' for raise or 'f' for fold." << endl;
        }
        else if(callAllowed && raiseAllowed)
        {
            cout << "Invalid input!" << endl;
            cout << "Please enter 'r' for raise, 'f' for fold or 'c' for call." << endl;
        }
        else if (callAllowed && !raiseAllowed)
        {
            cout << "Invalid input!" << endl;
            cout << "Please enter 'c' for call or 'f' for fold." << endl;
        }
        else
        {
            cout << "Invalid input!" << endl;
            cout << "Please enter 'f' for fold." << endl;
        }
    }
}

