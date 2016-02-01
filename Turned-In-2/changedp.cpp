/******************************************************************************************
** Source file for changedp.
** Inspiration for function from http://romanenco.com/coin-change-problem/
******************************************************************************************/

#include "changedp.h"


void Changedp::dpChange(std::vector<int> &coinSet, int makeChangeVal, struct coinChange &result){

	std::vector<struct coinChange> values;

	//load the values array with coinChange structs:
	//values will store the min num of coins needed to sum to value i
	//initialize values to -1 to signify no coins	
	for(int i = 0; i <= makeChangeVal; ++i){
		struct coinChange value;
		values.push_back(value);
		values.at(i).coins = std::numeric_limits<int>::max();

		//initialize each result vec to show zero coins
		for(unsigned int x = 0; x < coinSet.size(); ++x){
			values.at(i).resultVec.push_back(0);
		}
	}

	//intialize 0 value to 0
	values.at(0).coins = 0;

	//outter loop iterates through the values of the change up to the makeChangeVal
	for(unsigned int change = 0; change < values.size(); ++change){
		//inner loop iterates through the coin set and finds the fewest num of coins to make change 
		//for the change value. 
		for(unsigned int x = 0; x < coinSet.size(); ++x){
			//store fewest num of coins required to make change in values array
			if((int)change >= coinSet.at(x)){
				if((values.at(change - coinSet.at(x) ).coins + 1) <= values.at(change).coins){
					//found a better solution for this problem so save it in values array
					for(unsigned int i = 0; i < coinSet.size(); ++i){						
						values.at(change).resultVec.at(i) = values.at(change - coinSet.at(x)).resultVec.at(i);											
					}
					//now add the coin just found
					++values.at(change).resultVec.at(x);
				}

				values.at(change).coins = std::min(values.at(change).coins, values.at(change - coinSet.at(x)).coins + 1);
			}
		}
	}

	//finished so set the result and return
	//solution is stored in the last element in values coinChange struct
	result.coins = values.at(makeChangeVal).coins;

	for(unsigned int i = 0; i < coinSet.size(); ++i){	
		result.resultVec.push_back(values.at(makeChangeVal).resultVec.at(i));
	}

}
