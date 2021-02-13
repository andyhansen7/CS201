/* ==========================
 * Circular Dynamic Array
 * CS201-001 Spring 2021
 * Developed by Andrew Hansen
 * arhansen@crimson.ua.edu
 * ===========================
 */

#include "CDA.h"
#include <iostream>
#include <stdlib.h>
//#include <string>

//#define _DEBUG_

template<typename T>
CDA<T>::CDA()
    : _size(0), _capacity(1), _start(0), _reverse(false)
{
    //_array = new T[_capacity];
    _array = new T[_capacity];

    //DebugLog("Array created with default constuctors");
}

template<typename T>
CDA<T>::CDA(int s)
    : _size(s), _capacity(s), _start(0), _reverse(false)
{
    _array = new T[_capacity];

    //DebugLog("Array created with specified size" + std::to_string(s));
}

template<typename T>
CDA<T>::CDA(CDA& c)
    : _size(c.Length()), _capacity(c.Capacity()), _start(0), _reverse(false) 
{
    _array = new T[_capacity];

    for(int i = 0; i < _size; i++)
    {
        _array[i] = c[i];
    }

    //DebugLog("Array created using copy constructor");
}

template<typename T>
CDA<T>::~CDA()
{
    delete[] _array;

    //DebugLog("All memory freed");
}

template<typename T>
CDA<T>& CDA<T>::operator=(CDA& c)
{
    _size = c.Length();
    _capacity = c.Capacity();
    _start = 0;

    _array = new T[_capacity];

    for(int i = 0; i < _size; i++) _array[i] = c[i];

    return *this;

    //DebugLog("Array copied using copy assignment operator");
}

template<typename T>
T& CDA<T>::operator[](int index)
{
    // check for validity of the index
    if(index < 0 || index >= _size || _size < 1)
    {
        std::cout << "[ERROR] Invalid index specified" << std::endl;

        // return a cast value so that there are never errors
        //return _validreference;
        //return nullptr;
        return _array[0];
    }

    // Access element in opposite direction
    if(_reverse) {  

        //DebugLog("Array index " + std::to_string(index) + " accessed in reverse order, returning value of index " + std::to_string((_capacity + _start - index) % _capacity));
        
        return _array[(_start + _size - index - 1) % _capacity];
    }

    // Access array normally
    else {  

        //DebugLog("Array index " + std::to_string(index) + " accessed in normal order, returning value of index " + std::to_string(index));

        return _array[(_capacity + _start + index) % _capacity];
    }
}

template <typename T>
void CDA<T>::AddEnd(T v)
{   
    if(_reverse) InsertFront(v);
    else InsertEnd(v);
}

template <typename T>
void CDA<T>::AddFront(T v)
{
    if(_reverse) InsertEnd(v);
    else InsertFront(v);
}

template <typename T>
void CDA<T>::DelEnd()
{
    if(_reverse) RemoveFront();
    else RemoveEnd();
}

template <typename T>
void CDA<T>::DelFront()
{
    if(_reverse) RemoveEnd();
    else RemoveFront();
}

template <typename T>
int CDA<T>::Length()
{
    return _size;
}

template <typename T>
int CDA<T>::Capacity()
{
    return _capacity;
}

template <typename T>
void CDA<T>::Clear()
{
    //T* oldarr = _array;
    _array = new T[4];

    //std::cout << "HERE" << std::endl;

    //T* newarr = new T[4];

    //std::cout << "1" << std::endl;
    //_array = newarr;
    //std::cout << "2" << std::endl;

    _size = 0;
    _capacity = 4;
    _start = 0;

    //std::cout << "3" << std::endl;

    //delete [] oldarr;

    ////DebugLog("Array cleared");
}

template <typename T>
void CDA<T>::Reverse()
{
    _reverse = !_reverse;

    //DebugLog("Reverse called, reverse is now " + std::to_string(_reverse));
}

template <typename T>
T CDA<T>::Select(int k)
{
    // QuickSelect sorts the array. Apparently we don't need it to sort the array. 
    // Making an array copy to reset it after the search is complete
    T* backup = new T[_capacity];
    for(int i = 0; i < _size; i++) backup[(_start + i) % _capacity] = _array[(_start + i) % _capacity];

    T retval = QuickSelectRecursive(0, _size - 1, k);

    delete[] _array;
    _array = backup;

    return retval;
}

