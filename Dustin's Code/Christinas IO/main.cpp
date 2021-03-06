#include <algorithm>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <limits.h>		//for INT_MAX
#include <fstream>		//for file IO
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <ctime>		//for random number generation
#include <time.h>		//for random number generation
#include <string>
#include <sstream>

// just a large int for initializing purposes
const int largeInt = 999999;

using std::vector;

struct coins
{
    int coinAmount;
    int coinValue;
    int changeLeft;
};


//Function prototypes
std::vector<std::string>* readFile(std::ifstream& input);
void getinput(std::ifstream &inStream, std::vector<std::vector<int>> &returnCoinLists,
                                 std::vector<int> &returnTotalValue);
void formatLine(std::string &rawString);
std::vector<int> convertToNumber(std::string &line);
std::vector<std::vector<int>> getNumbers(std::ifstream &input);
void writeResults(std::ofstream &output, std::vector<struct coins>& results, int total);
void runtimetrial(int (*whichAlg)(std::vector<int>&, int, std::vector<int>&), std::vector<int> &coinSet, int coinSetValue, std::vector<int> &actualCoinsUsed);
vector <struct coins> makeChange(int changeAmount, vector <struct coins> coinsUsedVector);
int coinCounter(vector <struct coins> resultVector);

/**************************************************************
 * *  This main function creates a vector of randomly generated integers
 * *  for use in testing the implementations of Algorithms 1-4. The first part measures
 * *  the running time in ms for each Algorithm for display. The second part tests
 * *  input output by reading input from a specified text file, running each Algorithm
 * *  on this input, and writing the results to another specified text file.
 * ***************************************************************/
int main(int argc, char* argv[]){
	std::string filename;
	std::string outputfilename;
    std::string timingOutputFile;


    int changeAmount;
    vector <struct coins> coinsUsedVector;
    vector <int> coinValues;

    vector <struct coins> resultVector;
    int resultCoins;

	/* The first argument (argc) is the number of elements in the array so we should have two elements the program name and file name 
	Credit: http://www.site.uottawa.ca/~lucia/courses/2131-05/labs/Lab3/CommandLineArguments.html
	*/
    if(argc != 2)
    {
        std::cout << "Please enter an input filename." << std::endl << std::endl;
        exit(1);
    }
	/* which is the second argument (argv). The second argument is always an array of char*, */
    else
    {      
        filename = std::string(argv[1]);
		std::string tempoutputfilename = std::string(argv[1]);
		//http://www.cplusplus.com/reference/string/string/length/
		int strsize = tempoutputfilename.length() - 4;
		/* http://www.cplusplus.com/reference/string/string/operator+/ 
		http://www.cplusplus.com/reference/string/string/substr/ */
		outputfilename = (tempoutputfilename.substr(0, strsize)) + "change.txt";
        timingOutputFile =(tempoutputfilename.substr(0, strsize)) + "timings.txt";
		std::cout << outputfilename << std::endl;
	}
	//cout << filename << endl;
	/* Stream class provided by C++ to read from files
	Credit: http://www.cplusplus.com/doc/tutorial/files/*/
    std::ifstream textfile;
	/* In order to open a file with a stream object we use its member function open */
    textfile.open(filename);
	/* To check if a file stream was successful opening a file, you can do it by calling to member is_open
	Credit: http://www.cplusplus.com/doc/tutorial/files/*/
    if(!textfile.is_open())
    {
        std::cout << "The file could not be opened." << std::endl;
        textfile.close();
        exit(1);
    }
	/* Call function to put first alternating lines as the coin set input and the second alternating lines as total change V */
    std::vector<std::vector<int>> coinsetinput;
    std::vector<int> changevalueV;
    getinput( textfile, coinsetinput, changevalueV );
    textfile.close();
	/* Stream class to write on files
	Credit: http://www.cplusplus.com/doc/tutorial/files/*/
	std::ofstream textfile2;
    std::ofstream timingStream;

    textfile2.open(outputfilename);
    timingStream.open(timingOutputFile);

    if(!textfile2.is_open())
    {
        std::cout << "Cannot open for writing. Check the permissions of the directory." << std::endl;
        textfile2.close();
        exit(1);
    }
    if(!timingStream.is_open())
    {
        std::cout << "Cannot open timingFile for writing. Check the permissions of the directory." << std::endl;
        timingStream.close();
        exit(1);
    }
	/* Display a babel for brute force algorithm time trial */
    std::cout << "Testing Bruteforce...." << std::endl;
    for( unsigned int i = 0; i < coinsetinput.size(); i++ )
    {
        coinValues.clear();
        resultVector.clear();
        coinsUsedVector.clear();

        changeAmount = changevalueV.at(i);
        coinValues = coinsetinput.at(i);

        //initialize
        for (unsigned int i = 0; i < coinValues.size(); i++)
        {
            struct coins test;
            test.coinAmount = 0;
            test.coinValue = coinValues[i];
            test.changeLeft = changeAmount;
            coinsUsedVector.push_back(test);
            // printf("pushed coin value %i\n", coinsUsedVector.back().coinValue);
        }

        std::clock_t start = std::clock();
    
        resultVector = makeChange(changeAmount, coinsUsedVector);
        resultCoins = coinCounter(resultVector);
        double runtime = (std::clock() - start) / (double) CLOCKS_PER_SEC;

        printf("Running time is %f\n", runtime);
        printf("The minimum amount of coins used is: %i\n", resultCoins);

        for (unsigned int i = 0; i < resultVector.size(); i++)
        {
            printf("Coin value: %i Amount: %i | ", resultVector[i].coinValue, resultVector[i].coinAmount);
        }
        printf("\n");

        timingStream << changeAmount << ", " << runtime << std::endl;
        writeResults(textfile2, resultVector, resultCoins);	
    }
    timingStream.close();
    textfile2.close();	
}

