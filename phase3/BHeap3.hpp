/*
	Binomial Heap : Priority Queue Data Structure using C++11
	@author:	github.com/138paulmiller
*/


#ifndef BHeap_H_
#define BHeap_H_


#define DEBUG false
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ostream>

#include <string>

template<typename K>
class BHeap;

template <typename K>
class BinomialNode
{
	public:
		friend class BHeap<K>;
		BinomialNode(K key, BinomialNode<K>* parent = NULL)
		{
			key = key;
			parent = parent;
			sibling = NULL;
			child = NULL;
			order =  0;
		}

		~BinomialNode()
		{
			delete child;
			delete sibling;
		}

		void addChild(BinomialNode<K>* childNode)
		{
			if(childNode)
			{
				childNode->sibling = nullptr;
				if(child)
				{
					BinomialNode<K>* temp = child;
					while(temp->sibling)
					{
						temp = temp->sibling;
					}
					temp->sibling = childNode;
				}
				else
				{
					child = childNode;
				}
				//
				++order;
				childNode->parent = this;
			}
		}

		BinomialNode<K>* find(K k)
		{
			BinomialNode<K>* found = NULL;
			if(k == key)
				return this;
			else if(sibling)
			{
				found = sibling->find(k);
			}
			if( key < k && !found)
			{
				if(child)
				{
					found = child->find(k);
				}
			}

			return found;
		}

		int size(int& i)
		{
			++i;
			if(sibling != NULL)
				sibling->size(i);
			if(child != NULL)
				child->size(i);

			return i;
		}
		void addTo(BHeap<K>* other)
		{
			other->insert(key);
			if(sibling != NULL)
			{
				sibling->addTo(other);
			}

			if(child != NULL)
			{
				child->addTo(other);
			}
		}
	private:
		K key;
		BinomialNode<K>* sibling;
		BinomialNode<K>* child;
		BinomialNode<K>* parent;
		int order;
};

template <typename K>
class BHeap
{

	public:
		friend class BinomialNode<K>;
		
		BHeap();
		BHeap(K k[], int s);
		BHeap(const BHeap& other);
		BHeap& operator=(const BHeap& other);
		~BHeap();
		void insert(K key);
		K peekKey();
		K extractMin();
		void deleteKey(K key);
		void decreaseKey(K key, K newkey);
		int size();
		bool isEmpty();
		void clear();
	protected:
		BinomialNode<K>* findKey(K v);
		/*
		* unionHeap
		* 		Consolidates two heaps by merging them into a single
		* 		The heap is appended to the end of the child list to maintain child order
		* 		of roots from min to max
		* 		Assumes heapA and heapB siblings are ordered by root order(sibling count)
		*
		* 	HeapA - root of heap to union with heapB
		* 	HeapB - root of heap to union with heapA
		*
		*
		* 	returns
		* 		the root of the heap representing the union of heapA and heapB
		* 		such that the either heapA becomes a child of heapB or the reverse
		*/
		static BinomialNode<K>* unionHeap(BinomialNode<K>* heapA, BinomialNode<K>* heapB);
		/* mergeHeap
		* 		Merges two heaps into a single Binomial heap by adding
		* 		all siblings of heapA and heapB into a single heap containing
		* 		all nodes in heapA and heapB.
		* 		Assumes heapA and heapB siblings are ordered by root order(sibling count)
		* 		Consolidating two heaps maintains merged ordering
		*
		* 	HeapA - root of heap to union with heapB
		* 	HeapB - root of heap to union with heapA
		*
		* 	returns
		* 		the root of the new heap that contains all heapA and heapB nodes
		*
		*/
		static BinomialNode<K>* mergeHeap(BinomialNode<K>* heapA, BinomialNode<K>* heapB);
		/*
		* order
		* 		Number of children incident on heap
		* 	heap
		* 		pointer to root of Binomial heap
		* 	returns
		* 		order or heap
		*/
		static int order(BinomialNode<K>* heap);

	private:
		BinomialNode<K>* head;
		K _sentinel;
};

#endif /* BHeap_H_ */