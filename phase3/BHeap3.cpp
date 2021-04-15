#include "BHeap3.hpp"

template<typename K>
BHeap<K>::BHeap()
{
	head = NULL;
}

template<typename K>
BHeap<K>::BHeap(K k[], int s)
{
    head = NULL;

    for(int i = 0; i < s; i++) insert(k[i]);
}
template<typename K>
BHeap<K>::BHeap(const BHeap<K>& other)
{
	//invoke = op
	*this = other;
}

template<typename K>
BHeap<K>& BHeap<K>::operator=(const BHeap<K>& other)
{
	head = NULL;
	if(other.head)
		other.head->addTo(this);
}

template<typename K>
BHeap<K>::~BHeap()
{
	clear();
}
template<typename K>
void BHeap<K>::clear()
{
	delete head;
	head = nullptr;
}

template<typename K>
bool BHeap<K>::isEmpty()
{
	return (head==0);
}

template<typename K>
void BHeap<K>::insert(K key)
{
	BinomialNode<K> *p = head?  head->parent:  nullptr;
	BinomialNode<K> *singleton = new BinomialNode<K>(key, p);
	head = unionHeap(singleton, head);

}

template<typename K>
K BHeap<K>::peekKey()
{
	K min;
	if(head)
	{
		BinomialNode<K>* temp = head;
		min = head->key;
		while(temp)
		{
			if(temp->key < min)
			{
				min = temp->key;
			}
			temp = temp->sibling;
		}

	}
	return min;
}

template<typename K>
K BHeap<K>::extractMin()
{
	BinomialNode<K> *prev=nullptr, 
					*min=nullptr, 
					*temp=nullptr, 
					*next=nullptr;
	K minkey;
	if(head)
	{
		BinomialNode<K>* minPrev = nullptr; //previous node of min node
		min = head;
		temp = head->sibling;
		prev= head;
		/*
		 * Find min and minPrev of heaps
		 */
		while(temp)
		{
			if(temp->key < min->key)
			{
				min = temp;
				minPrev= prev;
			}
			prev= prev->sibling;
			temp = temp->sibling;
		}
		/*
		 *  If prev, assign prev sibling to min sibling.
		 *  Else if no prev min->sibling is new head
		 */
		if(minPrev)
		{
			minPrev->sibling=min->sibling;
		}
		else
		{
			head = min->sibling;
		}
		/*
		 * Update all children nodes parent pointers to null
		*/
		next = min->child;
		temp = next;
		while(temp)
		{
			temp->parent = min->parent;
			temp = temp->sibling;
		}
		/*
		 * Detach and delete min
		 */
		min->sibling = nullptr;
		min->child = nullptr;
		min->parent = nullptr;
		minkey=  min->key;
		delete min;
		/*
		 * Union the two detached heaps
		 */
		head = unionHeap(head, next);
		temp = min = minPrev = next= nullptr;
	}
	else
		std::cout << "Empty Heap!" << std::endl;
        return _sentinel;

	return minkey;
}

/*
 *
 */
template<typename K>
int BHeap<K>::size()
{
	int i = 0;
	if(head)
		head->size(i);
	return i;
}

template<typename K>
void BHeap<K>::deleteKey(K key)
{
	decreaseKey(key, peekKey()-1); //set to min
	extractMin();
}

template<typename K>
void BHeap<K>::decreaseKey(K key, K newKey)
{
	if(head)
	{
		if(key > newKey)
		{
			/*
			 * maintains heap property by bubbling current until parent > current
			 */
			BinomialNode<K> *current = head->find(key), 
							*parent = nullptr;
			K temp;
			if(current)
			{
				current->key = newKey;
				parent = current->parent;

				while(current && parent && (current->key < parent->key))
				{
					temp = current->key;
					current->key = parent->key;
					parent->key  = temp;
					current = parent;
					parent = current->parent;
				}
			}
			else
			{
				throw BHeap<K>::Exception("Key not found!");
			}	
		}
		else
			throw BHeap<K>::Exception("New Key must be less than current key!");
	}
	else
	{
		throw BHeap<K>::Exception("Heap is empty!");
	}
}
template<typename K>
BinomialNode<K>* BHeap<K>::findKey(K key)
{
	if(head)
	{
		return head->find(key);
	}
	return nullptr;
}

template<typename K>
int BHeap<K>::order(BinomialNode<K>* heap)
{
	if(!heap)
		return -1;
	int i = 0;
	BinomialNode<K>* child = heap->child;
	while(child)
	{
		++i;
		child = child->sibling;
	}
	return i;
}


template<typename K>
BinomialNode<K>* BHeap<K>::unionHeap(BinomialNode<K>* heapA, BinomialNode<K>* heapB)
{
	/*
	 * Merges heapA and heapB assuming both are sorted by heap order
	 * concatenates heaps of same order so that at most one tree of each order
	*/

	/*
	 * get merged heap of heapA and heapB
	 */
	BinomialNode<K>* heapU  = mergeHeap(heapA, heapB);
	if(heapU)
	{
		/*    prev   cur      next
		 * U-> |_|-> |_|->    |_|->
		 *            |        |
		 *           |_|->    |_|->
		 */
		BinomialNode<K>
			*cur = heapU,  // current node to append before or after
			*prev = nullptr, // node with sibling equal to current
			*next = nullptr; // the next potential
		int orderA, orderB;
		while(cur && cur->sibling)
		{
			next = cur->sibling;
			orderA = cur->order;
			orderB = next->order;
			if(orderA == orderB && orderA != order(next->sibling))
			{
				//Next becomes Current's Child
				if(cur->key < next->key)
				{
					cur->sibling = next->sibling;
					cur->addChild(next);
					//tempNext->parent = cur;
					prev = cur;
					cur = cur->sibling;
				}
				else //Current becomes Next's Child
				{
					if(prev)
						prev->sibling = next;
					else
						heapU = next;
					next->addChild(cur);
					prev = next;
					cur = next->sibling;
				}
			}
			else
			{
				// got to Next's Child
				if(!prev)
					heapU = cur;
				prev = cur;
				cur = next;
			}
		}
	}

	return heapU;
}


template<typename K>
BinomialNode<K>* BHeap<K>::mergeHeap(BinomialNode<K>* heapA, BinomialNode<K>* heapB)
{
	//modify to insert
	BinomialNode<K>* heapM = nullptr;//merged heap

	if(heapA || heapB)
	{
		if(heapA && !heapB)
		{
			heapM = heapA;
		}
		else if(!heapA && heapB)
		{
			heapM = heapB;
		}
		else
		{
			BinomialNode<K>*temp = nullptr, 
							*next = nullptr, 
							*prev = nullptr,
							*cur = nullptr;
			//pick minimum heap root to be merged heap root
			if(heapA->order > heapB->order)
			{
				heapM = heapB;
				next = heapA;

			}else
			{
				heapM = heapA;
				next = heapB;
			}
			cur = heapM;
			//Merges heap by reassigning sibling pointers
			while(cur && next && cur != next)
			{
				if(cur->order <= next->order)
				{
					if(cur->sibling)
					{
						temp = cur->sibling;
						cur->sibling = next;
						prev = cur;
						cur = next;
						next = temp;
					}
					else
					{
						cur->sibling = next;
						cur = next; // break loop
					}
				}
				else
				{
					if(prev)
						prev->sibling = next;
					else
						heapM = next;
					temp=next->sibling;
					next->sibling = cur;
					prev = next;
					next= temp;

				}
			}

		}
	}
	return heapM;
}