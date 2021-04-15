/* ==========================
 * Binomial Heap Implementation
 * CS201-001 Spring 2021
 * Developed by Andrew Hansen
 * arhansen@crimson.ua.edu
 * ===========================
 */

#include "BHeap.h"

// Default constructor with empty heap
template<typename K>
BHeap<K>::BHeap()
    : _root(NULL)
{
    _rootList = new std::vector<BinomialTree<K>*>();
}

// Array constructor using repeated insertion
template<typename K>
BHeap<K>::BHeap(K k[], int s)
    : _root(NULL)
{
    _rootList = new std::vector<BinomialTree<K>*>();

    for(int i = 0; i < s; i++) insert(k[i]);
}

// Copy constructor
template<typename K>
BHeap<K>::BHeap(BHeap<K>& base)
    : _root(NULL)
{
    _rootList = new std::vector<BinomialTree<K>*>();
}

// Copy assignment operator
template<typename K>
BHeap<K>& BHeap<K>::operator=(BHeap<K>& base)
{
    return *this;
}

// Destructor
template<typename K>
BHeap<K>::~BHeap()
{

}

// Return minimum of heap without modifying the heap
template<typename K>
K BHeap<K>::peekKey()
{
    return _root->array->operator[](0);
}

// Remove the minimum key of the heap and return its value
template<typename K>
K BHeap<K>::extractMin()
{
   return _root->array->operator[](0);
}

// Insert key k into the tree
template<typename K>
void BHeap<K>::insert(K k)
{
    //std::cout << "Insert value " << k << " into tree" << std::endl;

    // Create new node and new subtree
    BinomialTree<K>* newtree = new BinomialTree<K>(0);
    newtree->array->AddFront(k);

    //Empty tree - new heap is only binomial tree
    //if(_root == NULL) _root = newheap;
    if(_rootList->size() == 0)
    {
        _rootList->push_back(newtree);
        _root = newtree;
    }

    // Add new heap to existing root list
    else
    {
        // Add new heap to root list
        _rootList->push_back(newtree);

        MergeRootList();

        UpdateRoot();
    }
}

// Merge heap H2 into the current heap, destructively
template<typename K>
void BHeap<K>::merge(BHeap& H2)
{
    
}

// Print the keys stored in the heap, starting with the smallest binomial tree first
template<typename K>
void BHeap<K>::printKey()
{
    
    // Sort root list in ascending order
    UpdateRoot();

    for(int i = _rootList->size() - 1; i >= 0; i--)
    {
        std::cout << "B" << _rootList->at(i)->heapClass << std::endl;
        _rootList->at(i)->PrintTree();
        std::cout << std::endl << std::endl;
    }
}

template<typename K>
void BHeap<K>::MergeRootList()
{
    int binaryRepresentation = 0;
    unsigned int numRoots = _rootList->size();

    for(unsigned int i = 0; i < numRoots; i++)
    {
        // Get current tree in list
        BinomialTree<K>* currentTree = _rootList->at(i);

        // Check for duplicate tree - if duplicate, merge trees
        if(binaryRepresentation & (1 << currentTree->heapClass))
        {
            // Find other instance of tree with same size
            for(unsigned int j = 0; j < i; j++)
            {
                // Match found
                if(_rootList->at(j)->heapClass == currentTree->heapClass)
                {
                    BinomialTree<K>* mergedTrees = currentTree->MergeTrees(currentTree, _rootList->at(j));

                    _rootList->erase(_rootList->begin() + i);
                    _rootList->erase(_rootList->begin() + j);

                    _rootList->push_back(mergedTrees);


                    // Recurse and return
                    MergeRootList();
                    return;
                }
            }
        }

        // Not already in representation - add to representation and continue
        else
        {
            binaryRepresentation = (binaryRepresentation | (1 << currentTree->heapClass));
        }
    }
}
/*{
    int binaryRepresentation = 0;
    unsigned int numRoots = _rootList->size();

    unsigned int tempIndex = 0;
    unsigned int otherIndex = 0;

    for(unsigned int i = 0; i < numRoots; i++)
    {
        BinomialTree<K>* temp = _rootList->at(i);

        tempIndex = i;

        // Entry already at position
        if(binaryRepresentation & (1 << temp->heapClass))
        {
            //std::cout << "Merging trees of duplicate size: B" << temp->heapClass << std::endl; 
            //printKey();

            // Merge duplicate trees
            BinomialTree<K>* otherTree = _rootList->at(0);

            for(unsigned int j = 0; j < tempIndex; j++)
            {
                if(otherTree->heapClass == temp->heapClass) otherTree = _rootList->at(j);
                otherIndex = j;
            }

            // Make sure we're not trying to merge the same tree
            if(tempIndex == otherIndex) break;

            //std::cout << "temp tree is key " << temp->root->key << ", other is " << otherTree->root->key << std::endl;
            //std::cout << "INDICES " << tempIndex << " " << otherIndex << " " << _rootList->size() << std::endl;

            // Found second tree, combine trees - smaller index should be root
            HeapNode<K>* newHeapRoot;

            // Error checking
            if(temp->heapClass != otherTree->heapClass)
            {
                std::cout << "[Error] Merge of non-matching heap classes" << std::endl;
                return;
            }

            // Temp has smaller key, parent of other
            if(temp->root->key < otherTree->root->key)
            {
                newHeapRoot = temp->root;

                // Set children
                HeapNode<K>* prevChild = newHeapRoot->child;
                newHeapRoot->child = otherTree->root;
                otherTree->root->parent = newHeapRoot;
                otherTree->root->rightSibling = prevChild;
                if(prevChild != NULL) prevChild->leftSibling = otherTree->root;
            }
            // Other has smaller key, parent of temp
            else 
            {
                newHeapRoot = otherTree->root;

                // Set children
                HeapNode<K>* prevChild = newHeapRoot->child;
                newHeapRoot->child = temp->root;
                temp->root->parent = newHeapRoot;
                temp->root->rightSibling = prevChild;
                if(prevChild != NULL) prevChild->leftSibling = temp->root;
            }

            // Build new tree
            BinomialTree<K>* newtree = new BinomialTree<K>(newHeapRoot, temp->heapClass + 1);

            // Remove old trees from root list
            _rootList->erase(_rootList->begin() + otherIndex);
            _rootList->erase(_rootList->begin() + tempIndex);

            // Update representation
            binaryRepresentation++;// = (binaryRepresentation ^ (1 << (temp->heapClass + 1)));
            std::cout << "New bin rep is " << binaryRepresentation << std::endl;

            // Insert new tree into end of list
            _rootList->push_back(newtree);
        }

        // Update array
        else 
        {
            binaryRepresentation = (binaryRepresentation | (1 << temp->heapClass));

            //std::cout << "Binary rep now contains tree B" << temp->heapClass << std::endl;
        }
    }
}*/

template<typename K>
void BHeap<K>::UpdateRoot()
{
    std::sort(_rootList->begin(), _rootList->end());

    _root = _rootList->at(0);
}