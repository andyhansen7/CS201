/* ==========================
 * 2-3-4 Tree
 * CS201-001 Fall 2020
 * Developed by Andrew Hansen
 * arhansen@crimson.ua.edu
 * ===========================
 */

#ifndef _Two4Tree_H_
#define _Two4Tree_H_

#include <iostream>
#include <string>

template<typename K, typename V>
struct Node {
    K key;
    V value;
};

enum class NodeClass {
    TWONODE = 0,
    THREENODE,
    FOURNODE
};

template<typename K, typename V>
class TwoThreeFourNode {
    public: 
        NodeClass node_class;
        int rank = 0;
        bool internal = true;

        Node<K, V>* pivot0 = nullptr;
        Node<K, V>* pivot1 = nullptr;
        Node<K, V>* pivot2 = nullptr;

        TwoThreeFourNode<K, V>* child0 = nullptr;
        TwoThreeFourNode<K, V>* child1 = nullptr;
        TwoThreeFourNode<K, V>* child2 = nullptr;
        TwoThreeFourNode<K, V>* child3 = nullptr;

        TwoThreeFourNode<K, V>* parent = nullptr;

        bool full() {
            return (pivot0 != nullptr && pivot1 != nullptr && pivot2 != nullptr);
        }

        NodeClass nodetype() {
            int pivots = 0;

            if(pivot2 != nullptr) pivots++;
            if(pivot1 != nullptr) pivots++;

            switch(pivots) {
                case 0: 
                    node_class = NodeClass::TWONODE;
                    return NodeClass::TWONODE;
                case 1: 
                    node_class = NodeClass::THREENODE;
                    return NodeClass::THREENODE;
                case 2: 
                    node_class = NodeClass::FOURNODE;
                    return NodeClass::FOURNODE;
                default: 
                    node_class = NodeClass::TWONODE;
                    return NodeClass::TWONODE;
            }
        }

        bool contains(K key) {
            return ( (pivot0 != nullptr && pivot0->key == key) || (pivot1 != nullptr && pivot1->key == key) || (pivot2 != nullptr && pivot2->key == key) );
        }

        void clear() {
            if(child0 != nullptr) child0->clear();
            if(child1 != nullptr) child1->clear();
            if(child2 != nullptr) child2->clear();
            if(child3 != nullptr) child3->clear();

            if(pivot0 != nullptr) delete pivot0;
            if(pivot1 != nullptr) delete pivot1;
            if(pivot2 != nullptr) delete pivot2;

            pivot0 = nullptr;
            pivot1 = nullptr;
            pivot2 = nullptr;

            child0 = nullptr;
            child1 = nullptr;
            child2 = nullptr;
            child3 = nullptr;
        }
};

template<typename K, typename V>
class Two4Tree {
    public:
        /** Default Constructor with an empty tree.
         * O(1)
         * @param none
         */
        Two4Tree();

        /** Constructor for tree to be built using existing arrays of keys and values.
         * O(s lg s)
         * 
         * @param keys: array of keys for existing tree, of type K
         * @param values: array of values for existing tree, of type V
         * @param s: size of arrays 'keys' and 'values'
         */ 
        Two4Tree(K keys[], V values[], int s);

        /** Copy Constructor for the class
         * 
         * @param base: The tree to copy
         */
        Two4Tree(Two4Tree& base);

        /** Copy assignment operator for the class
         * 
         * @param base: The tree to copy
         */
        Two4Tree& operator=(Two4Tree& c); 

        /** Destructor for the class.
         * O(n)
         * 
         * @param none
         */
        ~Two4Tree(); 

        /** Traditional search. 
         * O(lg n)
         * 
         * @param key: the key to search for
         * @return Returns a pointer to the valuetype stored with the key. If the key is not stored in the tree then the function returns NULL.
         */
        V* search(K key);

        /** Inserts the node with key k and value v into the tree.
         * O(lg n)
         * 
         * @param key: the key of the node to be inserted
         * @param value: the value of the node to be inserted
         */ 
        void insert(K key, V value);

        /** Removes the node with key k.
         * O(lg n)
         * 
         * @param key: the key of the node to be removed from the tree
         * @return Returns 1, or 0 if the key k is not in the tree
         */ 
        int remove(K key);

