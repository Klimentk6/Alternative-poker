# Alternative-poker

<img src="images/sevenOfClubs.png" alt="" width="200"/>

## Overview
This is a competitive card game that can be played by 2 to 9 players. The game uses only cards from 7 to Ace. At the beginning of each game, three cards are dealt to each player. The goal is to determine the winner based on the value of their cards. The value is calculated as the sum of the card values, with specific rules for card values that can be predefined (described in the game rules section).

## Features
- Multiplayer support (2 to 9 players).
- Uses a deck from 7 to Ace.
- Round-based gameplay with betting mechanics.
- Strategic elements combined with luck.

## Gameplay
The game progresses in rounds. In each round:
1. Players review their cards and place their bets.
2. After all bets are placed, the players reveal their cards.
3. The player with the highest total wins the round.
4. If there are multiple players with the same highest total, the game enters a \"tie\" mode where players compete for the already placed points.

The game can continue for several rounds, and the overall winner is the player with the highest total score after a predetermined number of rounds.

## Codebase Details
- Language: C++ (console-based application).
- Dependencies: None required; the game runs with standard C++ libraries.
