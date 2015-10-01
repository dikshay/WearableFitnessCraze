/*
 * Commands.h
 *
 *  Created on: Sep 3, 2015
 *      Author: dikshay
 */
#include <iostream>
#ifndef COMMANDS_H_
#define COMMANDS_H_
using namespace std;

class Commands {
	public:

		void start(string x);
		void readFileData();
		bool getSorted();
		void setSorted(bool);
		void select(string);
		void end(string);
		void InsertionSort();
		void doMergeSort();
		void MergeSort(int [],int,int);
		void Merge(int [],int,int,int);
		void doParallelMergeSort();
		void ParallelMergeSort(int [],int,int);
		void average();
		void parallelAverage();
		void exit();
};

#endif /* COMMANDS_H_ */
