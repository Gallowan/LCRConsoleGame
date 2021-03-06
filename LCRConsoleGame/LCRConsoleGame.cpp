/**
 * Justin Galloway
 * Personal Project
 * - LCR Game -
 *
 * LCR, or Left Center Right, is a dice game for three or more players, 
 * published by George & Company LLC in 1992. It is entirely a game of chance. 
 * The players make no decisions of any kind, even as to wagering.
 *
 */

#include "pch.h"
#include <iostream>
#include "dice.h"
#include "divider.h"

#include "pch.h"
#include <string>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <fstream>

using namespace std;

// menuChoice - Listens for the main menu input and directs accordingly.
// diceValue - Value of the random roll happening in roller()
int menuChoice = 0, diceValue = 0;

// playerCount - Number of players entered in the menu
// roundNumber - Current round playing out
int playerCount = 0, roundNumber = 0;

// compareCount - Assists with allocating chips
// roundScore - Assists in counting chips in play
// winCounter - Checks if any of the players has won the game
// winnerNumber - The number of the player who has won the game. if any
int compareCount = 0, roundScore = 0, winCounter = 0, winnerNumber = 0;

// Strings determining variables and inputs.
string name = "", rules = "", inputHold = "";
bool winner = false;
// Vectors holding player number, score and name respectively.
vector<int> playerCode, playerScore;
vector<string> playerName;

// Gathers number of players and those players' names.
void mainMenu()
{
	do
	{
		cout << "Please enter the number of players!" << endl;
		cout << "Note: There must be at least *3* players." << endl;
		cin >> playerCount;
		if (!cin)
		{
			cin.clear();
			cout << "Okay, I'm pretty sure that was supposed to be a number. Care to try again?" << endl;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		compareCount = (playerCount - 1); // Helps determine where chips will go later.
		divider();
	} while (playerCount < 3);

	for (int i = 1; i < (playerCount + 1); i++) // Loops through respective to player count.
	{
		playerCode.push_back(i);
		cout << "Enter player " << i << "'s name!" << endl;
		cin >> name;
		playerName.push_back(name);
		playerScore.push_back(3);
		divider();
	}
}

// Rolls the die and returns a random value.
class roll
{
public:
	int diceRoll()
	{
		diceValue = rand() % 6 + 1;
		return diceValue;
	}
};

// Tells the dice class what to show for the round and where.
void diceView(int rolled)
{
	switch (rolled)
	{
	case 1:
	{
		dice left('L');
		left.show();
		break;
	}
	case 2:
	{
		dice center('C');
		center.show();
		break;
	}
	case 3:
	{
		dice right('R');
		right.show();
		break;
	}
	default:
	{
		dice dot('*');
		dot.show();
		break;
	}
	}
}

// Handles passing of chips to the left, center and right respectively
// "default" is a dot space on the dice.
void chipTransfer(int code, int rolled)
{
	switch (rolled)
	{
	case 1:
	{
		cout << playerName[code] << " tosses a chip to " << playerName[position(code - 1)] << "!... Bummer." << endl;
		playerScore[code] = playerScore[code] - 1;
		playerScore[position(code - 1)] = playerScore[position(code - 1)] + 1;
		break;
	}
	case 2:
	{
		cout << playerName[code] << " reluctantly slides a chip to the pot. Yikes." << endl;
		playerScore[code] = playerScore[code] - 1;
		break;
	}
	case 3:
	{
		cout << playerName[code] << " tosses a chip to " << playerName[position(code + 1)] << "!... Sucks." << endl;
		playerScore[code] = playerScore[code] - 1;
		playerScore[position(code + 1)] = playerScore[position(code + 1)] + 1;
		break;
	}
	default:
	{
		cout << "... nothing happens." << endl;
	}
	}
}

// Shows who is on the left and right of the current player
int position(int locator)
{
	if (locator < 0)
	{
		return compareCount;
	}
	else if (locator > compareCount)
	{
		return 0;
	}
	else
	{
		return locator;
	}
}

// Handles each players turn, including message, resetting the win counter, roll counter, etc.
// Case 0 - No roll
void turnHandler(int pTurn)
{
	roundScore = playerScore[pTurn];
	cout << "It's " << playerName[pTurn] << "'s turn." << endl;
	cout << "You've got " << playerScore[pTurn] << " chips, buddy." << endl;

	winCounter = 0;

	switch (playerScore[pTurn])
	{
	case 0:
	{
		cout << "No chips, no roll. Them's the rules. NEXT -" << endl;
		divider();
		break;
	}
	default:
	{
		cout << "You get " << playerScore[pTurn] << " rolls." << endl;
		cout << "Enter anything to roll." << endl;
		cin >> inputHold;

		// Reads the die, prints the value and handles the chip transfer, if any.
		for (int i = 0; i < roundScore; i++)
		{
			roll chance;
			diceValue = chance.diceRoll();
			diceView(diceValue);
			chipTransfer(pTurn, diceValue);
			divider();
		}
		// Checks for a winner after the turn.
		winCheck();
	}
	}
}

// Counts how many players have more than 0 chips, and listens to see if the game has ended.
void winCheck()
{
	// Take the winners number down to reference later.
	for (int i = 0; i < playerCount; i++)
	{
		if (playerScore[i] > 0)
		{
			winnerNumber = i;
			winCounter++;
		}
	}

	// Sets the state to the winning condition. Sets the victory message to the winning player.
	if (winCounter == 1)
	{
		winner = true;
		victory(winnerNumber);
	}
}

// Gives a congrats message to the winner!
void victory(int won)
{
	cout << playerName[won] << "is the winner! Time to gloat. Do it, " << playerName[won] << ". You've earned it." << endl;
}

// Loops through the players to continue the game.
void gameLoop()
{
	do 
	{
		cout << "Round " << ++roundNumber << "!" << endl;

		for (int i = 0; i < playerCount; i++)
		{
			if (winner == false)
			{
				turnHandler(i);
			}
		}
	} while (winner == false);
}

// Grabs the ruleset and prints it into the console!
// Wanted to test to see if I remembered filestreaming. I hardly did.
// Don't quote me on that though. I know everything, obviously.
void readRules()
{
	ifstream rulesFile("LCR_RuleSet.txt");
	if (rulesFile.fail())
		{
		cout << "File doesn't exist!" << endl;
		cin >> inputHold;
		std::exit;
		}

	while (!rulesFile.eof())
	{
		getline(rulesFile, rules);
		cout << rules << endl;
	}

	divider();
}

// Main class.
int main()
{
	srand((unsigned)time(0));

	cout << "|~-Left Center Right: The Movie: The Game-~|" << endl;
	divider();
	divider();
	do
	{
		cout << "Choose an Option..." << endl;
		cout << "1: I've never heard of this game. (Show me how to play, please.)" << endl;
		cout << "2: Let's start this up! [Charisma 30]" << endl;
		cout << "3: Exit program." << endl;

		cin >> menuChoice;
		divider();

		switch (menuChoice)
		{
		case 1:
		{
			readRules();
			break;
		}
		case 2:
		{
			mainMenu();
			gameLoop();
			break;
		}
		case 3:
		{
			std::exit;
		}
		}
	} while (menuChoice <= 1 || menuChoice > 3);
	cin >> inputHold;
	return 0;
}