/******************************************************************************************
** Header file for changegreed.
** Provides a function changegreedy that will return the minimum number of coins from a set
** V to make change for a value A.
******************************************************************************************/
#ifndef _CHANGEGREEDY_H
#define _CHANGEGREEDY_H


#include <iostream>
#include <vector>
#include <algorithm>

//Function prototype
int changegreedy(std::vector<int> &coinSet, int coinSetValue, std::vector<int> &coinCount);

#endif
