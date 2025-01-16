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
        if (!isValidPlayersCount(playersCount))
        {
            cout << "Invalid input!" << endl;
            cout << "Please enter a number between " << MIN_PLAYERS_COUNT << " and " << MAX_PLAYERS_COUNT << "." << endl;
        }
        else
        {
            break;
        }
    }

    cout << endl;

    return playersCount;
}

bool areGoingToContinue()
{
    cout << "Do you want to continue your last game? (y/n)" << endl;
    char answer;
    while (true)
    {
        cin >> answer;
        if (answer == 'y')
        {
            return true;
        }
        else if (answer == 'n')
        {
            return false;
        }
        else
        {
            cout << "Invalid input! Please enter 'y' for yes or 'n' for no." << endl;
        }
    }
}

bool areGoingToPlayNewRound()
{
    cout << "Do you want to play again? (y/n)" << endl;

    char answer;
    while (true)
    {
        cin >> answer;
        if (answer == 'y')
        {
            return true;
        }
        else if (answer == 'n')
        {
            return false;
        }
        else
        {
            cout << "Invalid input! Please enter 'y' for yes or 'n' for no." << endl;
        }
    }
}

void saveInfoInAFile(int* chipStacks, unsigned playersCount, unsigned roundCount)
{
    ofstream outputFile;
    outputFile.open("score.txt");
    outputFile.clear();
    if (!outputFile)
    {
        cout << "Unable to open file." << endl;
    }
    else
    {
        outputFile << "Alternative poker" << endl;
        outputFile << endl;
        outputFile << "Number of players: " << playersCount << endl;
        outputFile << "Rounds played: " << roundCount - 1<< endl;
        outputFile << endl;
        outputFile << "Chip stacks" << endl;
        for (int i = 0; i < playersCount; i++)
        {
            outputFile << "Player" << i + 1 << ": " << chipStacks[i] << std::endl;
        }
        outputFile.close();
    }
}

bool isStringPrefix(const char* text1, const char* text2)
{
    while (*text2)
    {
        if (*text1 != *text2)
        {
            return false;
        }
        text1++;
        text2++;
    }
    return true;
}
unsigned stringLength(const char* text)
{
    unsigned result = 0;
    while (*text)
    {
        result++;
        text++;
    }
    return result;
}
unsigned myAtoiUnsigned(const char* text) {
    if (text == nullptr) 
    {
        return 0;
    }

    unsigned result = 0;
    while (*text >= '0' && *text <= '9') 
    {
        result *= 10;
        result += *text - '0';
        text++;
    }
    return result;
}

void getInfoFromFile(ifstream &inputFile, unsigned &playersCount, int* &chipStacks, unsigned &roundsCount)
{
    char line[FILE_LINE_LENGTH];
    while (inputFile.getline(line, FILE_LINE_LENGTH))
    {
        if (isStringPrefix(line, FILE_PLAYERS_COUNT_TEXT))
        {
            char* lineStart = line + stringLength(FILE_PLAYERS_COUNT_TEXT);
            playersCount = myAtoiUnsigned(lineStart);
            chipStacks = new int[playersCount];
        }
        else if (isStringPrefix(line, FILE_ROUNDS_TEXT))
        {
            char* lineStart = line + stringLength(FILE_ROUNDS_TEXT);
            roundsCount = myAtoiUnsigned(lineStart) + 1;
        }
        else if (isStringPrefix(line, FILE_PLAYER_TEXT))
        {
            char* ptrIndexStart = line + stringLength(FILE_PLAYER_TEXT);
            unsigned index = myAtoiUnsigned(ptrIndexStart) - 1;
            char* ptrChipsStart = line + stringLength(FILE_PLAYER_AND_NUMBER_TEXT);
            unsigned chips = myAtoiUnsigned(ptrChipsStart);
            chipStacks[index] = chips;
        }
    }
}

