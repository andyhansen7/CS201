/* ==========================
 * 2-3-4 Tree
 * CS201-001 Fall 2020
 * Developed by Andrew Hansen
 * arhansen@crimson.ua.edu
 * ===========================
 */

#include "Two4Tree.h"

template<typename K, typename V>
Two4Tree<K, V>::Two4Tree()
    : _root(nullptr), _size(0) {
    debuglog("2-3-4 tree created with no parameters.");
}

template<typename K, typename V>
Two4Tree<K, V>::Two4Tree(K keys[], V values[], int s) 
    : _root(nullptr), _size(s) {
    debuglog("2-3-4 tree created with array parameters, beginning insert operations.");

    // insert nodes from arrays sequentially
    for(int i = 0; i < s; i++) insert(keys[i], values[i]);

    debuglog("2-3-4 tree creation from array completed successfully.");
}

template<typename K, typename V>
Two4Tree<K, V>::Two4Tree(Two4Tree& base)  
    : _root(nullptr), _size(0) {

    tempsize = 0;
    Node<K,V>* array[base.size()];

    buildarray(base.getroot(), array);

    // build new array
    _root = nullptr;

    for(int i = 0; i < base.size(); i++) {
        insert(array[i]->key, array[i]->value);
    }
}

template<typename K, typename V>
Two4Tree<K, V>& Two4Tree<K, V>::operator=(Two4Tree<K, V>& base) {

    tempsize = 0;
    Node<K,V>* array[base.size()];

    buildarray(base.getroot(), array);

    // build new array
    _root = nullptr;
    _size = 0;

    for(int i = 0; i < base.size(); i++) {
        insert(array[i]->key, array[i]->value);
    }

    return *this;
}

template<typename K, typename V>
Two4Tree<K, V>::~Two4Tree() {
    debuglog("Destructor called for 2-3-4 tree.");

    recursivedelete(_root);

    debuglog("Destruction completed.");
}

template<typename K, typename V>
V* Two4Tree<K, V>::search(K key) {
    //debuglog("Recursively searching for value of key " + std::to_string(key));

    Node<K, V>* node = recursivesearch(_root, key);

    if(node == nullptr) {
        V* val = new V(static_cast<V>(0));
        return val;
    }
    else {
        V* val = &(node->value);
        return val;
    }
}

template<typename K, typename V>
void Two4Tree<K, V>::insert(K key, V value) {
    //debuglog("Insert operation called for new node with value " + std::to_string(value) + " and key " + std::to_string(key));

    // create a new node for the value
    Node<K, V>* newnode = new Node<K, V>();
    newnode->key = key;
    newnode->value = value;

    // increment size
    _size++;

    // check if tree is empty - node becomes root
    if(_root == nullptr) {
        TwoThreeFourNode<K, V>* newinternalnode = new TwoThreeFourNode<K, V>();
        newinternalnode->internal = false;
        newinternalnode->node_class = NodeClass::TWONODE;
        newinternalnode->pivot0 = newnode;

        _root = newinternalnode;

        debuglog("\tInsert operation completed sucessfully with new node as root.");
        return;
    }
    else {
        recursiveinsert(newnode, _root);

        debuglog("\tInsert operation completed sucessfully.");
    }
}

template<typename K, typename V>
int Two4Tree<K, V>::remove(K key) {
    //debuglog("Remove operation called for new node with key " + std::to_string(key));

    // if node is not in tree, return
    if(recursivesearch(_root, key) == nullptr) {
        debuglog("Remove called for node not in tree.");
        return 0;
    }
    else {
        tempsize = 0;
        Node<K,V>* array[_size];// = {};

        buildarray(_root, array);

        // remove node from array
        for(int i = 0; i < tempsize; i++) {
            if(array[i]->key == key) {
                for(int j = i; j < tempsize - 1; j++) {
                    array[j] = array[j+1];
                }
            }
        }

        // decrease size
        _size--;

        // build new array
        _root = nullptr;

        for(int i = 0; i < tempsize - 1; i++) {
            insert(array[i]->key, array[i]->value);
        }

        return 1;
    }

    // unreachable
    return 0;
}