        /** Returns the rank of the key k in the tree.
         * O(lg n)
         * 
         * @param key: the key to determine the rank of
         * @return The rank of the key, or 0 if the key is not found
         */ 
        int rank(K key);

        /** Order Statistics.
         * O(lg n)
         * 
         * @param pos: the position of the key to return the key of
         * @return The key of the node in position pos
         */ 
        K select(int pos);

        /** Returns the key after k in the tree. 
         * O(lg n)
         * 
         * @param key: the key to find the sucessor to
         * @return The key of the node after the specified node
         */ 
        K successor(K key);

        /** Returns the key before k in the tree. 
         * O(lg n)
         * 
         * @param key: the key to find the sucessor to
         * @return The key of the node before the specified node
         */
        K predecessor(K key);

        /** Returns the number of nodes in the tree.
         * O(1)
         * 
         * @param none
         * @return The number of nodes in the tree
         */ 
        int size();

        /** Prints the keys of the tree in a preorder traversal.
         * O(n)
         * @param none
         */ 
        void preorder();

        /** Prints the keys of the tree in an inorder traversal.
         * O(n)
         * @param none
         */ 
        void inorder();

        /** Prints the keys of the tree in a postorder traversal.
         * O(n)
         * @param none
         */ 
        void postorder();

        /** Enables debugging output using the default output stream
         * 
         * @param none
         */ 
        void debug();

        /** Helper function to build array from the values in a tree.
         * 
         * @param node: The root node of the tree
         * @param array: pointer to array to store values in.
         */ 
        void buildarray(TwoThreeFourNode<K,V>* node, Node<K, V>** array);

        /** Returns the root of the tree for use in copy constructor
         * 
         * @param none
         */
        TwoThreeFourNode<K, V>* getroot();

    private:
        /** Recursive search function, returns the value of a specified key
         * 
         * @param node: The current node being searched
         * @param key: The key to search for
         */
        Node<K,V>* recursivesearch(TwoThreeFourNode<K, V>* node, K key);

        /** Recursive insert function, called by insert function
         * 
         * @param newnode: The node to be inserted
         * @param parent: The node to be inserted into
         */
        void recursiveinsert(Node<K, V>* newnode, TwoThreeFourNode<K, V>* parent);

        /** Function to sift a 4 node up to the parent
         * 
         * @param lower: the node that needs to be sifted up
         * @param upper: the node that will be sifted to
         */ 
        void siftup(TwoThreeFourNode<K, V>* lower, TwoThreeFourNode<K, V>* upper);

        /** Function to set the rank of all nodes in tree
         * 
         * @param node: the current node
         * @param rank: the rank of the current node
         */ 
        void setranks(TwoThreeFourNode<K, V>* node, int rank);

        /** Function to get the rank of a node with key
         * 
         * @param node: the current node
         * @param key: the key to get the rank of
         */ 
        int recursiverank(TwoThreeFourNode<K, V>* node, K key);

        /** Recursive function to delete all children of a node.
         * 
         * @param node: The node to be freed
         */ 
        void recursivedelete(TwoThreeFourNode<K, V>* node);

        /** Recursive function to print tree in preorder transversal
         * 
         * @param node: The root node of the subtree
         */ 

        void recursivepreorder(TwoThreeFourNode<K, V>* node);

        /** Recursive function to print tree in inorder transversal
         * 
         * @param node: The root node of the subtree
         */ 

        void recursiveinorder(TwoThreeFourNode<K, V>* node);

        /** Recursive function to print tree in postorder transversal
         * 
         * @param node: The root node of the subtree
         */ 

        void recursivepostorder(TwoThreeFourNode<K, V>* node);

        /** Helper function to display debugging info, if debugging is enabled.
         * O(1)
         * 
         * @param s: The message to be logged
         */ 
        void debuglog(std::string s);

        // pointer to root of tree
        TwoThreeFourNode<K, V>* _root;

        // stores size of tree
        int _size;
        int tempsize = 0;

        // default stream for output / debug
        std::ostream& _stream = std::cout;
};

#endif // !_Two4Tree_H_