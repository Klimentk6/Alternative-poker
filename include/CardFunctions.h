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
void calculatePoints(unsigned* points, const Card* deck, unsigned playersCount)
{
    for (unsigned i = 0; i < playersCount * CARDS_PER_PLAYER; i += CARDS_PER_PLAYER)
    {
        unsigned playerIndex = i / CARDS_PER_PLAYER;
        unsigned playersPoints = 0;

        Card first = deck[i];
        Card second = deck[i + 1];
        Card third = deck[i + 2];

        if (first.rank == second.rank && second.rank == third.rank)
        {
            if (first.rank == SEVEN)
            {
                playersPoints = 34;
            }
            else
            {
                playersPoints = RANK_POINTS[first.rank] * CARDS_PER_PLAYER;
            }
        }
        else if (first.suit == second.suit && second.suit == third.suit)
        {
            if (isSevenOfClubs(first) || isSevenOfClubs(second) || isSevenOfClubs(third))
            {
                playersPoints = RANK_POINTS[first.rank] + RANK_POINTS[second.rank] + RANK_POINTS[third.rank] + RANK_POINTS[ACE] - RANK_POINTS[SEVEN];
            }
            else
            {
                playersPoints = RANK_POINTS[first.rank] + RANK_POINTS[second.rank] + RANK_POINTS[third.rank];
            }
        }
        else if (first.rank == SEVEN && second.rank == SEVEN)
        {
            playersPoints = 23;
        }
        else if (first.rank == SEVEN && third.rank == SEVEN)
        {
            playersPoints = 23;
        }
        else if (second.rank == SEVEN && third.rank == SEVEN)
        {
            playersPoints = 23;
        }
        else if (first.rank == ACE && second.rank == ACE)
        {
            playersPoints = RANK_POINTS[ACE] * 2;
        }
        else if (first.rank == ACE && third.rank == ACE)
        {
            playersPoints = RANK_POINTS[ACE] * 2;
        }
        else if (second.rank == ACE && third.rank == ACE)
        {
            playersPoints = RANK_POINTS[ACE] * 2;
        }
        else if (first.rank == second.rank && isSevenOfClubs(third))
        {
            playersPoints = RANK_POINTS[first.rank] * 2 + RANK_POINTS[ACE];
        }
        else if (first.rank == third.rank && isSevenOfClubs(second))
        {
            playersPoints = RANK_POINTS[first.rank] * 2 + RANK_POINTS[ACE];
        }
        else if (second.rank == third.rank && isSevenOfClubs(first))
        {
            playersPoints = RANK_POINTS[second.rank] * 2 + RANK_POINTS[ACE];
        }
        else if (first.suit == second.suit)
        {
            if (isSevenOfClubs(third))
            {
                playersPoints = RANK_POINTS[first.rank] + RANK_POINTS[second.rank] + RANK_POINTS[ACE];
            }
            else
            {
                playersPoints = RANK_POINTS[first.rank] + RANK_POINTS[second.rank];
                if (isSevenOfClubs(first) || isSevenOfClubs(second))
                {
                    playersPoints += RANK_POINTS[ACE] - RANK_POINTS[SEVEN];
                }
            }
        }
        else if (first.suit == third.suit)
        {
            if (isSevenOfClubs(second))
            {
                playersPoints = RANK_POINTS[first.rank] + RANK_POINTS[third.rank] + RANK_POINTS[ACE];
            }
            else
            {
                playersPoints = RANK_POINTS[first.rank] + RANK_POINTS[third.rank];
                if (isSevenOfClubs(first) || isSevenOfClubs(third))
                {
                    playersPoints += RANK_POINTS[ACE] - RANK_POINTS[SEVEN];
                }
            }
        }
        else if (second.suit == third.suit)
        {
            if (isSevenOfClubs(first))
            {
                playersPoints = RANK_POINTS[second.rank] + RANK_POINTS[third.rank] + RANK_POINTS[ACE];
            }
            else
            {
                playersPoints = RANK_POINTS[second.rank] + RANK_POINTS[third.rank];
                if (isSevenOfClubs(second) || isSevenOfClubs(third))
                {
                    playersPoints += RANK_POINTS[ACE] - RANK_POINTS[SEVEN];
                }
            }
        }
        else
        {
            if (first.rank > second.rank && first.rank > third.rank)
            {
                if (isSevenOfClubs(second) || isSevenOfClubs(third))
                {
                    playersPoints = RANK_POINTS[first.rank] + RANK_POINTS[ACE];
                }
                else
                {
                    playersPoints = RANK_POINTS[first.rank];
                }
            }
            else if (second.rank > first.rank && second.rank > third.rank)
            {
                if (isSevenOfClubs(first) || isSevenOfClubs(third))
                {
                    playersPoints = RANK_POINTS[second.rank] + RANK_POINTS[ACE];
                }
                else
                {
                    playersPoints = RANK_POINTS[second.rank];
                }
            }
            else if (third.rank > second.rank && third.rank > first.rank)
            {
                if (isSevenOfClubs(first) || isSevenOfClubs(second))
                {
                    playersPoints = RANK_POINTS[third.rank] + RANK_POINTS[ACE];
                }
                else
                {
                    playersPoints = RANK_POINTS[third.rank];
                }
            }
            else
            {
                int maxRank = 0;
                if (first.rank >= maxRank)
                {
                    maxRank = first.rank;
                }
                if (second.rank >= maxRank)
                {
                    maxRank = second.rank;
                }
                if (third.rank >= maxRank)
                {
                    maxRank = third.rank;
                }
                playersPoints = RANK_POINTS[maxRank];
            }
        }

        points[playerIndex] = playersPoints;
    }
}

