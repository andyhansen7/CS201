/* ==========================
 * Circular Dynamic Array
 * CS201-001 Fall 2020
 * Developed by Andrew Hansen
 * arhansen@crimson.ua.edu
 * ===========================
 */

#ifndef __CDA_H__
#define __CDA_H__

#include <iostream>
#include <string>

template<typename T>
class CDA
{
   public:
      /* Default constructor for array, with size 1 and capacity 0*/
      CDA();

      /* Constructor for array with capacity and size s */
      CDA(int s);

      /* Traditional copy constructor, per specifications */
      CDA(CDA& c);

      /* Destructor for the class*/
      ~CDA();

      /* Traditional copy assignment operator */
      CDA& operator=(CDA& c);

      /* Traditional [ ] operator. Will print a message if i is out of bounds,
         * otherwise will return a reference to value*/
      T& operator[](int i);


      /*Increases the size of the array by 1 and stores v at the end of the array.*/
      void AddEnd(T v);

      /*Increases the size of the array by 1 and stores v at the front of the array.*/
      void AddFront(T v);

      /*Reduces the size of the array by 1 at the end of the array*/
      void DelEnd();

      /*Reduces the size of the array by 1 at the front of the array*/
      void DelFront();

      /*Returns the size of the array*/
      int Length();

      /*Returns capacity of array minus size of array*/
      int EmptySlots();

      /*Frees the array and and resets to capacity of 1 and size 0*/
      void Clear();

      /*Returns the status of the ordered flag. 
         * 1 is increasing order
         * -1 is decreasing order
         * 0 is unordered
         */
      int Ordered();

      /*Check to see if array is ordered, and set ordered flag appropriately*/
      int SetOrdered();

      /* Returns the k-th smallest element in array*/
      T Select(int k);

      /* Perform insertion sort on array, and set ordered flag*/
      void InsertionSort();

      /*Perform quick sort on array, and set ordered flag*/
      void MergeSort();

      /*Perform counting sort on arrray, and set ordered flag*/
      void CountingSort(int m);

      /*Perform binary search if array is ordered, otherwise perform linear search*/
      int Search(T e);

      /* Print the list for debugging purposes*/
      void Print();

   private:

      T* _array;

      int _size;
      int _capacity;
      int _ordered;
      int _start;

      T _validreference = static_cast<T>(0);

      /* Recursive method for Select() */
      T QuickSelectSubarray(int lower, int upper, int pivot);

      /* Method for partitioning array given by QuickSelect function */
      int PartitionArray(int lower, int upper);

      /* Recursive method for MergeSort() */
      void MergeSortSubarray(int lower, int upper);

      /* Method to merge sorted arrays */
      void Merge(int lower, int median, int upper);

      /* Recursive binary search method */
      int BinarySearch(int lower, int upper, T e);

      /* Private method of debugging in terminal */
      void DebugLog(std::string s);

      /* Check if array needs to be expanded */
      void Extend();

      /* Check if array needs to be shrunk */
      void Contract();

      /* Reorder array with start at 0 */
      void ResetStart();

 };

#endif