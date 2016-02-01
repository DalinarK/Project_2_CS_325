#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "changegreedy.h"

//Function prototype
int changegreedy(std::vector<int> &coinSet, int coinSetValue, std::vector<int> &coinCount);

/**************************************************************
 * *  Function name: change greedy 
 * *  Parameters: Vector of coin set, int representing V, Vector of coin counts
 * *  Return value: Returns sum of coin count values representing minimum coins to make V change 
 * *  Description: Another approach to coin change problem is the greedy approach.  This implementation is called changegreedy.  
 * *  This is also “naive” since it may not be optimal. 
 * *  Credits: http://everythingcomputerscience.com/algorithms/Greedy_Algorithm.html
 * *  http://stackoverflow.com/questions/13557979/why-does-the-greedy-coin-change-algorithm-not-work-for-some-coin-sets
 * *  https://www.quora.com/What-is-an-intuitive-explanation-of-greedy-algorithms
 * *  https://www.youtube.com/watch?v=AUIgt5y5Eyo
 * ***************************************************************/
int changegreedy(std::vector<int> &coinSet, int coinSetValue, std::vector<int> &coinCount)
{
	int sum = 0;
	/* Create and initialize coin set object representing minimum coin count for each coin set element */
	for( unsigned int i = 0; i < coinSet.size(); i++ )
		coinCount.push_back(0);
	/* while change value is greater than 0 we can keep going */
	while ( coinSetValue > 0 )
	{
		/* for each next greatest element (starting from end since this data input is ascending)vector[i] initalize coin count for that element vector[i]  */
		for (long i = coinSet.size() - 1; i >= 0; i--)
		{
			int tempcoincount = 0;
			/* For each element vector[i], while current change value greater than or equal to vector[i]*/
			while ( coinSetValue >= coinSet[i] )
			{
				/* Increment coin count for vector[i] and subtract vector[i] from current change value */
				tempcoincount++;
				coinSetValue -= coinSet[i];
			}
			/* Update i element of coin set object with coin count vector[i] */			
			coinCount.at(i) = tempcoincount;
		}
	}
	/* Loop through coin set object to sum up values of coin counts for vector elements */
	for ( unsigned int j = 0; j < coinCount.size(); j++ )
		sum += coinCount[j];
	/* sum of coin count values is minimum coins to make V change */
	return sum;
}