template <typename T>
void CDA<T>::Sort()
{
    // quit if size is too small to sort
    if(_size < 2) return;

    // use mergesort to sort array in ascending order
    MergeSortSubarray( 0, _size - 1);
}

template <typename T>
int CDA<T>::Search(T e)
{
    //T nextlargest = e;

    // Unordered linear search of array for element
    for(int i = 0; i < _size; i++) {

        if((*this)[i] == e) return i;
    }

    return -1;
}

template<typename T>
int CDA<T>::BinSearch(T e)
{
    // variable to store next largest value
    int *nextlargest = new int(-1);
    //*nextlargest = -1;

    // initial call to recursive function
    int retval = BinSearchRecursive(0, _size - 1, e, nextlargest);

    if(retval == -1) {
        if(*nextlargest != -1) return ~(*nextlargest);
        else return ~_size;
    } 
    else return retval;
}

template<typename T>
void CDA<T>::Print()
{
    std::cout << "Start -> ";
    for(int i = 0; i < _size; i++) std::cout << (*this)[i] << " -> ";
    std::cout << "End" << std::endl;
}

template <typename T>
void CDA<T>::Extend()
{
    if(_size >= _capacity)
    {
        T* newarray = new T[_capacity * 2];
        int newcap = 2 * _capacity;
        int newstart = (_start + _capacity) % newcap;

        //std::cout << newcap << "   " << newstart << std::endl; 

        // set values to new array
        /*
        for(int i = 0; i < _size; i++) newarray[i] = (*this)[i];

        delete[] _array;
        _array = newarray;

        // Reset values
        _start = 0;
        _capacity *= 2;
        //_reverse = !_reverse;
        */

        for(int i = 0; i < _size; i++) 
        {
            newarray[(newstart + i) % newcap] = _array[(_start + i) % _capacity];
            //std::cout << newarray[(newstart + i) % newcap] << std::endl;
        }

        //delete[] _array;
        _array = newarray;

        _start = newstart;
        _capacity = newcap;


        //DebugLog("Capacity expanded to " + std::to_string(_capacity));
    }
}

template <typename T>
void CDA<T>::Contract()
{
    if(_size <= (_capacity / 4) && ((_capacity / 2) > 4)) 
    {
        //std::cout << "CONTRACT" << std::endl;
        T* newarray = new T[_capacity / 2];
        int newcap = _capacity / 2;
        int newstart = (_start + _capacity) % newcap;

        /*
        for(int i = 0; i < _size; i++) newarray[i] = (*this)[i];

        delete[] _array;
        _array = newarray;

        // Reset values
        _start = 0;
        _capacity = _capacity / 2;
        _reverse = false;
        */

        for(int i = 0; i < _size; i++) 
        {
            newarray[(newstart + i) % newcap] = _array[(_start + i) % _capacity];
            //std::cout << newarray[(newstart + i) % newcap] << std::endl;
        }

        //delete[] _array;
        _array = newarray;

        _start = newstart;
        _capacity = newcap;

        //DebugLog("Capacity contracted to " + std::to_string(_capacity));
    }
}

template <typename T>
void CDA<T>::InsertFront(T value)
{
    Extend();

    _start = (_capacity + _start - 1) % _capacity;
    _array[_start] = value;

    //DebugLog(std::to_string(_start));

    _size++;

    //DebugLog("New element with value " + std::to_string(value) + " inserted at true front of array");
}

template <typename T>
void CDA<T>::InsertEnd(T value)
{
    Extend();

    _array[(_start + _size) % _capacity] = value;

    _size++;

    //DebugLog("New element with value " + std::to_string(value) + " inserted at true end of array");
}

template <typename T>
void CDA<T>::RemoveFront()
{
    //_array[_start] = _validreference;
    _start++;

    _size--;

    Contract();

    //DebugLog("True start of array removed");
}

template <typename T>
void CDA<T>::RemoveEnd()
{
    //_array[(_start + _size - 1) % _capacity] = _validreference;

    _size--;

    Contract();

    //DebugLog("True end of array removed");
}

