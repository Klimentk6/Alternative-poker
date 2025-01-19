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
            cout << endl;
            return true;
        }
        else if (answer == 'n')
        {
            cout << endl;
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
        outputFile << playersCount << endl;
        outputFile << roundCount - 1 << endl;
        for (int i = 0; i < playersCount; i++)
        {
            outputFile << chipStacks[i] << endl;
        }
        outputFile.close();
    }
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
    int i = 0;
    while (inputFile.getline(line, FILE_LINE_LENGTH))
    {
        if (i == 0)
        {
            playersCount = myAtoiUnsigned(line);
            chipStacks = new int[playersCount];
        }
        else if (i == 1)
        {
            roundsCount = myAtoiUnsigned(line);
        }
        else
        {
            chipStacks[i - 2] = myAtoiUnsigned(line);
        }
        i++;
    }
}

void deleteFile()
{
    ifstream file("score.txt");

    if (!file) 
    {
        std::cout << "File does not exist" << std::endl;
    }
    else 
    {
        file.close(); 
        remove("score.txt");
    }
}