template<typename K, typename V>
int Two4Tree<K, V>::rank(K key) {
    //debuglog("Rank operation called for new node with key " + std::to_string(key));

    //setranks(_root, 1);

    //return recursiverank(_root, key);

    tempsize = 0;
    Node<K,V>* array[_size];// = {};

    buildarray(_root, array);

    for(int i = 0; i < tempsize; i++) {
        // correct node
        if(array[i]->key == key) {
            return (i + 1);
        }
    }

    // node not in tree
    return 0;
}

template<typename K, typename V>
K Two4Tree<K, V>::select(int pos) {
    //debuglog("Select operation called for new node with position " + std::to_string(pos));

    tempsize = 0;
    Node<K,V>* array[_size];// = {};

    buildarray(_root, array);

    int n = pos - 1;

    if(n < tempsize) return array[n]->key;
    else {
        debuglog("Invalid index specified for select");
        return static_cast<K>(0);
    }
}

template<typename K, typename V>
K Two4Tree<K, V>::successor(K key) {
    //debuglog("Sucessor operation called for new node with key " + std::to_string(key));

    tempsize = 0;
    Node<K,V>* array[_size];// = {};

    buildarray(_root, array);

    for(int i = 0; i < tempsize; i++) {
        if(array[i]->key == key) {
            if(i < tempsize - 1) return array[i+1]->key;
            else {
                debuglog("Invalid key for successor");
                return static_cast<K>(0);
            }
        }
    }

    // node not in tree
    debuglog("Node not in tree for successor");
    return static_cast<K>(0);
}

template<typename K, typename V>
K Two4Tree<K, V>::predecessor(K key) {
    //debuglog("Predecessor operation called for new node with key " + std::to_string(key));
        
    tempsize = 0;
    Node<K,V>* array[_size];// = {};

    buildarray(_root, array);

    for(int i = 0; i < tempsize; i++) {
        if(array[i]->key == key) {
            if(i > 0) return array[i-1]->key;
            else {
                debuglog("Invalid key for predecessor");
                return static_cast<K>(0);
            }
        }
    }

    // node not in tree
    debuglog("Node not in tree for predecessor");
    return static_cast<K>(0);
}

template<typename K, typename V>
int Two4Tree<K, V>::size() {
    debuglog("Size operation called.");

    return _size;
}

template<typename K, typename V>
void Two4Tree<K, V>::preorder() {
    debuglog("Printing preorder transversal for tree.");

    recursivepreorder(_root);

    _stream << std::endl;
}

template<typename K, typename V>
void Two4Tree<K, V>::inorder() {
    debuglog("Printing inorder transversal for tree.");

    //_stream << std::endl;

    recursiveinorder(_root);

    _stream << std::endl;
}

template<typename K, typename V>
void Two4Tree<K, V>::postorder() {
    debuglog("Printing postorder transversal for tree.");

    recursivepostorder(_root);

    _stream << std::endl;
}

template<typename K, typename V>
void Two4Tree<K, V>::debug() {
    //#define _DEBUG_
}

template<typename K, typename V>
void Two4Tree<K, V>::buildarray(TwoThreeFourNode<K,V>* node, Node<K, V>** array) {
    if(node->internal) {
        switch(node->node_class) {
            case NodeClass::TWONODE:
                //debuglog("2 NODE");

                buildarray(node->child0, array);

                array[tempsize] = node->pivot0;
                tempsize++;

                buildarray(node->child1, array);

                break;
            case NodeClass::THREENODE:
                //debuglog("3 NODE");

                buildarray(node->child0, array);

                array[tempsize] = node->pivot0;
                tempsize++;

                buildarray(node->child1, array);

                array[tempsize] = node->pivot1;
                tempsize++;

                buildarray(node->child2, array);

                break;
            case NodeClass::FOURNODE:
                //debuglog("4 NODE");

                buildarray(node->child0, array);

                array[tempsize] = node->pivot0;
                tempsize++;

                buildarray(node->child1, array);

                array[tempsize] = node->pivot1;
                tempsize++;

                buildarray(node->child2, array);

                array[tempsize] = node->pivot2;
                tempsize++;

                buildarray(node->child3, array);
                
                break;
            default: break;
        }
    }
    else {
        switch(node->node_class) {
            case NodeClass::TWONODE:
                array[tempsize] = node->pivot0;
                tempsize++;

                break;
            case NodeClass::THREENODE:
                array[tempsize] = node->pivot0;
                tempsize++;

                array[tempsize] = node->pivot1;
                tempsize++;

                break;
            case NodeClass::FOURNODE:
                array[tempsize] = node->pivot0;
                tempsize++;

                array[tempsize] = node->pivot1;
                tempsize++;

                array[tempsize] = node->pivot2;
                tempsize++;
            
                break;
            default: break;
        }
    }
}

