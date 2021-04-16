/* ==========================
 * Binomial Heap Implementation
 * CS201-001 Spring 2021
 * Developed by Andrew Hansen
 * arhansen@crimson.ua.edu
 * ===========================
 */

#ifndef __BHEAP_HPP__
#define __BHEAP_HPP__

#include <iostream>
#include <vector>
#include <algorithm>
#include "CDA.cpp"

template<typename K>
class BinomialTree
{
    public:
        BinomialTree(int heapClass)
            : heapClass(heapClass)
        {
            array = new CDA<K>();
        }
        ~BinomialTree()
        {
            delete array;
        }

        static bool CompareByClass(const BinomialTree<K>* first, const BinomialTree<K>* second)
        {
            return first->heapClass < second->heapClass;
        }

        BinomialTree<K>* MergeTrees(BinomialTree<K>* first, BinomialTree<K>* second)
        {
            if(first->heapClass != second->heapClass) return NULL;

            BinomialTree<K>* newtree;

            // First will become new root
            if(first->array->operator[](0) < second->array->operator[](0))
            {
                // Create new tree
                newtree = new BinomialTree<K>(first->heapClass + 1);

                // Insert children
                for(int i = 0; i < first->array->Length(); i++) newtree->array->AddEnd(first->array->operator[](i));
                for(int i = 0; i < second->array->Length(); i++) newtree->array->AddEnd(second->array->operator[](i));
            }
            // Second will become new root
            else 
            {
                // Create new tree
                newtree = new BinomialTree<K>(second->heapClass + 1);

                // Insert children
                for(int i = 0; i < second->array->Length(); i++) newtree->array->AddEnd(second->array->operator[](i));
                for(int i = 0; i < first->array->Length(); i++) newtree->array->AddEnd(first->array->operator[](i));
            }

            return newtree;
        }

        void PrintTree()
        {
            std::cout << array->operator[](0) << " ";

            int arrayLength = array->Length();

            // Print sub trees
            for(int i = heapClass - 1; i >= 0; i--)
            {
                BinomialTree<K> temp(i);
                int halfLength = arrayLength / 2;
                for(int j = 0; j < halfLength; j++) temp.array->AddEnd(array->operator[](halfLength + j));
                temp.PrintTree();
                arrayLength /= 2;
            }
        }

        // Class of heap
        int heapClass = 0;
    
        // Array for children
        CDA<K>* array;
};

template<typename K>
class BHeap
{
    public:
        // Default constructor with empty heap
        BHeap();

        // Array constuctor using repeated insertion
        BHeap(K k[], int s);

        // Copy constructor
        BHeap(BHeap& base);

        // Copy assignment operator
        BHeap& operator=(BHeap& base);

        // Destructor
        ~BHeap();

        // Return minimum of heap without modifying the heap
        K peekKey();

        // Remove the minimum key of the heap and return its value
        K extractMin();

        // Insert key k into the tree
        void insert(K k);

        // Merge heap H2 into the current heap, destructively
        void merge(BHeap& H2);

        // Print the keys stored in the heap, starting with the smallest binomial tree first
        void printKey();

    protected:
        std::vector<BinomialTree<K>*>* _rootList;
    
    private:
        unsigned int _minIndex;

        K _sentinel;

        // Helper function to merge nodes with duplicate classes into larger nodes
        void MergeRootList();
        
        // Helper function to sort the root list in ascending order and find the index of the minimum node
        void UpdateMinimum();
};

#endif // !__BHEAP_HPP__