template <typename T>
void CDA<T>::MergeSortSubarray(int lower, int upper)
{
    if(lower < upper)
    {
        int median = ( (upper - lower) / 2) + lower;

        //DebugLog("Mergesort called, with lower index " + std::to_string(lower) + " and upper index " + std::to_string(upper));

        MergeSortSubarray(lower, median); 
        MergeSortSubarray(median + 1, upper); 
  
        Merge(lower, median, upper);
    }
}

template <typename T>
void CDA<T>::Merge(int lower, int median, int upper)
{
    int n_lower = 1 + median - lower;
    int n_upper = upper - median;

    // temp arrays
    T* lowerArray = new T[n_lower];
    T* upperArray = new T[n_upper];

    // indices for merging
    int lowerIndex = 0;
    int upperIndex = 0;
    int mergedIndex = lower;

    // copy data to temp arrays
    for(int i = 0; i < n_lower; i++) lowerArray[i] = (*this)[i + lower];
    for(int j = 0; j < n_upper; j++) upperArray[j] = (*this)[j + median + 1];

    // merge temp arrays back into initial array
    while(lowerIndex < n_lower && upperIndex < n_upper)
    {
        if(lowerArray[lowerIndex] <= upperArray[upperIndex])
        {
            (*this)[mergedIndex] = lowerArray[lowerIndex];
            lowerIndex++;
        }
        else
        {
            (*this)[mergedIndex] = upperArray[upperIndex];
            upperIndex++;
        }
        mergedIndex++;
    }

    // copy leftover elements from each subarray
    while(lowerIndex < n_lower)
    {
        (*this)[mergedIndex] = lowerArray[lowerIndex];
        lowerIndex++;
        mergedIndex++;
    }

    while(upperIndex < n_upper)
    {
        (*this)[mergedIndex] = upperArray[upperIndex];
        upperIndex++;
        mergedIndex++;
    }

    delete[] lowerArray;
    delete[] upperArray;

    //DebugLog("Merged array with lower index " + std::to_string(lower) + ", upper index " + std::to_string(upper) + " and median of " + std::to_string(median));
}

template<typename T>
int CDA<T>::BinSearchRecursive(int lower, int upper, T e, int* next)
{
    // check boundary validity
    if(lower <= upper)
    {
        int median = (upper - lower) / 2 + lower;

        if((*this)[median] == e) return median;

        // index is in lower half of array
        if((*this)[median] > e) {
            *next = median;
            return BinSearchRecursive(lower, median - 1, e, next);
        }
        // index is in upper half of array
        return BinSearchRecursive(median + 1, upper, e, next);
    }
    // unreachable
    return -1;
}

template <typename T>
T CDA<T>::QuickSelectRecursive(int lower, int upper, int position)
{
   if(position > 0 && position <= _size)
   {
        // find a random pivot in range
        int random;
        if(lower < upper) random = (rand() % (upper - lower)) + lower;
        else random = lower;

        // swap random pivot with highest value in array
        T temp = (*this)[random];
        (*this)[random] = (*this)[upper];
        (*this)[upper] = temp;

       int index = Partition(lower, upper);

       // if psoition is correct, return
       if(index - lower == position - 1) return (*this)[index];

       // if position is greater, run it again
       if(index - lower > position- 1) return QuickSelectRecursive(lower, index - 1, position);

       // if position is less, run it again
       else return QuickSelectRecursive(index + 1, upper, position - index + lower - 1);
   }
   else { return 0b00; }//_validreference
}

template <typename T>
int CDA<T>::Partition(int lower, int upper)
{
    T val = (*this)[upper];
    int i = lower;
    T temp;

    for(int j = lower; j <= upper - 1; j++)
    {
        if((*this)[j] <= val)
        {
            // swap array[i] and array[j]
            temp = (*this)[i];
            (*this)[i] = (*this)[j];
            (*this)[j] = temp;
            i++;
        }
    }

    temp = (*this)[upper];
    (*this)[upper] = (*this)[i];
    (*this)[i] = temp;

    return i;
}

template <typename T>
void CDA<T>::DebugLog(std::string s)
{
    #ifdef _DEBUG_
    std::cout << "> " << s << std::endl;
    #endif
}