template<typename K, typename V>
TwoThreeFourNode<K, V>* Two4Tree<K, V>::getroot() {
    return _root;
}

template<typename K, typename V>
Node<K,V>* Two4Tree<K, V>::recursivesearch(TwoThreeFourNode<K, V>* node, K key) {
    // check if key is in current node
    switch(node->node_class) {
        case NodeClass::TWONODE:
            if(node->pivot0->key == key) return node->pivot0;

            if(node->internal) {
                if(key < node->pivot0->key) return recursivesearch(node->child0, key);
                else return recursivesearch(node->child1, key);
            }

            else {
                debuglog("Search called for node not in tree");
                return nullptr;
            }

            break;

        case NodeClass::THREENODE:
            if(node->pivot0->key == key) return node->pivot0;
            else if(node->pivot1->key == key) return node->pivot1;

            if(node->internal) {
                if(key < node->pivot0->key) return recursivesearch(node->child0, key);
                else if(key >= node->pivot0->key && key < node->pivot1->key) return recursivesearch(node->child1, key);
                else return recursivesearch(node->child2, key);
            }

            else {
                debuglog("Search called for node not in tree");
                return nullptr;
            }

            break;

        case NodeClass::FOURNODE:
            if(node->pivot0->key == key) return node->pivot0;
            else if(node->pivot1->key == key) return node->pivot1;
            else if(node->pivot2->key == key) return node->pivot2;

            if(node->internal) {
                if(key < node->pivot0->key) return recursivesearch(node->child0, key);
                else if(key >= node->pivot0->key && key < node->pivot1->key) return recursivesearch(node->child1, key);
                else if(key >= node->pivot1->key && key < node->pivot2->key) return recursivesearch(node->child2, key);
                else return recursivesearch(node->child3, key);
            }

            else {
                debuglog("Search called for node not in tree");
                return nullptr;
            }

            break;

        default: break;
    }

    // unreachable
    return nullptr;
}

