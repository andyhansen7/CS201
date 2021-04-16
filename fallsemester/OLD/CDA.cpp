/* ==========================
 * Circular Dynamic Array
 * CS201-001 Fall 2020
 * Developed by Andrew Hansen
 * arhansen@crimson.ua.edu
 * ===========================
 */

#include "CDA.h"
#include <iostream>
#include <string>

//#define _DEBUG_

template<typename T>
CDA<T>::CDA()
    : _size(0), _capacity(1), _ordered(0), _start(0)
{
    _array = new T[_capacity];

    DebugLog("Array created with default constuctors");
}

template<typename T>
CDA<T>::CDA(int s)
    : _size(s), _capacity(s), _ordered(0), _start(0)
{
    _array = new T[_capacity];

    DebugLog("Array created with specified size" + std::to_string(s));
}

template<typename T>
CDA<T>::CDA(CDA& c)
    : _size(c.Length()), _capacity(c.Length() + c.EmptySlots()), _ordered(c.Ordered()), _start(0) 
{
    _array = new T[_capacity];

    for(int i = 0; i < _size; i++)
    {
        _array[i] = c[i];
    }
}
template<typename T>
CDA<T>::~CDA()
{
    delete[] _array;

    DebugLog("All memory freed");
}

template<typename T>
CDA<T>& CDA<T>::operator=(CDA& c)
{
    _size = c.Length();
    _capacity = c.Length() + c.EmptySlots();
    _ordered = c.Ordered();
    _start = 0;

    _array = new T[_capacity];

    for(int i = 0; i < _size; i++) _array[i] = c[i];

    return *this;
}
template<typename T>
T& CDA<T>::operator[](int i)
{
    // check for validity of the index
    if(i < 0 || i >= _size || _size < 1)
    {
        std::cout << "[ERROR] Invalid index specified" << std::endl;

        // return a cast value so that there are never errors
          
        return _validreference;
    }

    DebugLog("Index " + std::to_string((_start + i) % _capacity) + " accessed through [ ] overload");

    return _array[(_start + i) % _capacity];
}

template <typename T>
void CDA<T>::AddEnd(T v)
{   
    Extend();

    _array[(_start + _size) % _capacity] = v;

    _size++;

    DebugLog("Node added to end of array");
}

template <typename T>
void CDA<T>::AddFront(T v)
{
    Extend();

    // add element to end of array
    _array[(_start + _capacity - 1) % _capacity] = v;
    _start = (_start + _capacity - 1) % _capacity;

    _size++;

    DebugLog("Node added to front of array");
}

template <typename T>
void CDA<T>::DelEnd()
{
    // list is empty
    if(_size < 1)
    {
        std::cout << "[ERROR] Delete end called, but list is empty!" << std::endl;
        return;
    }

    // end is only element
    if(_size == 1)
    {
        Clear();
    }

    // end is not first
    else
    {
        //_array[(_start + _size) % _capacity] = _validreference;
        _size--;
    }

    Contract();

    DebugLog("Node removed from end of array");
}

template <typename T>
void CDA<T>::DelFront()
{
    // list is empty
    if(_size < 1)
    {
        std::cout << "[ERROR] Delete front called, but list is empty!" << std::endl;
        return;
    }

    // front is only element
    if(_size == 1)
    {
        Clear();
    }

    // front is not first 
    else
    {
        _array[_start] = _validreference;
        _start = (_start + 1) % _capacity;
        _size--;
    }

    Contract();

    DebugLog("Node removed from front of array");
}

template <typename T>
int CDA<T>::Length()
{
    return _size;
}

template <typename T>
int CDA<T>::EmptySlots()
{
    return _capacity - _size;
}

template <typename T>
void CDA<T>::Clear()
{
    delete[] _array;

    _array = new T[1];
    _size = 0;
    _capacity = 1;
    _ordered = 0;
    _start = 0;

    DebugLog("Array cleared");
}

template <typename T>
int CDA<T>::Ordered()
{
    return _ordered;
}

template <typename T>
int CDA<T>::SetOrdered()
{
    bool ascending = true;
    bool descending = true;

    // escape if size is 1 or zero
    if(_size < 2)
    {
        _ordered = 0;
        return _ordered;
    }

    ResetStart();

    // check the front elements first
    if(_array[0] > _array[1]) ascending = false;
    if(_array[0] < _array[1]) descending = false;

    for(int i = 1; i < _size; i++)
    {
        if(_array[i] > _array[i - 1]) descending = false;
        else if(_array[i] < _array[i - 1]) ascending = false;
    }

    if(ascending && !descending) _ordered = 1;
    else if(!ascending && descending) _ordered = -1;
    else _ordered = 0;

    return _ordered;
}

