/*
 * Commands.cpp
 *
 *  Created on: Sep 3, 2015
 *      Author: dikshay
 */
#include<chrono>
#include "Commands.h"
#include <fstream>
#include<iostream>
#include<sstream>
#include <string>
#include <math.h>
#include <time.h>
#include <omp.h>
#include <iomanip>
#define GETMICROS() chrono::system_clock::now().time_since_epoch() / chrono::microseconds(1)

using namespace std;

bool isSorted = false;//"isSorted" variable is used to determine whether the user fitness data is sorted or not
int *userFitnessData;/**This is the array in which the user fitness data will be stored
 	 	 	 	 	 	 The array will be initialized dynamically*/

int dataSize;//here we store the size of the array('userFitnessData') or the count of user fitness data
ifstream dataFile;//dataFile is used to read the file that will be specified by the start command
long double numberOfComparisonForMerge=0;
long double numberOfSwapForMerge=0;
string gFileName;
/*
 * This function reads fitness data from file specified and iniializes user fitness data array
 */
void Commands :: readFileData()
{
	string fileName = gFileName + ".txt";
	dataFile.open(fileName.c_str());//opens the file containing the user fitness data
	string dataRowsCount;//data read from the file is stored in this variable
	int counter =-1;//counter used to traverse the array
	int arraysize;
	int data;
	if(dataFile.is_open())//will only read the file if the file is open
		{
			while(!dataFile.eof())//the file will be continuously read until the end of file is reached
				{
					getline(dataFile,dataRowsCount);//reads the fitness data from the file and stores it in variable,"dataRowsCount"
						if(!dataFile.eof())//will only read until end of file is reached
							{
								if(counter ==-1)//first line of the file is being read.The first line is the size of the fitness data
									{

										istringstream (dataRowsCount) >> arraysize;//store the first line in variable arraysize
										userFitnessData = new int[arraysize];//dyanmically initialize the array userFitnessData
										dataSize = arraysize;
										counter++;
									}
								else
									{
										istringstream(dataRowsCount) >> data;//read all the data from file to variable data
										userFitnessData[counter] = data;//store the content of file in array
										counter++;//incrementing the counter
									}

							}
				}
		}
	dataFile.close();
}
/*
 * Function for the start command
 * Takes the filename as parameter.(For eg. Start Ravi will read the file Ravi.txt)
 * the first line is the total length of the data and we will dynamically initialize the array using this size
 * The rest of the data will then be stored in the array
 */
void Commands :: start(string pReadFromFile)
	{
		gFileName = pReadFromFile;
		string startOutput = "Processing fitness data of ";
		startOutput =startOutput + pReadFromFile;
		readFileData();

		cout<<startOutput<<endl;//display the necessary output of the start command
	}
/*
 * funtion for the select command
 * the user can select max,min,median or select a number by specifiying index
 * However the select command will only be invoked if the array is sorted
 * which will be specified using the isSorted variable
 */
void Commands :: select(string pSelectNumber)
	{
		//const clock_t begin_time = clock();//clocks the time before the selection operation begins
		double begin_time,end_time;
		begin_time = GETMICROS();
		float item;
		if(pSelectNumber == "max")
			{
				item = userFitnessData[dataSize-1];//returns the last number in the array that is the max number
			}
		else if(pSelectNumber == "min")
			{
				item = userFitnessData[0];//returns the first number in array, that is the min number
			}
		else if(pSelectNumber == "median")
			{
				if((dataSize % 2) == 0)
					{
						item = (userFitnessData[dataSize/2] + userFitnessData[(dataSize+1)/2])/2;//returns the medain if arraysize is even
					}
				else
					{
						item = userFitnessData[dataSize/2];//returns the median if arraysize is odd
					}
			}
		else
			{
				int lSelectNumber;
				istringstream(pSelectNumber) >> lSelectNumber;//the index specified the user is stored in lSelectNumber
				if(lSelectNumber >= 1 && lSelectNumber <= dataSize)//checks if the index is greater than 0 and does not exceed the last index
					{
						item = userFitnessData[lSelectNumber-1];//returns the item in array using the index specified by the user
					}
				else
					{
						cout<<"Invalid selection."<<endl;//if the index specified by the user goes out of range than it is invalid selection
						return;
					}

			}
		end_time = GETMICROS();
		cout<<"Selecting item: "<<item<<endl;
		cout<<"Time to run the selection (ms): "<<(end_time - begin_time)/1000<<endl;/* displays the time it took to perform the select operation
		here the begin_time recorded at the begin of select operation is subtracted from the current time
		We get the output in nanoseconds. We multiply it with 1000000 to get the time in milliseconds*/
	}