template<typename K, typename V>
void Two4Tree<K, V>::recursiveinsert(Node<K, V>* newnode, TwoThreeFourNode<K, V>* currentnode) {
   // debuglog("Recursive insert called for node with key " + std::to_string(newnode->key));

    // if currentnode is nullptr, create a new 2-node with the newnode as the pivot - should never happen
    if(currentnode == nullptr)
    {
        debuglog("currentnode was null pointer - new node created.");

        TwoThreeFourNode<K, V>* newcurrentnode = new TwoThreeFourNode<K, V>;
        newcurrentnode->internal = false;
        newcurrentnode->node_class = NodeClass::TWONODE;
        newcurrentnode->pivot0 = newnode;

        return;
    }

    switch(currentnode->node_class)
    {
        case NodeClass::TWONODE:         // currentnode is a 2-Node

            //debuglog("current node is a 2-node with pivot " + std::to_string(currentnode->pivot0->key));

            // recursive call if currentnode is internal
            if(currentnode->internal) {
                // recursive call on left child
                if(newnode->key < currentnode->pivot0->key) {
                    debuglog("\tRecursive calling on left child of currentnode.");

                    recursiveinsert(newnode, currentnode->child0);
                    return;
                }

                // recursive call on right child
                else {
                    debuglog("\tRecursive calling on right child of currentnode.");

                    recursiveinsert(newnode, currentnode->child1);
                    return;
                }
            }

            // currentnode is a leaf node - insert node
            else {
                debuglog("Inserting new node into leaf node.");

                currentnode->node_class = NodeClass::THREENODE;

                // new node is greater than current pivot
                if(newnode->key > currentnode->pivot0->key) {
                    debuglog("\tNew node inserted as greater pivot.");

                    currentnode->pivot1 = newnode;
                    return;
                }

                // new node is less than current pivot
                else {
                    debuglog("\tNew node inserted as lesser pivot.");

                    currentnode->pivot1 = currentnode->pivot0;
                    currentnode->pivot0 = newnode;
                    return;
                }
            }

            break;

        case NodeClass::THREENODE:         // currentnode is a 3-Node

            //debuglog("currentnode node is a 3-node with pivots " + std::to_string(currentnode->pivot0->key) + ", " + std::to_string(currentnode->pivot1->key));
            
            // recursive call if currentnode is internal
            if(currentnode->internal)
            {
                // recursive call on left child
                if(newnode->key < currentnode->pivot0->key) {
                    debuglog("\tRecursive calling on left child of currentnode.");

                    recursiveinsert(newnode, currentnode->child0);
                    return;
                }
                // recursive call on middle child
                else if(newnode->key >= currentnode->pivot0->key && newnode->key < currentnode->pivot1->key) {
                    debuglog("\tRecursive calling on middle child of currentnode.");

                    recursiveinsert(newnode, currentnode->child1);
                    return;
                }
                // recursive call on right child
                else {
                    debuglog("\tRecursive calling on right child of currentnode.");

                    recursiveinsert(newnode, currentnode->child2);
                    return;
                }

            }
            // currentnode is a leaf node - insert node
            else {
                debuglog("Inserting new node into leaf node.");

                currentnode->node_class = NodeClass::FOURNODE;

                // new node is less than lower pivot
                if(newnode->key < currentnode->pivot0->key) {
                    debuglog("\tNew node inserted as lesser pivot.");

                    currentnode->pivot2 = currentnode->pivot1;
                    currentnode->pivot1 = currentnode->pivot0;
                    currentnode->pivot0 = newnode;
                    return;
                }

                // new node is between pivots
                else if(newnode->key >= currentnode->pivot0->key && newnode->key < currentnode->pivot1->key) {
                    debuglog("\tNew node inserted as middle pivot.");

                    currentnode->pivot2 = currentnode->pivot1;
                    currentnode->pivot1 = newnode;
                    return;
                }

                // new node is greater than upper pivot
                else {
                    debuglog("\tNew node inserted as greater pivot.");
                    
                    currentnode->pivot2 = newnode;
                    return;
                }

            }

            break;

        case NodeClass::FOURNODE:         // currentnode is a 4-node

            //debuglog("currentnode node is a 4-node with pivots " + std::to_string(currentnode->pivot0->key) + ", " + std::to_string(currentnode->pivot1->key) + ", " + std::to_string(currentnode->pivot2->key));

            // recursive call if currentnode is internal
            if(currentnode->internal) {
                // recursive call on left child
                if(newnode->key < currentnode->pivot0->key) {
                    debuglog("\tRecursive calling on left child of currentnode.");

                    recursiveinsert(newnode, currentnode->child0);
                    return;
                }

                // recursive call on left-middle child
                else if(newnode->key >= currentnode->pivot0->key && newnode->key < currentnode->pivot1->key) {
                    debuglog("\tRecursive calling on left-middle child of currentnode.");

                    recursiveinsert(newnode, currentnode->child1);
                    return;
                }

                // recursive call on right-middle child
                else if(newnode->key >= currentnode->pivot1->key && newnode->key < currentnode->pivot2->key) {
                    debuglog("\tRecursive calling on right-middle of currentnode.");

                    recursiveinsert(newnode, currentnode->child2);
                    return;
                }

                // recursive call on right child
                else {
                    debuglog("\tRecursive calling on right child of currentnode.");
                    
                    recursiveinsert(newnode, currentnode->child3);
                    return;
                }
            }
            // split 4 node if node is a leaf node
            else {
                debuglog("Splitting 4 node before recursively calling.");

                // if current node is root, split into multiple 2-nodes
                if(currentnode->parent == nullptr) {
                    debuglog("Splitting root node in recursive insert.");

                    TwoThreeFourNode<K, V>* left = new TwoThreeFourNode<K, V>();
                    TwoThreeFourNode<K, V>* right = new TwoThreeFourNode<K, V>();

                    left->internal = false;
                    right->internal = false;
                    currentnode->internal = true;

                    left->node_class = NodeClass::TWONODE;
                    right->node_class = NodeClass::TWONODE;
                    currentnode->node_class = NodeClass::TWONODE;

                    left->parent = currentnode;
                    right->parent = currentnode;

                    left->pivot0 = currentnode->pivot0;
                    currentnode->pivot0 = currentnode->pivot1;
                    right->pivot0 = currentnode->pivot2;

                    currentnode->pivot1 = nullptr;
                    currentnode->pivot2 = nullptr;

                    /*left->child0 = currentnode->child0;
                    left->child1 = currentnode->child1;
                    right->child0 = currentnode->child2;
                    right->child1 = currentnode->child3;*/
                    
                    currentnode->child0 = left;
                    currentnode->child1 = right;

                    recursiveinsert(newnode, _root);
                }
                // current node is not parent - sift up
                else {
                    debuglog("Calling sift before insertion");
                    
                    siftup(currentnode, currentnode->parent);

                    debuglog("Running recursive insert again.");

                    recursiveinsert(newnode, _root);
                }
            
            }
            break;

        default: 
            debuglog("One or more nodes is fucked. Insert called on node with no class");
            break;
    }
}

