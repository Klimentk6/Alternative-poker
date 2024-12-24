#pragma once

bool isValidNumberOfPlayers(unsigned numberOfPlayers)
{
    return numberOfPlayers >= MIN_PLAYERS_COUNT && numberOfPlayers <= MAX_PLAYERS_COUNT;
}
unsigned chooseNumberOfPlayers()
{
    cout << "How many players are going to play? (" << MIN_PLAYERS_COUNT << "-" << MAX_PLAYERS_COUNT << ")" << endl;

    unsigned numberOfPlayers;
    bool isValidInput = true;
    do
    {
        isValidInput = true;
        cin >> numberOfPlayers;
        if (cin.fail())
        {
            isValidInput = false;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!" << endl;
            cout << "Please enter a number between " << MIN_PLAYERS_COUNT << " and " << MAX_PLAYERS_COUNT << "." << endl;
        }
        else if (!isValidNumberOfPlayers(numberOfPlayers))
        {
            isValidInput = false;
            cout << "Invalid input!" << endl;
            cout << "Please enter a number between " << MIN_PLAYERS_COUNT << " and " << MAX_PLAYERS_COUNT << "." << endl;
        }
    } while (!isValidInput);

    cout << endl;

    return numberOfPlayers;
}

bool areGoingToPlayAgain()
{
    cout << endl;
    cout << "Do you want to play again? (y/n)" << endl;

    char yesOrNo;
    while (true)
    {
        cin >> yesOrNo;

        if (yesOrNo == 'y')
        {
            return true;
        }
        else if (yesOrNo == 'n')
        {
            return false;
        }
        else
        {
            cout << "Invalid input! Please enter 'y' for yes or 'n' for no. " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
