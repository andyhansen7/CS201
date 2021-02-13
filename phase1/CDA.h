/* ==========================
 * Circular Dynamic Array
 * CS201-001 Spring 2021
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
        /* Default constructor for array, with size 1 and capacity 0 */
        CDA();

        /* Constructor for array with capacity and size s */
        CDA(int s);

        /* Traditional copy constructor, per specifications */
        CDA(CDA& c);

        /* Destructor for the class */
        ~CDA();

        /* Traditional copy assignment operator */
        CDA& operator=(CDA& c);

        /* Traditional [ ] operator. Will print a message if i is out of bounds,
        * otherwise will return a reference to value */
        T& operator[](int index);

        /* Increases the size of the array by 1 and stores v at the end of the array. */
        void AddEnd(T v);

        /* Increases the size of the array by 1 and stores v at the front of the array. */
        void AddFront(T v);

        /* Reduces the size of the array by 1 at the end of the array */
        void DelEnd();

        /* Reduces the size of the array by 1 at the front of the array */
        void DelFront();

        /* Returns the size of the array */
        int Length();

        /* Returns capacity of array */
        int Capacity();

        /* Frees the array and and resets to capacity of 4 and size 0 */
        void Clear();

        /* Inverts the logical direction of the array */
        void Reverse();

        /* Returns the k-th smallest element in array */
        T Select(int k);

        /* Performs an O(n lg n) sort on array */
        void Sort();

        /* Perform linear search on array for e */
        int Search(T e);

        /* Perform binary search on array for e */
        int BinSearch(T e);

        /* Print the list for debugging purposes */
        void Print();

    private:

        T* _array;

        int _size;
        int _capacity;
        int _start;
        bool _reverse;

        //T _validreference = dynamic_cast<T>(0);

        /* Extend array if needed */
        void Extend();

        /* Contract array if needed */
        void Contract();

        // Array insert / remove helpers
        void InsertFront(T value);
        void InsertEnd(T value);
        void RemoveFront();
        void RemoveEnd();

        // Sort helper functions
        void MergeSortSubarray(int lower, int upper);

        void Merge(int lower, int median, int upper);

        // Binary search recursive function
        int BinSearchRecursive(int lower, int upper, T e, int* next);

        // Quickselect helper functions
        T QuickSelectRecursive(int lower, int upper, int position);

        int Partition(int lower, int upper);

        /* Private method of debugging in terminal */
        void DebugLog(std::string s);
 };

#endif