template<typename K, typename V>
void Two4Tree<K, V>::siftup(TwoThreeFourNode<K, V>* lower, TwoThreeFourNode<K, V>* upper) {
    debuglog("Sift up process started.");

    /*std::cout << "LOWER:" << std::endl;
    recursiveinorder(lower);
    std::cout << "UPPER:" << std::endl;
    recursiveinorder(upper);
    std::cout << std::endl;*/

    // if parent is 4-node already, recursive call
    if(upper->node_class == NodeClass::FOURNODE) {
        // parent is root of tree - split into 2 2-nodes
        if(upper->parent == nullptr) {
            debuglog("\tRoot was a 4-node. Splitting and recursive calling.");

            // new node creation
            TwoThreeFourNode<K, V>* root = new TwoThreeFourNode<K, V>();
            TwoThreeFourNode<K, V>* left = new TwoThreeFourNode<K, V>();
            TwoThreeFourNode<K, V>* right = new TwoThreeFourNode<K, V>();

            // assign internal values
            left->internal = true;
            right->internal = true;
            root->internal = true;

            // assign node classes
            left->node_class = NodeClass::TWONODE;
            right->node_class = NodeClass::TWONODE;
            root->node_class = NodeClass::TWONODE;

            // set upper to be parent of new nodes
            left->parent = root;
            right->parent = root;

            // set pivots for new nodes and update current node
            left->pivot0 = upper->pivot0;
            right->pivot0 = upper->pivot2;
            root->pivot0 = upper->pivot1;

            // set children of new 2-nodes
            left->child0 = upper->child0;
            left->child1 = upper->child1;
            right->child0 = upper->child2;
            right->child2 = upper->child3;

            // set children of upper node
            root->child0 = left;
            root->child1 = right;

            // set new parents of all children nodes
            upper->child0->parent = left;
            upper->child1->parent = left;
            upper->child2->parent = right;
            upper->child3->parent = right;

            _root = root;
            
            // recursive call to sift
            siftup(lower, lower->parent);

            return;
        }
        // parent is not root
        else {
            debuglog("\tParent was a 4-node. Recursive calling.");

            //siftup(upper, upper->parent);

            //siftup(lower, lower->parent);

            if(upper->child0 == lower) {
                //std::cout << "CHILD0" << std::endl;
                siftup(upper, upper->parent);
                //siftup(upper->child0, upper);
                return;
            }
            if(upper->child1 == lower) {
                //std::cout << "CHILD1" << std::endl;
                siftup(upper, upper->parent);
                //siftup(upper->child1, upper);
                return;
            }
            if(upper->child2 == lower) {
                //std::cout << "CHILD2" << std::endl;
                siftup(upper, upper->parent);
                //siftup(upper->child2, upper);
                return;
            }
            else {
                //std::cout << "CHILD3" << std::endl;
                siftup(upper, upper->parent);
                /*std::cout << std::endl << std::endl;
                recursiveinorder(_root);
                std::cout << std::endl << std::endl;*/
                //siftup(upper->child3, upper);
                return;
            }
        }
    }

    // parent is not 4-node - continue
    else {
        TwoThreeFourNode<K, V>* newnode = new TwoThreeFourNode<K, V>;
        newnode->internal = lower->internal;
        newnode->parent = upper;
        newnode->node_class = NodeClass::TWONODE;

        switch(upper->node_class) {
            case NodeClass::TWONODE:
                //std::cout << "HERE" << std::endl;
                debuglog("\tParent is a two node.");

                upper->node_class = NodeClass::THREENODE;
                lower->node_class = NodeClass::TWONODE;

                // lower is left child of parent 
                if(upper->child0 == lower) {
                    debuglog("\t\tLower node was left child of parent");

                    //std::cout << "left child" << std::endl;

                    newnode->child0 = lower->child2;
                    newnode->child1 = lower->child3;
                    newnode->pivot0 = lower->pivot2;

                    upper->pivot1 = upper->pivot0;
                    upper->pivot0 = lower->pivot1;
                    
                    upper->child2 = upper->child1;
                    upper->child1 = newnode;

                    if(newnode->child0 != nullptr) newnode->child0->parent = newnode;
                    if(newnode->child1 != nullptr) newnode->child1->parent = newnode;
                }
                // lower is right child of parent
                else {
                    debuglog("\t\tLower node was right child of parent");
                    //std::cout << "right child" << std::endl;

                    newnode->child0 = lower->child2;
                    newnode->child1 = lower->child3;
                    newnode->pivot0 = lower->pivot2;

                    upper->pivot1 = lower->pivot1;         

                    upper->child1 = lower;
                    upper->child2 = newnode;
                    lower->parent = upper;

                    if(newnode->child0 != nullptr) newnode->child0->parent = newnode;
                    if(newnode->child1 != nullptr) newnode->child1->parent = newnode;
                }

                break;
            case NodeClass::THREENODE:
                //std::cout << "three" << std::endl;
                debuglog("\tParent is a three node.");

                upper->node_class = NodeClass::FOURNODE;
                lower->node_class = NodeClass::TWONODE;

                // lower is left child of parent
                if(upper->child0 == lower) {
                    debuglog("\t\tLower node was left child of parent");

                    newnode->child0 = lower->child2;
                    newnode->child1 = lower->child3;

                    upper->pivot2 = upper->pivot1;
                    upper->pivot1 = upper->pivot0;
                    upper->pivot0 = lower->pivot1;

                    newnode->pivot0 = lower->pivot2;

                    upper->child3 = upper->child2;
                    upper->child2 = upper->child1;
                    upper->child1 = newnode;

                    if(newnode->child0 != nullptr) newnode->child0->parent = newnode;
                    if(newnode->child1 != nullptr) newnode->child1->parent = newnode;
                    if(newnode->child2 != nullptr) newnode->child2->parent = newnode;
                }

                // lower is middle child of parent
                else if(upper->child1 == lower) {
                    debuglog("\t\tLower node was middle child of parent");

                    newnode->child0 = lower->child2;
                    newnode->child1 = lower->child3;

                    upper->pivot2 = upper->pivot1;
                    upper->pivot1 = lower->pivot1;

                    newnode->pivot0 = lower->pivot2;

                    upper->child3 = upper->child2;
                    upper->child2 = newnode;

                    if(newnode->child0 != nullptr) newnode->child0->parent = newnode;
                    if(newnode->child1 != nullptr) newnode->child1->parent = newnode;
                    if(newnode->child2 != nullptr) newnode->child2->parent = newnode;
                }

                // lower is right child of parent
                else {
                    debuglog("\t\tLower node was right child of parent");

                    newnode->child0 = lower->child2;
                    newnode->child1 = lower->child3;
                    
                    upper->pivot2 = lower->pivot1;

                    newnode->pivot0 = lower->pivot2;

                    upper->child3 = newnode;

                    if(newnode->child0 != nullptr) newnode->child0->parent = newnode;
                    if(newnode->child1 != nullptr) newnode->child1->parent = newnode;
                    if(newnode->child2 != nullptr) newnode->child2->parent = newnode;
                }

                break;
                
            default: 
                debuglog("Something is ROYALLY fucked up. Time to take shots and change your major!");

                break;
        }

    }
}