/*
 * This function is used to calculate the average and will be executed on the Average command
 */
void Commands :: average()
	{
		double startTime,endTime;
		double sum = 0.000000;
		double average=0.000000;
		startTime = GETMICROS();
		for(int i =0; i < dataSize; i++)
			{
				sum = sum + userFitnessData[i];//calculates the sum of all the numbers
			}
		endTime = GETMICROS();
		cout<<"Average number of steps: "<<setprecision(6)<<sum/dataSize<<endl;
		cout<<"Time to run the average (ms): "<<(endTime - startTime)/1000<<endl;/*
		calculates the time required to run the operation by subtracting the time recorded from the current time
		Here we get the time in nanoseconds. To get the time in milliseconds we multiply it with 1000000*/
	}
void Commands :: parallelAverage()
{
	int i;
	double startTime,endTime;
	long double sum = 0;
	long double average = 0;
	startTime = omp_get_wtime();
	//startTime = GETMICROS();
#pragma omp parallel for private(i) reduction(+:sum) num_threads(10)
	for(i = 0;i < dataSize; i++)
	{
		sum = sum + userFitnessData[i];
	}
	average = sum/dataSize;
	endTime = omp_get_wtime();
	//endTime = GETMICROS();
	cout<<"Average number of steps (parallel sum): "<<average<<endl;
	//cout<<"Time to run the average (parallel sum) (ms): "<<(endTime-startTime)/1000<<endl;
	cout<<"Time to run the average (parallel sum) (ms): "<<1000*(endTime-startTime)<<endl;
}
/*
 * Frees up all the memory which were allocated during start
 */
void Commands :: end(string pReadFromFile)
	{
		gFileName = "";
		dataSize = 0;//resets the size of the array of userfitness data
		isSorted = false;//resets the isSorted flag
		numberOfComparisonForMerge = 0;
		numberOfSwapForMerge = 0;
		delete[] userFitnessData;//destroys the array of user fitness data
		//dataFile.close();//closes the file which was opened to read the userfitness data
		cout<<"End of processing fitness data for: "<<pReadFromFile<<endl;
	}
/*
 * Performs the insertion sort
 */
void Commands :: InsertionSort()
	{
		readFileData();
		//const clock_t begin_time = clock();
		double begintime,endTime;
		begintime = GETMICROS();
		int key,i;
		long double numberOfComparison=0;//gives the number of comparisons of the array data
		long double numberOfSwaps=0;//gives the number of swaps taken place of the array data
		for(int j = 1;j<dataSize;j++)
			{
				key = userFitnessData[j];
				i = j-1;

				while(i >= 0 && userFitnessData[i] > key)
					{	numberOfComparison++;//the while loop is entered to swap a number after performing comparison
						numberOfSwaps++;
						userFitnessData[i+1] = userFitnessData[i];
						i = i-1;

					}
				//if(i>-1)
				//{
					numberOfComparison++;
					/*
					 * If the while loop is not entered still atleast one comparsion is done
					 * if the while loop is entered it will exit due to either of the two following conditions"
					 * 		1)the fitness data is less than the key. In this case still one comparison will have to be done in order
					 * 		to reach this conclusion. Hence the number of comparsion will be incremented
					 * 		2)i becomes less than 0. In this case the element will not be compared. hence we do not have to
					 * 		increment numberOfComparison
					 */
				//}
				userFitnessData[i+1] = key;
			}
		endTime = GETMICROS();
		cout<<"Number of comparisons made by insertion sort: "<<numberOfComparison<<endl;
		cout<<"Number of swaps made by insertion sort: "<<numberOfSwaps<<endl;
		cout<<"Time to run insertion sort (ms): "<<(endTime - begintime)/1000<<endl;

		setSorted(true);

	}
/*
 * function to perfrom parallel mergesort.
 */
void Commands :: doParallelMergeSort()
{
	readFileData();
	numberOfComparisonForMerge = 0;
	numberOfSwapForMerge = 0;
	double startTime,endTime;
	//startTime = GETMICROS();
	startTime = omp_get_wtime();
	ParallelMergeSort(userFitnessData,0,dataSize-1);
	cout<<"Number of comparisons made by parallel merge sort: "<<numberOfComparisonForMerge<<endl;
	cout<<"Number of swaps made by parallel merge sort: "<<numberOfSwapForMerge<<endl;
	//endTime = GETMICROS();
	endTime = omp_get_wtime();
	//cout<<"Time to run parallel merge sort (ms): "<<(endTime - startTime)/1000<<endl;
	cout<<"Time to run parallel merge sort (ms): "<<1000*(endTime - startTime)<<endl;
	setSorted(true);


}
/*
 * In order to reduce the overhead from creation of multiple tasks, only 1 recursive call of 2 is parallel.
 * So rather than the parent thread being idle and creating 2 threads to handle 2 sub partitions,
 * we reuse the parent thread to solve 1 subpartition and other subpartition is solved
 * using new task.
 */
