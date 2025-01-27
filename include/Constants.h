#pragma once

const unsigned MIN_PLAYERS_COUNT = 2;
const unsigned MAX_PLAYERS_COUNT = 9;

struct Card
{
    unsigned rank;
    unsigned suit;
};

enum RankIndexes
{
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
};
enum SuitIndexes
{
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

const char RANK_SYMBOLS[] = { '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };
const char SUIT_SYMBOLS[] = { 'C', 'D', 'H', 'S' };
const unsigned RANK_POINTS[] = { 7, 8, 9, 10, 10, 10, 10, 11 };

const unsigned RANKS_COUNT = 8;
const unsigned SUITS_COUNT = 4;
const unsigned CARDS_COUNT = RANKS_COUNT * SUITS_COUNT;

const unsigned CHIP_VALUE = 10;
const unsigned START_CHIPS_COUNT = 100;
const unsigned ENTRY_CHIPS_COUNT = 1;

const unsigned CARDS_PER_PLAYER = 3;

const unsigned FILE_LINE_LENGTH = 100;