template<typename K, typename V>
void Two4Tree<K, V>::setranks(TwoThreeFourNode<K, V>* node, int rank){
    node->rank = rank;

    if(node->internal) {
        switch(node->node_class) {
            case NodeClass::TWONODE:
                setranks(node->child0, rank + 1);
                setranks(node->child1, rank + 1);

                break;
            case NodeClass::THREENODE:
                setranks(node->child0, rank + 1);
                setranks(node->child1, rank + 1);
                setranks(node->child2, rank + 1);

                break;
            case NodeClass::FOURNODE:
                setranks(node->child0, rank + 1);
                setranks(node->child1, rank + 1);
                setranks(node->child2, rank + 1);
                setranks(node->child3, rank + 1);

                break;
            default: break;
        }
    }

    return;
}

template<typename K, typename V>
int Two4Tree<K, V>::recursiverank(TwoThreeFourNode<K, V>* node, K key){
    // check if key is in current node
    switch(node->node_class) {
        case NodeClass::TWONODE:
            if(node->pivot0->key == key) return node->rank;

            if(node->internal) {
                if(key < node->pivot0->key) return recursiverank(node->child0, key);
                else return recursiverank(node->child1, key);
            }

            else {
                debuglog("Rank called for node not in tree");
                return 0;
            }

            break;

        case NodeClass::THREENODE:
            if(node->pivot0->key == key) return node->rank;
            else if(node->pivot1->key == key) return node->rank;

            if(node->internal) {
                if(key < node->pivot0->key) return recursiverank(node->child0, key);
                else if(key >= node->pivot0->key && key < node->pivot1->key) return recursiverank(node->child1, key);
                else return recursiverank(node->child2, key);
            }

            else {
                debuglog("Rank called for node not in tree");
                return 0;
            }

            break;

        case NodeClass::FOURNODE:
            if(node->pivot0->key == key) return node->rank;
            else if(node->pivot1->key == key) return node->rank;
            else if(node->pivot2->key == key) return node->rank;

            if(node->internal) {
                if(key < node->pivot0->key) return recursiverank(node->child0, key);
                else if(key >= node->pivot0->key && key < node->pivot1->key) return recursiverank(node->child1, key);
                else if(key >= node->pivot1->key && key < node->pivot2->key) return recursiverank(node->child2, key);
                else return recursiverank(node->child3, key);
            }

            else {
                debuglog("Rank called for node not in tree");
                return 0;
            }

            break;

        default: break;
    }

    // unreachable
    return 0;
}