template <typename T>
T CDA<T>::Select(int k)
{
    if(_ordered == 1)
    {
        return _array[(_start + k - 1) % _capacity];
    }
    else if(_ordered == -1)
    {
        return _array[(_start + _size - k) % _capacity];
    }
    else
    {
        // run quickselect algorithm
        ResetStart();


        // i have absolutely no idea why, but quickselect breaks the array and allocating a copy of the original crashes the program, so this hack is my hail mary
        T temp[_capacity];
        for(int i = 0; i < _size; i++) temp[i] = _array[i];

        // call to the recursive function
        T element = QuickSelectSubarray(0, _size - 1, k);

        for(int i = 0; i < _size; i++) _array[i] = temp[i];

        return element;
    }
}

template <typename T>
void CDA<T>::InsertionSort()
{
    // escape if size is 1 or zero
    if(_size < 2)
    {
        _ordered = 0;
        return;
    }
    
    ResetStart();

    T key = 0;
    int j = 0;

    for (int i = 1; i < _size; i++) 
    {  
        key = _array[i];  
        j = i - 1;  
  
        while(j >= 0 && _array[j] > key) 
        {  
            _array[j + 1] = _array[j];  
            j = j - 1;  
        }  
        _array[j + 1] = key;  
    }

    int k = 0, l = _size - 1;

    while(k < l)
    {
        T tmp = _array[k];
        _array[k] = _array[l];
        _array[l] = tmp;
        k++;
        l--;
    }
}

template <typename T>
void CDA<T>::MergeSort()
{
    // escape if size is 1 or zero
    if(_size < 2)
    {
        _ordered = 0;
        return;
    }

    ResetStart();

    MergeSortSubarray( 0, _size - 1);

    int k = 0, l = _size - 1;

    while(k < l)
    {
        T tmp = _array[k];
        _array[k] = _array[l];
        _array[l] = tmp;
        k++;
        l--;
    }
}

template <typename T>
void CDA<T>::CountingSort(int m)
{
    // escape if size is 1 or zero
    if(_size < 2)
    {
        _ordered = 0;
        return;
    }

    ResetStart();

    // find min and max elements of array
    /*
    for(int i = 0; i < _size; i++)
    {
        if(_array[i] < min) min = _array[i];
        else if(_array[i] > max) max = _array[i];
    }*/

    int range = m - 0;

    // create array of counts
    int count[range + 1] = {0};
    T newarray[_capacity];

    // count elements of array
    for(int i = 0; i < _size; i++)
    {
        count[static_cast<int>(_array[i])]++;
    }

    // update counts to reflect position
    for(int j = 1; j <= range; j++)
    {
        count[j] += count[j-1];
    }

    // rebuild new array from counts
    for(int k = 0; k < _size; k++)
    {
        newarray[count[static_cast<int>(_array[k])] - 1] = _array[k];
        count[static_cast<int>(_array[k])]--;
    }

    // write new array to array, in reverse
    for(int i = 0; i < _size; i++) _array[i] = newarray[_size - i - 1];

} 

template <typename T>
int CDA<T>::Search(T e)
{
    if(_ordered == 0)
    {
        ResetStart();

        // linear search for the element
        for(int i = 0; i < _size; i++)
        {
            if(_array[i] == e) return i;
        }
    }
    else
    {
        // array is ordered, so use binary search
        ResetStart();

        return BinarySearch(0, _size - 1, e);
    }
    // unreachable
    return -1;
}

template<typename T>
void CDA<T>::Print()
{
    std::cout << "Start -> ";
    for(int i = 0; i < _size; i++) std::cout << _array[(_start + i) % _capacity] << " -> ";
    std::cout << "End" << std::endl;
}

template <typename T>
T CDA<T>::QuickSelectSubarray(int lower, int upper, int position)
{
    // safety first kids
   if(position > 0 && position <= _size)
   {
       // partition array
       int index = PartitionArray(lower, upper);
    
       // if psoition is correct, return
       if(index - lower == position - 1) return _array[index];

       // if position is greater, run it again
       if(index - lower > position- 1) return QuickSelectSubarray(lower, index - 1, position);

       // if position is less, run it again
       else return QuickSelectSubarray(index + 1, upper, position - index + lower - 1);
   }
   else return _validreference;
}

