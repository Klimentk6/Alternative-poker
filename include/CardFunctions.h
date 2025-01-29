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
    srand(time(0));

    for (int i = CARDS_COUNT - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swapCards(cardsInDeck[i], cardsInDeck[j]);
    }
}

bool isSevenOfClubs(Card card)
{
    return card.rank == SEVEN && card.suit == CLUBS;
}

bool isTriple(const Card& first, const Card& second, const Card& third)
{
    return first.rank == second.rank && second.rank == third.rank;
}
unsigned calculateTriplePoints(const Card& first)
{
    if (first.rank == SEVEN)
    {
        return 34;
    }
    return RANK_POINTS[first.rank] * CARDS_PER_PLAYER;
}

bool isFlush(const Card& first, const Card& second, const Card& third)
{
    return first.suit == second.suit && second.suit == third.suit;
}
unsigned calculateFlushPoints(const Card& first, const Card& second, const Card& third)
{
    if (isSevenOfClubs(first) || isSevenOfClubs(second) || isSevenOfClubs(third))
    {
        return RANK_POINTS[first.rank] + RANK_POINTS[second.rank] + RANK_POINTS[third.rank] + RANK_POINTS[ACE] - RANK_POINTS[SEVEN];
    }
    return RANK_POINTS[first.rank] + RANK_POINTS[second.rank] + RANK_POINTS[third.rank];
}

bool isDoubleSeven(const Card& first, const Card& second, const Card& third)
{
    return (first.rank == SEVEN && second.rank == SEVEN) || (first.rank == SEVEN && third.rank == SEVEN) || (second.rank == SEVEN && third.rank == SEVEN);
}

bool isDoubleAce(const Card& first, const Card& second, const Card& third)
{
    return (first.rank == ACE && second.rank == ACE) || (first.rank == ACE && third.rank == ACE) || (second.rank == ACE && third.rank == ACE);
}

bool isPairWithSevenOfClubs(const Card& first, const Card& second, const Card& third)
{
    return (first.rank == second.rank && isSevenOfClubs(third)) || (first.rank == third.rank && isSevenOfClubs(second)) || (second.rank == third.rank && isSevenOfClubs(first));
}

unsigned calculatePairWithSevenPoints(const Card& first, const Card& second, const Card& third)
{
    if (first.rank == second.rank)
    {
        return RANK_POINTS[first.rank] * 2 + RANK_POINTS[ACE];
    }
    if (first.rank == third.rank)
    {
        return RANK_POINTS[first.rank] * 2 + RANK_POINTS[ACE];
    }
    return RANK_POINTS[second.rank] * 2 + RANK_POINTS[ACE];
}

bool isTwoCardsSameSuit(const Card& first, const Card& second, const Card& third)
{
    return first.suit == second.suit || first.suit == third.suit || second.suit == third.suit;
}

unsigned calculateSuitPoints(const Card& card1, const Card& card2, const Card& card3)
{
    if (isSevenOfClubs(card3))
    {
        return RANK_POINTS[card1.rank] + RANK_POINTS[card2.rank] + RANK_POINTS[ACE];
    }
    unsigned points = RANK_POINTS[card1.rank] + RANK_POINTS[card2.rank];
    if (isSevenOfClubs(card1) || isSevenOfClubs(card2))
    {
        points += RANK_POINTS[ACE] - RANK_POINTS[SEVEN];
    }
    return points;
}
unsigned calculateSameSuitPoints(const Card& first, const Card& second, const Card& third)
{
    if (first.suit == second.suit)
    {
        return calculateSuitPoints(first, second, third);
    }
    if (first.suit == third.suit)
    {
        return calculateSuitPoints(first, third, second);
    }
    return calculateSuitPoints(second, third, first);
}

unsigned myMax(unsigned a, unsigned  b, unsigned c) 
{
    return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
}
unsigned calculateHighestCardPoints(const Card& first, const Card& second, const Card& third)
{
    unsigned maxRank = myMax(first.rank, second.rank, third.rank);
    unsigned points = RANK_POINTS[maxRank];

    if (isSevenOfClubs(first) || isSevenOfClubs(second) || isSevenOfClubs(third))
    {
        points += RANK_POINTS[ACE];
    }
    return points;
}

unsigned calculatePlayerPoints(const Card& first, const Card& second, const Card& third)
{
    if (isTriple(first, second, third))
    {
        return calculateTriplePoints(first);
    }
    else if (isFlush(first, second, third))
    {
        return calculateFlushPoints(first, second, third);
    }
    else if (isDoubleSeven(first, second, third))
    {
        return 23;
    }
    else if (isDoubleAce(first, second, third))
    {
        return RANK_POINTS[ACE] * 2;
    }
    else if (isPairWithSevenOfClubs(first, second, third))
    {
        return calculatePairWithSevenPoints(first, second, third);
    }
    else if (isTwoCardsSameSuit(first, second, third))
    {
        return calculateSameSuitPoints(first, second, third);
    }
    else
    {
        return calculateHighestCardPoints(first, second, third);
    }
}
void calculatePoints(unsigned* points, const Card* deck, unsigned playersCount)
{
    for (unsigned i = 0; i < playersCount * CARDS_PER_PLAYER; i += CARDS_PER_PLAYER)
    {
        unsigned playerIndex = i / CARDS_PER_PLAYER;
        points[playerIndex] = calculatePlayerPoints(deck[i], deck[i + 1], deck[i + 2]);
    }
}
