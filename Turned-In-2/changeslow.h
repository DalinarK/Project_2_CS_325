/******************************************************************************************
** Header file for changeslow.
** Provides a function changeslow that will return the minimum number of coins from a set
** V to make change for a value A.
** Function will iterate through every possible combination of coins to make change for
** A.
** Algorithm will recursively iterate through the set of coins and check each coin is
** less than the param A, calling the function again if coin is lower on A - coin amount.
** When A is <= 0, base case is reached and returns 0.
******************************************************************************************/

#ifndef _CHANGESLOW_H
#define _CHANGESLOW_H


#include <vector>
#include <limits.h>
#include <iostream>

/**************************************************************
 * *  Struct to represent set of change
 * ***************************************************************/

struct CS
{
	int numberCoins;
	std::vector<int> actualCoins;
	//CS(){sum = std::numeric_limits<int>::min(); start = 0; end = 0;}
};

//Function prototype
int changeslow(std::vector<int> &coinSet, int coinSetValue, std::vector<int> &actualCoinsUsed);
void recursiveBrute(int coinSetValue, std::vector<int> coinSet, CS &minimumCoinSet, CS currentCoinSet );

#endif
