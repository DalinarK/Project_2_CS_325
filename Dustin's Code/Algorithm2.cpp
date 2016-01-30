#include <vector>
#include <cstdio>
#include <algorithm>

using std::vector;
using std::min;

struct coins
{
	int changeAmount;
	int coinValue;
	//contains the array with coin counts up to and including coinValue;
	vector <int> coinCount;
};

int countCoins ( vector <int> coinCount)
{
	int totalSum;

	for (unsigned int i; i < coinCount.size(); i++)
	{
		totalSum += coinCount[i];
	}

	// printf("Cumulative coins used is %i \n", totalSum );

	return totalSum;
}

int main(int argc, char const *argv[])
{
	int changeAmount = 15;
	vector <int> coinValues {1, 2, 4, 8};

	

	vector < vector <struct coins> > twoDCoinVector;

	//initialize columns
	for (int i = 0; i < changeAmount + 1; i++)
	{
		vector <struct coins> rowCoinVector;
		//initialize a row
		for (unsigned int j = 0; j < coinValues.size(); j++)
		{
			struct coins coinStruct;
			coinStruct.coinValue = coinValues[j];
			coinStruct.changeAmount = i;
			for (unsigned int k = 0; k < coinValues.size(); k++)
			{
				coinStruct.coinCount.push_back(0);
			}
			rowCoinVector.push_back(coinStruct);
		}
		twoDCoinVector.push_back(rowCoinVector);
	}

	// printf("amount of last element of last row is: %i value: %i row size is %i\n", twoDCoinVector.back().back().coinAmount, twoDCoinVector.back()[0].coinValue, twoDCoinVector.back().size() );

	//cycles through the columns aka the change desired
	for (unsigned int i = 1; i < twoDCoinVector.size(); i++)
	{
		// printf("\nChange desired: %i \n\n", i);
		//cycles through the rows aka the values of coins
		for(unsigned int j = 0; j < twoDCoinVector[i].size(); j++)
		{

			//Special case used in case the coin value being evaluated is larger than the change left. 
			// printf("Value being evaluated is: %i \n", twoDCoinVector[i][j].coinValue);
			if (twoDCoinVector[i][j].coinValue > i)
			{
				int tempValAbove = 900;
				int tempValLeft = 900;
				//if the coin is larger than the change desired, copy the coin counts from the previous 
				//change amount with the available coins then add 1 1-value coin to the count;
				
				if (twoDCoinVector[i][j].coinValue < i){
				tempValAbove = countCoins(twoDCoinVector[i-1][j].coinCount); }

				if (j-1 > 0) {
				tempValLeft = countCoins(twoDCoinVector[i][j-1].coinCount); }

				// printf("Sum of left is: %i Sum of above is: %i\n", tempValLeft, tempValAbove );
				if (tempValLeft < tempValAbove)
				{
					twoDCoinVector[i][j].coinCount = twoDCoinVector[i][j-1].coinCount;
				}
				else
				{
					twoDCoinVector[i][j].coinCount = twoDCoinVector[i-1][j].coinCount;
					twoDCoinVector[i][j].coinCount[0] += 1;
				}

			}
			else
			{
				//finds the column where the appropriate change can be found
				int newChangeAmount = i - twoDCoinVector[i][j].coinValue;
				// printf("New change amount is: %i \n", newChangeAmount);
				// printf("value supposed to be  %i \n", twoDCoinVector[newChangeAmount][j].coinCount[j] );
				twoDCoinVector[i][j].coinCount = twoDCoinVector[newChangeAmount][j].coinCount;

				//count the coin that was used to subtract from i in the previous step
				twoDCoinVector[i][j].coinCount[j] += 1;


			}

				// printf("Total coins: ");
				// for (unsigned int counter = 0; counter < twoDCoinVector[i].size(); counter++)
				// {
				// 	printf("Value: %i Count: %i | ", twoDCoinVector[i][counter].coinValue, twoDCoinVector[i][j].coinCount[counter] );
				// }
				// printf("\n");

		}
	}

	printf("Total coins: ");
	for (unsigned int counter = 0; counter < twoDCoinVector.back().size(); counter++)
	{
		printf("Value: %i Count: %i | ", twoDCoinVector.back()[counter].coinValue, twoDCoinVector.back().back().coinCount[counter] );
	}
	printf("\n");



	return 0;
}