/**************************************************************
 * *  Function name: readFile
 * *  Description: Function will format the lines by removing bracket
 * ***************************************************************/
std::vector<std::string>* readFile(std::ifstream& input)
{
  	std::vector<std::string>* stringVector = new std::vector<std::string>();
    std::string line;
	/* Read in a line until a newline character is found using getline
	Credit http://stackoverflow.com/questions/18786575/using-getline-in-c */
    while(std::getline(input, line))
    {
        /* Use push back to insert the line into string vector */
		stringVector->push_back(line);
    }
    return stringVector;
}

/**************************************************************
 * *  Function name: formatLine
 * *  Description: Function will format the lines by removing bracket
 * ***************************************************************/
void formatLine(std::string &rawString)
{
    /* This is a temp string to hold non-bracket part of string*/
	std::string formattedString;
	/* Iterate through the string to look for bracket */
    for( unsigned int i = 0; i < rawString.length(); i++ )
    {
        /* Skip any bracket characters */
		if(rawString.at(i) == '[' || rawString.at(i) == ']' || rawString.at(i) == ',')
            continue;
        /* Only add the non bracket characters to the temp string */
		else
            formattedString += rawString.at(i);
    }
	/* Now the string is formatted */
    rawString = formattedString;
}

/**************************************************************
 * *  Function name: convertToNumber
 * *  Description: Function will read file input and put contents
 * *  into number vector
 * ***************************************************************/
std::vector<int> convertToNumber(std::string &line)
{
    std::vector<int> returnVector;
	/* Convert the string into a C style string or const char
	http://stackoverflow.com/questions/236129/split-a-string-in-c*/ 
	std::string buf; // Have a buffer string
    std::stringstream ss; // Insert the string into a stream
	ss << line;
    std::vector<std::string> tokens; // Create vector to hold our words
	while (ss >> buf){
        tokens.push_back(buf);
	}
	int tempNum = 0;
	//http://code-better.com/c/convert-string-integer-using-stringstream
	for(unsigned int i = 0; i < tokens.size(); ++i)
    {
		ss.clear();
        ss << tokens.at(i);	
		ss >> tempNum;
		if(ss.fail()){
			std::cout << "error" << std::endl;
			exit(2);
		}else{
			/* Use push back function to insert number as integer to vector */
			returnVector.push_back(tempNum);		
		}
    }
    return returnVector;
}


/**************************************************************
 * *  Function name: getinput
 * *  Description: Function will format the lines by removing bracket
 * ***************************************************************/
void getinput(std::ifstream &inStream, std::vector<std::vector<int>> &returnCoinLists,
                             std::vector<int> &returnTotalValue)
{
    std::vector<std::string>* CoinFileLines = readFile(inStream);

    for( unsigned int i = 0; i < CoinFileLines->size(); i++ )
    {
        formatLine(CoinFileLines->at(i));

        //
        if(i % 2 == 0)
            returnCoinLists.push_back( convertToNumber( CoinFileLines->at(i)));
        else
            returnTotalValue.push_back(atoi(CoinFileLines->at(i).c_str()));
    }

    delete CoinFileLines;
}



/**************************************************************
 * *  Function name: writeResults
 * *  Description: Function will write results to MSSResults text file
 * ***************************************************************/
void writeResults(std::ofstream &output, std::vector<struct coins>& results, int total)
{
    /* Use the << operator to write to a file and add back the bracket
	CREDIT http://www.cplusplus.com/forum/beginner/4442/ */
	output << "[";		
	/* For each number, write it to the file followed by comma and space*/
        for( unsigned int i = 0; i < results.size() - 1; i++ )
            output << results.at(i).coinAmount << ", ";
	/* Once you get to last number, add a end bracket and newline */
    output << results.at(results.size() - 1).coinAmount << "]" << std::endl;
    /* Now we want to write the sum of max array from start to end on the file */
    output << total << "\n";
            
}


/**************************************************************
 * *  Function name: runtimetrial
 * *  Description: Function will write results to MSSResults text file
 * ***************************************************************/
void runtimetrial(int (*whichAlg)(std::vector<int>&, int, std::vector<int>&), std::vector<int>& coinSet, int coinSetValue, std::vector<int> &actualCoinsUsed)
{
    std::clock_t start = std::clock();
    int result = whichAlg( coinSet, coinSetValue, actualCoinsUsed );
    double runtime = (std::clock() - start) / (double) CLOCKS_PER_SEC;
    std::cout << "Coin Set Size(n): " << coinSet.size() << " Minimum Coins: " << result << " CPU Seconds: " << runtime << '\n';
}

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

int coinCounter(vector <struct coins> resultVector)
{
    int sumCoins = 0;

    // printf("counting: ");
    for (unsigned int i = 0; i < resultVector.size(); i++)
    {
        // printf("coin: %i count: %i ", resultVector[i].coinValue, resultVector[i].coinAmount );
        sumCoins += resultVector[i].coinAmount;
    }
    // printf("\n");

    return sumCoins;
}
