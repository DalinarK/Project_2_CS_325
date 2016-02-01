#include "changeslow.h"

/**************************************************************
 * *  Function name: change slow
 * *  Parameters: Vector of coin set, int representing V, Vector of actual coins in set
 * *  Brute force method 
 * *  Return value: minimum number coins to create V change
 * *  Description: This algorithm can be viewed as divide-and-conquer, or as brute force.  
 * *  This solution is very recursive and runs in exponential time.
 * *  Credit: http://www.geeksforgeeks.org/find-minimum-number-of-coins-that-make-a-change/
 * *  http://romanenco.com/coin-change-problem/
 * ***************************************************************/
int changeslow(std::vector<int> &coinSet, int coinSetValue, std::vector<int> &actualCoinsUsed)
{
   	/* CS struct consists of int representing coin set amount and int vector representing actual coins in a coin set */
	CS minimumCoinSet;
	/* Create and initialize coin set objects representing current and minimum coin sets for use in helper function */
	for ( unsigned int i = 0; i < coinSet.size(); i++ )
	{
		minimumCoinSet.actualCoins.push_back(0);
	}
	/* Initialize solution for minimum number of coins to make V change to infinity */
	minimumCoinSet.numberCoins = INT_MAX;	//algorithm library has constant for max
	CS currentCoinSet;
	for ( unsigned int i = 0; i < coinSet.size(); i++ )
	{
		currentCoinSet.actualCoins.push_back(0);
	}
	/* Since this coin set will be the current one being tested against the min, initalize it to 0 amount coins */
	currentCoinSet.numberCoins = 0;
	/* Call recursive helper function to run brute force algorithm */
	recursiveBrute( coinSetValue, coinSet, minimumCoinSet, currentCoinSet );
	/* Once the recursive helper function has returned the minimum solution, record the actual coins in the minimum solution coin set */
	for ( unsigned int i = 0; i < coinSet.size(); i++ )
	{
		actualCoinsUsed.push_back( minimumCoinSet.actualCoins[i] );
	}
	/* Return the minimum number of coins to make V change */
	return minimumCoinSet.numberCoins;

}

/**************************************************************
 * *  Function name: recursive brute
 * *  Parameters: Vector of coin set, int representing V, coin set structs for current coin set and current min coin set
 * *  Return value: Does not return as minimum coin set vector is recorded in the function
 * *  Description: Recursive helper method that is called recursively based on psuedocode 
 * *  Credit: http://www.geeksforgeeks.org/find-minimum-number-of-coins-that-make-a-change/
 * *  http://romanenco.com/coin-change-problem/
 * ***************************************************************/
void recursiveBrute(int coinSetValue, std::vector<int> coinSet, CS &minimumCoinSet, CS currentCoinSet )
{

	/* Base Case: We can make change using exactly one coin, then that is a minimum */
	if ( coinSetValue == 0 )
	{
		/* If there are less coins in current coin set than current min coin set */
		if ( currentCoinSet.numberCoins < minimumCoinSet.numberCoins )
		{
			/* Then update the new min coin set with amount value and actual coin list */
			minimumCoinSet.numberCoins = currentCoinSet.numberCoins;
			minimumCoinSet.actualCoins = currentCoinSet.actualCoins;
		}
		return;
	}
	/* If there are more coins in current set than minimum set then its not new min so return */
	if ( currentCoinSet.numberCoins > minimumCoinSet.numberCoins )
	{
		return;
	}
	/*  Try every coin that has smaller value than V 
	Find the minimum number of coins needed to make i cents  */
	for ( int j = coinSet.size() - 1; j >= 0; j-- )
	{
		/* If we haven't reached the K yet then we should keep recursively calling on K - i */
		if ( coinSetValue >= coinSet[j] )
		{
			/* With each mini-solution create a new coin set object and update its amount and coins used */
			CS newSet;
			newSet.numberCoins = currentCoinSet.numberCoins + 1;
			newSet.actualCoins = currentCoinSet.actualCoins;
			newSet.actualCoins[j]++;
			/* Find the minimum number of coins needed to make K - i cents  */
			recursiveBrute( coinSetValue - coinSet[j], coinSet, minimumCoinSet, newSet);
		}
	}
}