void Commands :: ParallelMergeSort(int userFitnessDataArrayForMergeSort[],int startPointer, int endPointer)
{
	if( startPointer < endPointer)
	{
		int mid = (int)floor((startPointer + endPointer)/2);
#pragma omp parallel
#pragma omp single nowait
		{
		#pragma omp task
		ParallelMergeSort(userFitnessDataArrayForMergeSort,startPointer,mid);


		//#pragma omp task
		MergeSort(userFitnessDataArrayForMergeSort,mid+1,endPointer);

		#pragma omp taskwait
		Merge(userFitnessDataArrayForMergeSort,startPointer,mid,endPointer);
		}
		}
}
void Commands :: doMergeSort()
{
	readFileData();
	numberOfComparisonForMerge = 0;
	numberOfSwapForMerge = 0;
	//const clock_t beginTime = clock();
	double startTime,endTime;
	startTime = GETMICROS();
	MergeSort(userFitnessData,0,dataSize-1);
	cout<<"Number of comparisons made by merge sort: "<<numberOfComparisonForMerge<<endl;
	cout<<"Number of swaps made by merge sort: "<<numberOfSwapForMerge<<endl;
	endTime = GETMICROS();
	cout<<"Time to run merge sort (ms): "<<(endTime - startTime)/1000<<endl;
	setSorted(true);


}
void Commands :: MergeSort(int userFitnessDataArrayForMergeSort[],int startPointer, int endPointer)
{
	if( startPointer < endPointer)
	{
		int mid = (int)floor((startPointer + endPointer)/2);
		MergeSort(userFitnessDataArrayForMergeSort,startPointer,mid);
		MergeSort(userFitnessDataArrayForMergeSort,mid+1,endPointer);
		Merge(userFitnessDataArrayForMergeSort,startPointer,mid,endPointer);
	}
}
void Commands :: Merge(int userFitnessDataArrayForMerge[],int startPointer, int mid, int endPointer)
{

	int tempUserFitnessDataArrayForMerge[endPointer + 1];
	int tempPointer = startPointer;
	//copy array to a temporary array
	while(tempPointer <= endPointer)
	{
		tempUserFitnessDataArrayForMerge[tempPointer] = userFitnessDataArrayForMerge[tempPointer];
		tempPointer++;
	}

	int startPointerForFirstSubArray = startPointer;
	int startPointerForSecondSubArray = mid + 1;
	int startPointerForFinalArray = startPointer;
	//compare the 2 partitions of array
	while((startPointerForFirstSubArray <= mid) && (startPointerForSecondSubArray <= endPointer))
	{
		numberOfComparisonForMerge++;
		numberOfSwapForMerge++;
		if(tempUserFitnessDataArrayForMerge[startPointerForFirstSubArray] <= tempUserFitnessDataArrayForMerge[startPointerForSecondSubArray])
		{
			userFitnessDataArrayForMerge[startPointerForFinalArray] = tempUserFitnessDataArrayForMerge[startPointerForFirstSubArray];
			startPointerForFirstSubArray++;
		}
		else
		{
			userFitnessDataArrayForMerge[startPointerForFinalArray] = tempUserFitnessDataArrayForMerge[startPointerForSecondSubArray];
			startPointerForSecondSubArray++;
		}
		startPointerForFinalArray++;
	}
		/*
		 * if some elements are left in any 1 array it will be added to final array. since this subarray will
		 * already be sorted, it need not be sorted again.
		 */
		while(startPointerForFirstSubArray <= mid)
		{
			userFitnessDataArrayForMerge[startPointerForFinalArray] = tempUserFitnessDataArrayForMerge[startPointerForFirstSubArray];
			startPointerForFirstSubArray++;
			startPointerForFinalArray++;
			numberOfSwapForMerge++;
		}


		while(startPointerForSecondSubArray <= endPointer)
		{
			userFitnessDataArrayForMerge[startPointerForFinalArray] = tempUserFitnessDataArrayForMerge[startPointerForSecondSubArray];
			startPointerForSecondSubArray++;
			startPointerForFinalArray++;
			numberOfSwapForMerge++;
		}

}
void Commands :: exit()
	{
		cout<<"Program terminating."<<endl;
	}
bool Commands :: getSorted()
	{
		return isSorted;
	}

void Commands :: setSorted(bool pIsSorted)
	{
		isSorted = pIsSorted;
	}

