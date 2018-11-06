/**
 * Justin Galloway
 * Personal Project
 * - LCR Game -
 *
 * | Dice Class |
 * Dice class for rolling. 
 *
 */

#include "pch.h"
#include "dice.h"
#include "divider.h"

#include <iostream>
using namespace std;

dice::dice(char rolled)
{
	face = rolled;
}

void dice::show()
{
	cout << "You rolled..." << endl;
	cout << "          _____" << endl << "         |     |" << endl;
	cout << "         |  " << face << "  |" << endl;
	cout << "         |_____|" << endl;
	divider();
}