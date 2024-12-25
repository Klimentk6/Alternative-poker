#pragma once

using namespace std;

void initializeDeck(Card* cardsInDeck)
{
    for (unsigned rank = 0; rank < RANKS_COUNT; rank++)
    {
        for (unsigned suit = 0; suit < SUITS_COUNT; suit++)
        {
            *cardsInDeck = { rank, suit };
            cardsInDeck++;
        }
    }
}

void swapCards(Card& card1, Card& card2)
{
    Card temp = card1;
    card1 = card2;
    card2 = temp;
}
void shuffleDeck(Card* cardsInDeck)
{
    unsigned int seed = static_cast<unsigned int>(std::time(0));

    for (int i = CARDS_COUNT - 1; i > 0; --i)
    {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        int randomIndex = seed % (i + 1);

        swapCards(cardsInDeck[i], cardsInDeck[randomIndex]);
    }
}

bool isSevenOfClubs(Card card)
{
    return card.rank == SEVEN && card.suit == CLUBS;
}

void printCard(Card card)
{
    cout << RANK_SYMBOLS[card.rank] << SUIT_SYMBOLS[card.suit] << ' ';
}
void printDeck(const Card* cardsInDeck)
{
    for (int i = 0; i < CARDS_COUNT; i++)
    {
        printCard(cardsInDeck[i]);
    }
    cout << endl;
}
