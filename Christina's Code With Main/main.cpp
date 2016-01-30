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
#include "changegreedy.h"
#include "changeslow.h"

//Function prototypes
std::vector<std::string>* readFile(std::ifstream& input);
void getinput(std::ifstream &inStream, std::vector<std::vector<int>> &returnCoinLists,
                                 std::vector<int> &returnTotalValue);
void formatLine(std::string &rawString);
std::vector<int> convertToNumber(std::string &line);
std::vector<std::vector<int>> getNumbers(std::ifstream &input);
void writeResults(std::ofstream &output, std::vector<int>& results, int total);
void runtimetrial(int (*whichAlg)(std::vector<int>&, int, std::vector<int>&), std::vector<int> &coinSet, int coinSetValue, std::vector<int> &actualCoinsUsed);

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
    textfile2.open(outputfilename);
    if(!textfile2.is_open())
    {
        std::cout << "Cannot open for writing. Check the permissions of the directory." << std::endl;
        textfile2.close();
        exit(1);
    }
	/* Display a babel for brute force algorithm time trial */
    std::cout << "Testing changeslow...." << std::endl;
    for( unsigned int i = 0; i < coinsetinput.size(); i++ )
    {
        /* Run brute force algorithm on input numbers from first to last element */
		std::vector<int> coinCount;
		runtimetrial( changeslow, coinsetinput.at(i), changevalueV.at(i), coinCount );
    }
	/* Display a babel for greedy algorithm time trial */
    std::cout << "Testing changegreedy...." << std::endl;
    for( unsigned int i = 0; i < coinsetinput.size(); i++ )
    {
        /* Run greedy algorithm on input numbers from first to last element */
		std::vector<int> coinCount;
        runtimetrial( changegreedy, coinsetinput.at(i), changevalueV.at(i), coinCount);
    }
    /* Display a babel for dynamic programming algorithm time trial */
    std::cout << "Testing changedp...." << std::endl;
    /*for( unsigned int i = 0; i < coinsetinput.size(); i++ )
    {
         Run greedy algorithm on input numbers from first to last element 
		
    }*/
	/* Call function to output is to be written to text file */
    textfile2 << "Brute Force \n\n";
	 /* Run changeslow algorithm on input numbers */
    for( unsigned int i = 0; i < coinsetinput.size(); i++ )
    {
        std::vector<int> coinCount;
        int minCoins = changeslow( coinsetinput.at(i), changevalueV.at(i), coinCount );
        writeResults( textfile2, coinCount, minCoins );
    }
	/* Call function to output is to be written to text file */
    textfile2 << "Greedy\n\n";
    for( unsigned int i = 0; i < coinsetinput.size(); i++ )
    {
        std::vector<int> coinCount;
        int minCoins = changegreedy(coinsetinput.at(i), changevalueV.at(i), coinCount);
        writeResults( textfile2, coinCount, minCoins );
    }
	/* Call function to output is to be written to text file */
    textfile2 << "Dynamic Programming\n\n";
    //for( unsigned int i = 0; i < coinsetinput.size(); i++ )
   // {
      //  std::vector<int> coinCount;
       // int minCoins = changedp();
        //writeResults( textfile2, coinCount, minCoins );
	//}
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
void writeResults(std::ofstream &output, std::vector<int>& results,int total)
{
    /* Use the << operator to write to a file and add back the bracket
	CREDIT http://www.cplusplus.com/forum/beginner/4442/ */
	output << "[";		
	/* For each number, write it to the file followed by comma and space*/
        for( unsigned int i = 0; i < results.size() - 1; i++ )
            output << results.at(i) << ", ";
	/* Once you get to last number, add a end bracket and newline */
    output << results.at(results.size() - 1) << "]" << std::endl;
    /* Now we want to write the sum of max array from start to end on the file */
    output << total << "\n \n";
            
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

