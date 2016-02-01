/******************************************************************************************
** Header file for changedp.
** Provides a function changedp that will return the minimum number of coins from a set
** coinSet to make change for a value makeChangeVal.
******************************************************************************************/

#ifndef _CHANGEDP_H
#define _CHANGEDP_H

#include <vector>
#include <math.h>
#include <limits>

struct coinChange{    		
	int coins;
	std::vector<int> resultVec;
	coinChange(){coins = 0;}
};

class Changedp{

public:

/***********************************************************************************************
 * Description: dpChange uses dynamic programming approach to find the minimum number of coins
 * that sum to the value of makeChangeVal from the set of coins coinSet.
 * Precondition:coinSet contains a set of integers, makeChangeVal is a number > 0
 * Postcondition: The number of coins and the solution set is stored in the coinChange struct
 *                result.
 * *********************************************************************************************/
	static void dpChange(std::vector<int> &coinSet, int makeChangeVal, struct coinChange &result);

};

#endif
