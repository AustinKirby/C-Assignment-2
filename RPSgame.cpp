/*
Student Number: 100999036
Student Name:	Austin Kirby
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
 
using namespace std;

#pragma region SAVE class

/*	Class SAVE
*	name	string		used to store player name
*	wins	int			used to store player wins
*/
class SAVE
{
public:
	string name = "";
	int wins;
} LOCAL_SAVE[12];

#pragma endregion

#pragma region Global Variables

/*	Save file name
*	SAVE_FILE	("save.txt")
*/
string SAVE_FILE = "save.txt";

/*	Store current player variables
*/
string	PLAYER_NAME;
int		PLAYER_WINS;

#pragma endregion

#pragma region Method Declaration

/*	Used to load values from save file.
*	Called at start of program.
*/
void Init();

/*	Used to control the four stages of game. [ Menu, Leaderboard, Game, Quit ]
*	Called after the Init method.
*/
void GameLoop();

/*	Used to write to save file.
*	Called on quiting of the game.
*/
void Save();

/*	Used to gather player's name.
*	Called if there is no save file when Init method is ran.
*/
void GetPlayerName();

/*	Used to sort the local save array of players.
*	Called when the local save array is changed.
*/
void SortLocalSave();

/*	Used to find current player's position in the save array.
*
*/
void GetPlayerSpot();

/*	Used to show the player the local save array.
*	Called when player enters 3 in menu method.
*/
void ShowSave();

/*	Used to change the players name.
*	Called when 2 is entered in Menu method.
*/
void ChangeName();

/*	Used to save player to the local save array.
*	Called when plaver is changed.
*/
void SavePlayer();

/*	Used to play Rock Papers Sissors.
*	Called in GameMenu and Menu.
*/
void Game();

/*	Used to gather player input for playing the game again.
*	Called in Menu method.
*/
void GameMenu();

/*	Used to get player input on which game state they would like to be in. [ Menu, Leaderboard, Game, Quit ]
*	Called in GameLoop.
*/
int Menu();

/*	Used to retreive the length of the longest name in the local save array.
*	Called in ShowLocalSave method.
*/
int GetLongestName();

#pragma endregion

int main()
{
	// Seed the random
	srand(time(NULL));

	// Load from the save file
	Init();

	// Run main game loop
	GameLoop();

	// Save local array
	Save();

	system("PAUSE");
    return 0;
}

#pragma region Prototype

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
			Game();
			GameMenu();
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
	cout << endl << "Rank  Player Name" << setw(abs(11 - longestName)) << " No Wins" << endl;
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
	cout << endl;
	system("PAUSE");
}

void ChangeName()
{
	string name = "";
	int i;
	do
	{
		cout << "Enter new name:" << endl << "==> ";
		cin.clear();
		fflush(stdin);
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
	LOCAL_SAVE[0].wins = PLAYER_WINS;
}

void SavePlayer()
{
	int i;
	bool found = false;
	for (i = 1; i < 11; i++)
	{
		if (PLAYER_NAME == LOCAL_SAVE[i].name)
		{
			LOCAL_SAVE[i].wins = PLAYER_WINS;
			found = true;
		}
	}
	if (!found)
	{
		for (i = 1; i < 11; i++)
		{
			if (LOCAL_SAVE[i].name == "")
			{
				LOCAL_SAVE[i].name = PLAYER_NAME;
				LOCAL_SAVE[i].wins = PLAYER_WINS;
				found = true;
				break;
			}
		}
		if (!found && LOCAL_SAVE[10].wins < PLAYER_WINS)
		{
			LOCAL_SAVE[10].name = PLAYER_NAME;
			LOCAL_SAVE[10].wins = PLAYER_WINS;
		}
	}
	SortLocalSave();
}

void Game()
{
	char s = 'a';
	do
	{
		cout << endl << "Choose your weapon!" << endl;
		cout << "r => Rock" << endl;
		cout << "p => Paper" << endl;
		cout << "s => Sissors" << endl;
		cout << "==> ";
		cin.clear();
		fflush(stdin);
		cin >> s;
	} while (s != 'r' && s != 'p' && s != 's');
	switch (rand() % 3 + 1)
	{
	case 3:  // rock
		if (s == 'p')
		{
			PLAYER_WINS++;
			LOCAL_SAVE[0].wins++;
			cout << "You won!" << endl;
			SavePlayer();
		}
		else
			cout << "You didn't win." << endl;
		break;
	case 2:  // paper
		if (s == 's')
		{
			PLAYER_WINS++;
			LOCAL_SAVE[0].wins++;
			cout << "You won!" << endl;
			SavePlayer();
		}
		else
			cout << "You didn't win." << endl;
		break;
	case 1:  // sissor
		if (s == 'r')
		{
			PLAYER_WINS++;
			LOCAL_SAVE[0].wins++;
			cout << "You won!" << endl;
			SavePlayer();
		}
		else
			cout << "You didn't win." << endl;
		break;
	}
}

void GameMenu()
{
	char s = 'a';
	do
	{
		cout << "Play again? [ y / n ]" << endl << "==> ";
		cin.clear();
		fflush(stdin);
		cin >> s;
	} while (s != 'y' && s != 'n');
	if (s == 'y')
	{
		Game();
		GameMenu();
	}
}

int Menu()
{
	int i = -1;
	do
	{
		system("cls");
		cout << "Current Player Name: <" << PLAYER_NAME << ">" << endl << endl;
		cout << "1 => Start the game" << endl;
		cout << "2 => Change the player name" << endl;
		cout << "3 => Show highest scores" << endl;
		cout << "0 => Exit" << endl << endl;
		cout << "What is your option?" << endl;
		cin.clear();
		fflush(stdin);
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

#pragma endregion