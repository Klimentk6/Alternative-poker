#include <iostream>
#include "Constants.hpp"
#include "InputFunctions.hpp"
#include "CardsFunctions.hpp"
#include "PointsFunctions.hpp"
#include "ChipsFunctions.hpp"

using namespace std;

int main()
{
    //Choose number of players
    unsigned playersCount = choosePlayersCount();

    //Initialize deck
    Card cardsInDeck[CARDS_COUNT];
    initializeDeck(cardsInDeck);

    //Initialize chip stacks
    int* chipStacks = new int[playersCount];
    initializeChipStacks(chipStacks, playersCount);

    //Game starts
    printGameStart();

    unsigned roundCount = 1;
    do
    {
        //Round starts
        printRoundStart(roundCount);

        //Shuffle deck
        shuffleDeck(cardsInDeck);

        //Calculate points
        unsigned* playersPoints = new unsigned[playersCount];
        calculatePlayersPoints(playersPoints, cardsInDeck, playersCount);
        printPoints(playersPoints, playersCount);

        //Create pot
        unsigned pot = 0;

        //Pay entry fee
        payEntryFee(chipStacks, playersCount, pot);
        printPlayersAndChipStacks(chipStacks, playersCount);
        printPot(pot);
        cout << endl;

        printDeck(cardsInDeck);

        
        /*while (true)
        {
            unsigned currentPlayer = 1;
            unsigned currentPlayerIndex = currentPlayer - 1;
            unsigned lastReise = 0;
            printPlayersCardsAndPoints(cardsInDeck, playersPoints, currentPlayerIndex);
            if (lastReise == 0)
            {
                cout << "Player" << currentPlayer << " raise or fold? (r/f)";
                char answer;
                cin >> answer;
            }
            else
            {
                cout << "Player" << currentPlayerIndex << " raise, call or fold? (r/c/f)";
                char answer;
                cin >> answer;
            }
        }*/






        //delete[] playersPoints;
        //roundCount++;

        if (!areGoingToPlayAgain())
        {
            break;
        }
    } while (true);

    //add chip stacks to a file

    delete[] chipStacks;

    return 0;
}
