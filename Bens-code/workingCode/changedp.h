/******************************************************************************************
** Header file for changedp.
** Provides a function changedp that will return the minimum number of coins from a set
** V to make change for a value A.
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
	
	static void dpChange(std::vector<int> &coinSet, int makeChangeVal, struct coinChange &result);

};

#endif