template<typename K, typename V>
void Two4Tree<K, V>::recursivedelete(TwoThreeFourNode<K, V>* node) {

    if(node) {
        switch(node->node_class) {
            case NodeClass::TWONODE:
                recursivedelete(node->child0);
                recursivedelete(node->child1);

                delete node->pivot0;

                break;
            case NodeClass::THREENODE:
                recursivedelete(node->child0);
                recursivedelete(node->child1);
                recursivedelete(node->child2);

                delete node->pivot0;
                delete node->pivot1;

                break;
            case NodeClass::FOURNODE:
                recursivedelete(node->child0);
                recursivedelete(node->child1);
                recursivedelete(node->child2);
                recursivedelete(node->child3);

                delete node->pivot0;
                delete node->pivot1;
                delete node->pivot2;
            
            default: break;
        }

        delete node;
    }
}

template<typename K, typename V>
void Two4Tree<K, V>::recursivepreorder(TwoThreeFourNode<K, V>* node) {
    // ROOT LEFT RIGHT
    if(node->internal) {
        switch(node->node_class) {
            case NodeClass::TWONODE:
                _stream << node->pivot0->key<< " ";

                recursivepreorder(node->child0);
                recursivepreorder(node->child1);

                break;
            case NodeClass::THREENODE:
                _stream << node->pivot0->key << " ";
                _stream << node->pivot1->key << " ";

                recursivepreorder(node->child0);
                recursivepreorder(node->child1);
                recursivepreorder(node->child2);

                break;
            case NodeClass::FOURNODE:
                _stream << node->pivot0->key << " ";
                _stream << node->pivot1->key << " ";
                _stream << node->pivot2->key << " ";

                recursivepreorder(node->child0);
                recursivepreorder(node->child1);
                recursivepreorder(node->child2);
                recursivepreorder(node->child3);

                break;
            default: break;
        }
    }
    else {
        switch(node->node_class) {
            case NodeClass::TWONODE:
                _stream << node->pivot0->key << " ";

                break;
            case NodeClass::THREENODE:
                _stream << node->pivot0->key << " ";
                _stream << node->pivot1->key << " ";

                break;
            case NodeClass::FOURNODE:
                _stream << node->pivot0->key << " ";
                _stream << node->pivot1->key << " ";
                _stream << node->pivot2->key << " ";
            
                break;
            default: break;
        }

    }
}

