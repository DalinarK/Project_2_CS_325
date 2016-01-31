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
