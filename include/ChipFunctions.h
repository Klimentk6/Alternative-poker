#pragma once

using namespace std;

void initializeChipStacks(int* chipsArray, unsigned playersCount)
{
    for (unsigned player = 0; player < playersCount; player++)
    {
        chipsArray[player] = START_CHIPS_COUNT * CHIP_VALUE;
    }
}

void payEntryFee(int* chipStacks, unsigned* bets, unsigned playersCount, unsigned& pot)
{
    unsigned entryValue = ENTRY_CHIPS_COUNT * CHIP_VALUE;

    cout << "Entry fee: " << entryValue << endl;
    for (unsigned i = 0; i < playersCount; i++)
    {
        bets[i] += entryValue;
        chipStacks[i] -= entryValue;
        pot += entryValue;
    }
}

void printChipStacks(int* chipsArray, unsigned playersCount)
{
    for (unsigned player = 0; player < playersCount; player++)
    {
        if (player % 3 == 0 && player != 0)
        {
            cout << endl;
        }
        cout << "Player" << player + 1 << ": " << chipsArray[player] << ' ';
    }
    cout << endl << endl;
}

void printPlayerChipStack(int* chipStacks, unsigned currentPlayerIndex)
{
    cout << "Player" << currentPlayerIndex + 1 << " - " << chipStacks[currentPlayerIndex] << endl;
}

void printPot(unsigned pot)
{
    cout << "Pot: " << pot << endl;
}

void printLastRaise(unsigned lastRaise)
{
    cout << "Last raise: " << lastRaise << endl;
    cout << endl;
}

void printPlayerBet(unsigned* bets, unsigned currentPlayerIndex)
{
    cout << "You have given: " << bets[currentPlayerIndex] << endl;
}