template<typename K, typename V>
void Two4Tree<K, V>::recursiveinorder(TwoThreeFourNode<K, V>* node) {
    // LEFT ROOT RIGHT
    if(node->internal) {
        switch(node->node_class) {
            case NodeClass::TWONODE:
                //_stream << std::endl << "Node is 2 node" << std::endl;
                
                recursiveinorder(node->child0);

                _stream << node->pivot0->key << " ";

                recursiveinorder(node->child1);

                break;
            case NodeClass::THREENODE:
                //_stream << std::endl << "Node is 3 node" << std::endl;

                recursiveinorder(node->child0);

                _stream << node->pivot0->key << " ";

                recursiveinorder(node->child1);

                _stream << node->pivot1->key << " ";

                recursiveinorder(node->child2);

                break;
            case NodeClass::FOURNODE:
                //_stream << std::endl << "Node is 4 node" << std::endl;

                recursiveinorder(node->child0);

                _stream << node->pivot0->key << " ";

                recursiveinorder(node->child1);

                _stream << node->pivot1->key<< " ";

                recursiveinorder(node->child2);

                _stream << node->pivot2->key<< " ";

                recursiveinorder(node->child3);
                
                break;
            default: break;
        }
    }
    else {
        switch(node->node_class) {
            case NodeClass::TWONODE:
                _stream << node->pivot0->key << " ";

                break;
            case NodeClass::THREENODE:
                _stream << node->pivot0->key << " ";
                _stream << node->pivot1->key << " ";

                break;
            case NodeClass::FOURNODE:
                _stream << node->pivot0->key << " ";
                _stream << node->pivot1->key << " ";
                _stream << node->pivot2->key << " ";
            
                break;
            default: break;
        }
    }
}

template<typename K, typename V>
void Two4Tree<K, V>::recursivepostorder(TwoThreeFourNode<K, V>* node) {
    // LEFT RIGHT ROOT
    if(node->internal) {
        switch(node->node_class) {
            case NodeClass::TWONODE:
                recursivepostorder(node->child0);
                recursivepostorder(node->child1);

                _stream << node->pivot0->key << " ";

                break;
            case NodeClass::THREENODE:
                recursivepostorder(node->child0);
                recursivepostorder(node->child1);

                _stream << node->pivot0->key << " ";

                recursivepostorder(node->child2);

                _stream << node->pivot1->key << " ";

                break;
            case NodeClass::FOURNODE:
                recursivepostorder(node->child0);
                recursivepostorder(node->child1);

                _stream << node->pivot0->key << " ";

                recursivepostorder(node->child2);

                _stream << node->pivot1->key << " ";

                recursivepostorder(node->child3);

                _stream << node->pivot2->key << " ";
                
                break;
            default: break;
        }
    }
    else {
        switch(node->node_class) {
            case NodeClass::TWONODE:
                _stream << node->pivot0->key << " ";

                break;
            case NodeClass::THREENODE:
                _stream << node->pivot0->key << " ";
                _stream << node->pivot1->key << " ";

                break;
            case NodeClass::FOURNODE:
                _stream << node->pivot0->key << " ";
                _stream << node->pivot1->key << " ";
                _stream << node->pivot2->key << " ";
            
                break;
            default: break;
        }

    }
}

template<typename K, typename V>
void Two4Tree<K, V>::debuglog(std::string s) {
    #ifdef _DEBUG_
        _stream << s << std::endl; 
    #endif
}

template class Two4Tree<int, int>;
template class Two4Tree<int, float>;
template class Two4Tree<int, double>;
template class Two4Tree<int, long>;

template class Two4Tree<short, short>;
template class Two4Tree<long, long>;
template class Two4Tree<long long, long long>;

template class Two4Tree<float, float>;
template class Two4Tree<double, double>;
template class Two4Tree<long double, long double>;

//template class Two4Tree<std::string>;
template class Two4Tree<char, char>;