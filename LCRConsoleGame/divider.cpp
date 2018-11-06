/**
 * Justin Galloway
 * Personal Project
 * - LCR Game -
 *
 * | Divider Class |
 * Creates a divider that's called to separate
 * lines throughout the console. Simple, probably
 * didn't need to be separated.
 *
 */

#include "pch.h"
#include "divider.h"

#include <iostream>
using namespace std;

divider::divider()
{
	for (int i = 0; i < 40; i++)
	{
		cout << "-";
	}
	cout << endl;
}