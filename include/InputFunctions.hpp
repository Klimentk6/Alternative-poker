#pragma once

using namespace std;

bool isValidPlayersCount(unsigned playersCount)
{
    return playersCount >= MIN_PLAYERS_COUNT && playersCount <= MAX_PLAYERS_COUNT;
}
unsigned choosePlayersCount()
{
    cout << "How many players are going to play? (" << MIN_PLAYERS_COUNT << "-" << MAX_PLAYERS_COUNT << ")" << endl;

    unsigned playersCount;
    while (true)
    {
        cin >> playersCount;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!" << endl;
            cout << "Please enter a number between " << MIN_PLAYERS_COUNT << " and " << MAX_PLAYERS_COUNT << "." << endl;
        }
        else if (!isValidPlayersCount(playersCount))
        {
            cout << "Invalid input!" << endl;
            cout << "Please enter a number between " << MIN_PLAYERS_COUNT << " and " << MAX_PLAYERS_COUNT << "." << endl;
        }
        else
        {   
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    cout << endl;

    return playersCount;
}

bool areGoingToPlayAgain()
{
    cout << "Do you want to play again? (y/n)" << endl;

    char playAgain;
    while (true)
    {
        cin >> playAgain;

        if (playAgain == 'y')
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return true;
        }
        else if (playAgain == 'n')
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return false;
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter 'y' for yes or 'n' for no. " << endl;
        }
    }
}
