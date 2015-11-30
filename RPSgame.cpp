/*
Student Number: 100999036
Student Name:	Austin Kirby
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
 
using namespace std;

/* For debugging perposes
* true =>  cout to console class variables on change
* false => do nothing
*/
bool	DEBUG = true;

string	PLAYER_NAME;
int		PLAYER_WINS;

class SAVE
{
public:
	string name = "";
	int wins;
} LOCAL_SAVE[12];

/* Input and output file names
* SAVE_FILE  ("save.txt")
*/
string SAVE_FILE = "save.txt";

void Init();

void GameLoop();

void Save();

void GetPlayerName();

void SortLocalSave();

void GetPlayerSpot();

void ShowSave();

void ChangeName();

void SavePlayer();

int Menu();

int GetLongestName();

int main()
{
	Init();
	GameLoop();
	Save();
	system("PAUSE");
    return 0;
}

void Init()
{
	ifstream inFile;
	string line;
	string name;
	int numWins;
	int i = 0;
	inFile.open(SAVE_FILE);
	if (inFile.good())
	{
		while (getline(inFile, line))
		{
			istringstream iss(line);
			iss >> name >> numWins;
			if (i == 0)
			{
				PLAYER_NAME = name;
				PLAYER_WINS = numWins;
			}
			LOCAL_SAVE[i].name = name;
			LOCAL_SAVE[i].wins = numWins;
			i++;
		}
		SortLocalSave();
	}
	else
	{
		ofstream file;
		file.open(SAVE_FILE);
		file.close();
		GetPlayerName();
		PLAYER_WINS = 0;
	}
}

void GameLoop()
{
	int choice;
	do
	{
		choice = Menu();
		switch (choice)
		{
		case 1:

			break;
		case 2:
			ChangeName();
			break;
		case 3:
			ShowSave();
			break;
		}
	} while (choice != 0);
}

void Save()
{
	int i = 0;
	ofstream file;
	SortLocalSave();
	file.open(SAVE_FILE);
	for (i = 0; i < 11; i++)
	{
		if (LOCAL_SAVE[i].name != "")
			file << LOCAL_SAVE[i].name << ' ' << LOCAL_SAVE[i].wins << endl;
	}
	file.close();
}

void GetPlayerName()
{
	string player;
	cout << "Please enter players name:" << endl << "==> ";
	cin >> player;
	PLAYER_NAME = player;
}

void SortLocalSave()
{
	int i, tmpWins = -1;
	for (i = 10; i > 0; i--)
	{
		if (LOCAL_SAVE[i].name != "")
		{
			if (tmpWins == -1)
				tmpWins = LOCAL_SAVE[i].wins;
			else if (LOCAL_SAVE[i].wins < tmpWins)
			{
				LOCAL_SAVE[11] = LOCAL_SAVE[i + 1];

				LOCAL_SAVE[i + 1] = LOCAL_SAVE[i];

				LOCAL_SAVE[i] = LOCAL_SAVE[11];

				SortLocalSave();
			}
		}
	}
}

void ShowSave()
{
	int longestName = GetLongestName();
	int i, z;
	cout << "Rank  Player Name" << setw(abs(11 - longestName)) << " No Wins" << endl;
	for (i = 0; i < 26; i++)
		cout << '-';
	cout << endl;
	for (i = 1; i < 11; i++)
	{
		cout << i << "    ";
		if (i != 10)
			cout << " ";

		if (LOCAL_SAVE[i].name != "")
		{
			cout << LOCAL_SAVE[i].name << setw(14 - LOCAL_SAVE[i].name.length());

			cout << LOCAL_SAVE[i].wins;
		}
		cout << endl;
	}
}

void ChangeName()
{
	string name = "";
	int i;
	do
	{
		cout << "Enter new name:" << endl << "==> ";
		cin >> name;
	} while (name == "");
	SavePlayer();
	PLAYER_NAME = name;
	PLAYER_WINS = 0;
	LOCAL_SAVE[0].name = name;
	for (i = 1; i < 11; i++)
	{
		if (PLAYER_NAME == LOCAL_SAVE[i].name)
		{
			PLAYER_WINS = LOCAL_SAVE[i].wins;
		}
	}
}

void SavePlayer()
{
	int i;
	for (i = 1; i < 11; i++)
	{
		if (PLAYER_NAME == LOCAL_SAVE[i].name)
		{
			LOCAL_SAVE[i].wins = PLAYER_WINS;
			i = 15;
		}
	}
	if (i != 15)
	{
		if (PLAYER_WINS > LOCAL_SAVE[10].wins)
		{
			LOCAL_SAVE[10].name = PLAYER_NAME;
			LOCAL_SAVE[10].wins = PLAYER_WINS;
		}
	}
	SortLocalSave();
}

int Menu()
{
	int i = -1;
	do
	{
		cout << "Current Player Name: <" << PLAYER_NAME << ">" << endl << endl;
		cout << "1 => Start the game" << endl;
		cout << "2 => Change the player name" << endl;
		cout << "3 => Show highest scores" << endl;
		cout << "0 => Exit" << endl << endl;
		cout << "What is your option?" << endl;
		cin >> i;
	} while (i < 0 || i > 3);
	return i;
}

int GetLongestName()
{
	int i, tmp = 0;
	for (i = 1; i < 11; i++)
		if (LOCAL_SAVE[i].name != "")
			if (LOCAL_SAVE[i].name.length() > tmp)
				tmp = LOCAL_SAVE[i].name.length();
	return tmp;
}