template <typename T>
int CDA<T>::PartitionArray(int lower, int upper)
{
    T val = _array[upper];
    int i = lower;
    T temp;

    for(int j = lower; j <= upper - 1; j++)
    {
        if(_array[j] <= val)
        {
            // swap array[i] and array[j]
            temp = _array[i];
            _array[i] = _array[j];
            _array[j] = temp;
            i++;
        }
    }

    temp = _array[upper];
    _array[upper] = _array[i];
    _array[i] = temp;

    return i;
}

template <typename T>
void CDA<T>::MergeSortSubarray(int lower, int upper)
{
    if(lower < upper)
    {
        int median = ( (upper - lower) / 2) + lower;

        DebugLog("Mergesort called, with lower index " + std::to_string(lower) + " and upper index " + std::to_string(upper));

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
    for(int i = 0; i < n_lower; i++) lowerArray[i] = _array[i + lower];
    for(int j = 0; j < n_upper; j++) upperArray[j] = _array[j + median + 1];

    // merge temp arrays back into initial array
    while(lowerIndex < n_lower && upperIndex < n_upper)
    {
        if(lowerArray[lowerIndex] <= upperArray[upperIndex])
        {
            _array[mergedIndex] = lowerArray[lowerIndex];
            lowerIndex++;
        }
        else
        {
            _array[mergedIndex] = upperArray[upperIndex];
            upperIndex++;
        }
        mergedIndex++;
    }

    // copy leftover elements from each subarray
    while(lowerIndex < n_lower)
    {
        _array[mergedIndex] = lowerArray[lowerIndex];
        lowerIndex++;
        mergedIndex++;
    }

    while(upperIndex < n_upper)
    {
        _array[mergedIndex] = upperArray[upperIndex];
        upperIndex++;
        mergedIndex++;
    }

    delete[] lowerArray;
    delete[] upperArray;

    DebugLog("Merged array with lower index " + std::to_string(lower) + ", upper index " + std::to_string(upper) + " and median of " + std::to_string(median));
}

template<typename T>
int CDA<T>::BinarySearch(int lower, int upper, T e)
{
    // check boundary validity
    if(lower <= upper)
    {
        int median = (upper - lower) / 2 + lower;

        if(_array[median] == e) return median;

        // sorted low to high (ascending)
        if(_ordered == 1)
        {
            // index is in lower half of array
            if(_array[median] > e) return BinarySearch(lower, median - 1, e);
            // index is in upper half of array
            return BinarySearch(median + 1, upper, e);
        }
        else if(_ordered == -1)
        {
            // index is in lower half of array
            if(_array[median] < e) return BinarySearch(lower, median - 1, e);
            // index is in upper half of array
            return BinarySearch(median + 1, upper, e);
        }
    }
    // unreachable
    return -1;
}

template <typename T>
void CDA<T>::DebugLog(std::string s)
{
    #ifdef _DEBUG_
    std::cout << "> " << s << std::endl;
    #endif
}

template <typename T>
void CDA<T>::Extend()
{
    if(_size >= _capacity)
    {
        int _prevcap = _capacity;
        _capacity *= 2;

        T* temp = new T[_capacity];
        for(int i = 0; i < _size; i++) temp[i] = _array[(_start + i) % _prevcap];
        
        delete[] _array;
        _array = temp;
        _start = 0;

        DebugLog("Capacity expanded to " + std::to_string(_capacity));
    }
}

template <typename T>
void CDA<T>::Contract()
{
    if(_size <= (_capacity / 4)) 
    {
        int _prevcap = _capacity;
        _capacity /= 2;

        T* temp = new T[_capacity];
        for(int i = 0; i < _size; i++) temp[i] = _array[(_start + i) % _prevcap];

        delete[] _array;
        _array = temp;
        _start = 0;

        // default capacity to 1 if it goes lower
        if(_capacity < 1) _capacity = 1;

        DebugLog("Capacity contracted to " + std::to_string(_capacity));
    }
}

template <typename T>
void CDA<T>::ResetStart()
{
        T* temp = new T[_capacity];
        for(int i = 0; i < _size; i++) temp[i] = _array[(_start + i) % _capacity];

        delete[] _array;
        _array = temp;
        _start = 0;

        DebugLog("Array head reset to position 0");
}

template class CDA<int>;
template class CDA<short>;
template class CDA<long>;
template class CDA<long long>;

template class CDA<float>;
template class CDA<double>;
template class CDA<long double>;

//template class CDA<std::string>;
template class CDA<char>;