# WearableFitnessCraze
C++ project that will read user's fitness data from file and perform serial operations like InsertionSort, MergeSort and parallel operations like Parrallel MergeSort using OpenMP.

You can enter the following commands into the program:

<b>Start Name</b>, where Name is a character string</br>
<b>End Name</b> indicates the end of the processing for the fitness data for Name</br>
<b>InsertionSort</b></br>
<b>MergeSort</b></br>
<b>ParallelMergeSort</b>, implemented using OpenMP</br>
<b>Select item</b>, selects an item from a sorted array. If the array has not been sorted (by a previous serial
or a parallel sort), the following error must be reported:
Unable to select from an unsorted array.
Valid items for selection include:
– max, prints the largest value in the fitness data, i.e., data item N.
– min, prints the smallest item in the fitness data, i.e., first data item.
– median, prints the median value of the fitness data.
– k, where 1 ≤ k ≤ N, selects the k
th item in the fitness data and prints it. When k = 1 this is
equivalent to selecting the min. When k = N this is equivalent to selecting the max.</br>
<b>Average</b></br>
<b>ParallelAverage</b></br>
<b>Exit</b> indicates that there are no more commands to execute, i.e., the program terminates</br>

</br>
<h3>Consider the demo command sequence:</h3>
<b>Start Ray</b> // Working on Ray’s fitness data</br>
<b>InsertionSort</b> // Use insertion sort to sort Ray’s fitness data</br>
<b>Select max</b> // Print the maximum number of steps Ray has walked in a day</br>
<b>ParallelAverage</b> // The average number of steps walked using a parallel sum</br>
<b>MergeSort</b> // Ray’s data read in again and sorted using merge sort</br>
<b>Select min</b> // The fewest steps Ray has walked in a day</br>
<b>Select 5</b> // The fifth smallest number of steps Ray walked in a day</br>
<b>Select median</b> // The median number of steps Ray walked in a day</br>
<b>Average</b> // The average number of steps walked in a day (serial)</br>
<b>End Ray</b> // Free any memory dynamically allocated for Ray</br>
<b>Start Amy</b> // Working on Amy’s fitness data</br>
<b>ParallelMergeSort</b> // Sort Amy’s data using a parallel merge sort algorithm</br>
<b>Select max</b> // The maximum number of steps Amy has walked in a day</br>
<b>End Amy</b> // Free any memory dynamically allocated for Amy</br>
<b>Exit</b></br>

<h3>Consider the demo data sequence:</h3>
10</br>
43</br>
54</br>
67</br>
33</br>
63</br>
1</br>
98</br>
567</br>
544</br>
22</br>
