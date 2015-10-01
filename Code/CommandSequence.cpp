/*
 * CommandSequence.cpp
 *
 *  Created on: Sep 3, 2015
 *      Author: dikshay
 */

#include <iostream>
#include <fstream>
#include <map>
#include <iterator>
#include "CommandSequence.h"
#include "Commands.h"

using namespace std;


static const string START = "Start";
static const string SELECT = "Select";
static const string INSERTION_SORT = "InsertionSort";
static const string MERGE_SORT = "MergeSort";
static const string PARALLEL_MERGE_SORT = "ParallelMergeSort";
static const string AVERAGE = "Average";
static const string PARALLEL_AVERAGE = "ParallelAverage";
static const string END = "End";
static const string EXIT = "Exit";
static const string delimiter = " ";
Commands commandObject;

void readCommandSequence()
{


			string inputCommand;
			string userName;
			string token;
			while(true)
				{
					getline(cin,inputCommand);//reads the command from standard input and stores it in variable inputCommand
					if (!inputCommand.empty() && inputCommand[inputCommand.size() - 1] == '\r')
						inputCommand.erase(inputCommand.size() - 1);
					size_t pos = 0;
					pos = inputCommand.find(delimiter);//if the command consist of 2 words here we find the posisition of space(delimiter) in order to separate the two words
					token =  inputCommand.substr(0,pos);//the first word will be stored in token (for eg. Start Ravi. Here Start will be stored in token)
					userName = inputCommand.substr(pos+1);//the second word will be stored here(for eg. Start Ravi. here Ravi will be stored here)
					if(token.compare(START)==0)
						{
							commandObject.start(userName);//If it is start command, the start function will be invoked
						}
					else if(token.compare(SELECT)==0)
						{
							if(commandObject.getSorted())
								{
									commandObject.select(userName);//If it is select command and the array is sorted the select function will be invoked
								}
							else
								{
									cout<<"Unable to select from an unsorted array."<<endl;//If it is select command and the array is not yet sorted, then we will display this message
								}
						}
					else if(token.compare(INSERTION_SORT)==0)
						{

							commandObject.InsertionSort();// If command is insertion sort then  the Insertion sort function will be invoked
						}
					else if(token.compare(MERGE_SORT)==0)
					{

							commandObject.doMergeSort();// If command is merge sort then the Merge Sort function will be invoked.
					}
					else if(token.compare(PARALLEL_MERGE_SORT)==0)
					{
						commandObject.doParallelMergeSort();
					}
					else if(token.compare(AVERAGE)==0)
						{
							commandObject.average();//If command is average, then the average functionn will be invoked
						}
					else if(token.compare(PARALLEL_AVERAGE)==0)
					{
						commandObject.parallelAverage();
					}
					else if(token.compare(END)==0)
						{
							commandObject.end(userName);//used to invoke the end function
						}
					else if(token.compare(EXIT)==0)
						{
							commandObject.exit();//used to invoke the exit function
							break;//breaks the loop and exits the program
						}
				}
}


