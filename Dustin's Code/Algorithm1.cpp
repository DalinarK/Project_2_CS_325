#include <vector>
#include <cstdio>

using std::vector;

// just a large int for initializing purposes
const int largeInt = 999999;

// just a large int for initializing purposes
const int largeInt = 999999;

struct coins
{
	int coinAmount;
	int coinValue;
	int changeLeft;
};

//counts the amount of coins used in the vector for the sum.
int coinCounter(vector <struct coins> resultVector);

vector <struct coins> makeChange(int changeAmount, vector <struct coins> coinsUsedVector)
{
	vector <struct coins> resultVector;
	int resultCoins;
	vector <struct coins> lowestCoinVector;
	int lowestcoins = largeInt;
	int newChangeAmount= 88;

	vector <struct coins> currentVector;

	//basecase
	for (unsigned int i = 0; i < coinsUsedVector.size(); i++)
	{
		currentVector  = coinsUsedVector;

		if (currentVector[i].coinValue == currentVector[0].changeLeft)
		{
			currentVector[i].coinAmount++;
			currentVector[0].changeLeft -= currentVector[i].coinValue;
			// printf("Base Case Reached Returning with +1 amount to coin value %i. Value: %i Amount: %i Value: %i Amount: %i\n",coinsUsedVector[i].coinValue, coinsUsedVector[0].coinValue, coinsUsedVector[0].coinAmount, coinsUsedVector[1].coinValue, coinsUsedVector[1].coinAmount );
			return currentVector;
		}
	}

	for (unsigned int i = 0; i < coinsUsedVector.size(); i++)
	{
		resultCoins = 0;
		currentVector = coinsUsedVector;

		// printf("Calling function with changeAmount %i - coin %i = %i \n", coinsUsedVector[0].changeLeft, currentVector[i].coinValue, currentVector[0].changeLeft);
		if (coinsUsedVector[0].changeLeft > currentVector[i].coinValue)
		{
			currentVector[0].changeLeft = currentVector[0].changeLeft - currentVector[i].coinValue;
			currentVector[i].coinAmount++;
			resultVector = makeChange(newChangeAmount, currentVector);
		}

		
		resultCoins = coinCounter(resultVector);
		// printf("Comparing resultCoins %i to %i lowest coins\n", resultCoins, lowestcoins);
		if (resultCoins < lowestcoins)
		{
			lowestcoins = resultCoins;
			lowestCoinVector = resultVector;
		}
	}

	resultCoins = coinCounter(lowestCoinVector);
	// printf("The lowest coin vector is %i \n",  lowestcoins);

	// printf("returning\n");
	return lowestCoinVector;
}



int main (int argc, const char * argv[])
{
	int changeAmount = 15;
	vector <struct coins> coinsUsedVector;
	vector <int> coinValues {1, 2, 4, 8};

	vector <struct coins> resultVector;
	int resultCoins;

	for (unsigned int i = 0; i < coinValues.size(); i++)
	{
		struct coins test;
		test.coinAmount = 0;
		test.coinValue = coinValues[i];
		test.changeLeft = changeAmount;
		coinsUsedVector.push_back(test);
		printf("pushed coin value %i\n", coinsUsedVector.back().coinValue);
	}

	// copyVector(resultVector, coinsUsedVector);

	// printf("this works\n");

	resultVector = makeChange(changeAmount, coinsUsedVector);
	resultCoins = coinCounter(resultVector);
	printf("The minimum amount of coins used is: %i\n", resultCoins);

	for (unsigned int i = 0; i < resultVector.size(); i++)
	{
		printf("Coin value: %i Amount: %i \n", resultVector[i].coinValue, resultVector[i].coinAmount);
	}
}

int coinCounter(vector <struct coins> resultVector)
{
	int sumCoins;

	// printf("counting: ");
	for (unsigned int i = 0; i < resultVector.size(); i++)
	{
		// printf("coin: %i count: %i ", resultVector[i].coinValue, resultVector[i].coinAmount );
		sumCoins += resultVector[i].coinAmount;
	}
	// printf("\n");

	return sumCoins;
}
