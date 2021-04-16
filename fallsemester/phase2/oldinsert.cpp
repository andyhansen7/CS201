/*// create a new node for the value
    Node<K, V>* newnode = new Node<K, V>();
    newnode->key = key;
    newnode->value = value;

    // increment size
    _size++;

    // Check if tree is empty
    if (_root == nullptr) {
        _root = new TwoThreeFourNode<K, V>();
        _root->internal = false;
        _root->node_class = NodeClass::TWONODE;
        _root->pivot0 = newnode;

        debuglog("\tInsert operation completed sucessfully with new node as root.");
        return;
    }

    TwoThreeFourNode<K, V>* pointer = _root;
    TwoThreeFourNode<K, V>* parent = pointer;

    debuglog("Starting loop...");

    while(pointer != nullptr) {
        debuglog("Loop top.");

        // check for duplicate keys already in tree
        if(pointer->contains(key)) {
            debuglog("Key already in tree!");
            return;
        }

        // if current node is a 4-node, split
        if(pointer->nodetype() == NodeClass::FOURNODE) {
            debuglog("Splitting 4-node");

            // check if parent is root first
            if(parent == _root) {
                debuglog("Splitting root and rerunning");

                TwoThreeFourNode<K, V>* newroot = new TwoThreeFourNode<K, V>();
                TwoThreeFourNode<K, V>* left = new TwoThreeFourNode<K, V>();
                TwoThreeFourNode<K, V>* right = new TwoThreeFourNode<K, V>();

                left->pivot0 = pointer->pivot0;
                left->child0 = pointer->child0;
                left->child1 = pointer->child1;

                right->pivot0 = pointer->pivot2;
                right->child0 = pointer->child2;
                right->child1 = pointer->child3;

                newroot->pivot0 = pointer->pivot2;
                newroot->child0 = left;
                newroot->child1 = right;

                left->node_class = NodeClass::TWONODE;
                right->node_class = NodeClass::TWONODE;
                newroot->node_class = NodeClass::TWONODE;

                _root = newroot;

                insert(key, value);
                return;
            }

            // first case: parent is a 2-node
            if(parent->nodetype() == NodeClass::TWONODE) {
                debuglog("Parent was a 2-node");

                if(parent->pivot0->key < pointer->pivot1->key) {
                    parent->pivot1 = pointer->pivot1;

                    // construct new child nodes
                    TwoThreeFourNode<K, V>* left = new TwoThreeFourNode<K, V>();
                    TwoThreeFourNode<K, V>* right = new TwoThreeFourNode<K, V>();

                    left->pivot0 = pointer->pivot0;
                    left->child0 = pointer->child0;
                    left->child1 = pointer->child1;

                    right->pivot0 = pointer->pivot2;
                    right->child0 = pointer->child2;
                    right->child1 = pointer->child3;

                    // complete split
                    parent->child1 = left;
                    parent->child2 = right;
                }

                else {

                    // construct new child nodes
                    TwoThreeFourNode<K, V>* left = new TwoThreeFourNode<K, V>();
                    TwoThreeFourNode<K, V>* right = new TwoThreeFourNode<K, V>();

                    left->pivot0 = pointer->pivot0;
                    left->child0 = pointer->child0;
                    left->child1 = pointer->child1;

                    right->pivot0 = pointer->pivot2;
                    right->child0 = pointer->child2;
                    right->child1 = pointer->child3;

                    left->node_class = NodeClass::TWONODE;
                    right->node_class = NodeClass::TWONODE;

                    parent->pivot1 = parent->pivot0;
                    parent->child2 = parent->child1;
                    parent->pivot0 = pointer->pivot1;

                    parent->child0 = left;
                    parent->child1 = right;
                }

                // memory cleaning
                delete pointer;

                // find where node is to be inserted
                if(key < parent->pivot0->key) pointer = parent->child0;
                else if(key < parent->pivot1->key) pointer = parent->child1;
                else if(key > parent->pivot1->key) pointer = parent->child2;
                else return; // invalid
            }

            // second case - parent is a 3-node
            else if(parent->nodetype() == NodeClass::THREENODE) {
                debuglog("Parent was a 3-node");

                if(parent->pivot1->key < pointer->pivot1->key) {
                    // construct child nodes
                    TwoThreeFourNode<K, V>* left = new TwoThreeFourNode<K, V>();
                    TwoThreeFourNode<K, V>* right = new TwoThreeFourNode<K, V>();

                    left->pivot0 = pointer->pivot0;
                    left->child0 = pointer->child0;
                    left->child1 = pointer->child1;

                    right->pivot0 = pointer->pivot2;
                    right->child0 = pointer->child2;
                    right->child1 = pointer->child3;

                    left->node_class = NodeClass::TWONODE;
                    right->node_class = NodeClass::TWONODE;

                    parent->pivot2 = pointer->pivot1;

                    parent->child2 = left;
                    parent->child3 = right;
                }

                else if(parent->pivot1->key < pointer->pivot1->key) {
                    // construct child nodes
                    TwoThreeFourNode<K, V>* left = new TwoThreeFourNode<K, V>();
                    TwoThreeFourNode<K, V>* right = new TwoThreeFourNode<K, V>();

                    left->pivot0 = pointer->pivot0;
                    left->child0 = pointer->child0;
                    left->child1 = pointer->child1;

                    right->pivot0 = pointer->pivot2;
                    right->child0 = pointer->child2;
                    right->child1 = pointer->child3;

                    left->node_class = NodeClass::TWONODE;
                    right->node_class = NodeClass::TWONODE;

                    parent->pivot2 = parent->pivot1;
                    parent->child2 = parent->child1;
                    parent->pivot1 = pointer->pivot1;

                    parent->child1 = left;
                    parent->child2 = right;
                }

                else {
                    TwoThreeFourNode<K, V>* left = new TwoThreeFourNode<K, V>();
                    TwoThreeFourNode<K, V>* right = new TwoThreeFourNode<K, V>();

                    left->pivot0 = pointer->pivot0;
                    left->child0 = pointer->child0;
                    left->child1 = pointer->child1;

                    right->pivot0 = pointer->pivot2;
                    right->child0 = pointer->child2;
                    right->child1 = pointer->child3;

                    left->node_class = NodeClass::TWONODE;
                    left->node_class = NodeClass::TWONODE;

                    parent->pivot2 = parent->pivot1;
                    parent->child3 = parent->child1;

                    parent->pivot1 = parent->pivot0;
                    parent->child2 = parent->child1;
                    parent->pivot0 = pointer->pivot1;

                    parent->child0 = left;
                    parent->child1 = right;
                }

                // memory cleaning
                delete pointer;

                if (key < parent->pivot0->key) pointer = parent->child0;
                else if (key < parent->pivot1->key) pointer = parent->child1;
                else if (key < parent->pivot2->key) pointer = parent->child2;
                else if (key > parent->pivot2->key) pointer = parent->child3;
                else return;
            }

            // third case - parent is a 2-node
            else {
                debuglog("Parent was a 2-node");

                // construct child nodes
                TwoThreeFourNode<K, V>* newroot = new TwoThreeFourNode<K, V>();
                TwoThreeFourNode<K, V>* left = new TwoThreeFourNode<K, V>();
                TwoThreeFourNode<K, V>* right = new TwoThreeFourNode<K, V>();

                newroot->pivot0 = pointer->pivot1;
                newroot->child0 = left;
                newroot->child1 = right;

                left->pivot0 = pointer->pivot0;
                left->child0 = pointer->child0;
                left->child1 = pointer->child1;

                right->pivot0 = pointer->pivot2;
                right->child0 = pointer->child2;
                right->child1 = pointer->child3;

                newroot->node_class = NodeClass::TWONODE;
                left->node_class = NodeClass::TWONODE;
                right->node_class = NodeClass::TWONODE;

                _root = newroot;

                // free memory
                delete pointer;

                parent = _root;
                if(key < _root->pivot0->key) pointer = _root->child0;
                else if(key > _root->pivot1->key) pointer = _root->child1;
                else return;
            }
        }

        // if node is a leaf node, need to insert into it
        if(!pointer->internal) {
            debuglog("Inserting into leaf node");
            
            // first case - node is a 2-node
            if(pointer->nodetype() == NodeClass::TWONODE) {
                debuglog("Leaf node was a 2-node");

                if(key > pointer->pivot0->key) {
                    pointer->pivot1 = newnode;

                    return;
                }

                else if(key < pointer->pivot0->key) {
                    pointer->pivot1 = pointer->pivot0;
                    pointer->pivot0 = newnode;

                    return;
                }
            }

            // second case - node is a 3-node
            else if(pointer->nodetype() == NodeClass::THREENODE) {
                debuglog("Leaf node was a 3-node");

                if(key > pointer->pivot1->key) {
                    pointer->pivot2 = newnode;

                    return;
                }

                else if(key > pointer->pivot0->key) {
                    pointer->pivot2 = pointer->pivot1;
                    pointer->pivot1 = newnode;

                    return;
                }

                else if(key < pointer->pivot0->key) {
                    pointer->pivot2 = pointer->pivot1;
                    pointer->pivot1 = pointer->pivot0;
                    pointer->pivot0 = newnode;

                    return;
                }
            }
        }

        // if not a leaf node, continue to next loop
        else {
            debuglog("Node was an internal node. Continuing to next loop");
            parent = pointer;

            // pointer is a 2-node
            if(pointer->nodetype() == NodeClass::TWONODE) {
                if(key < pointer->pivot0->key) pointer = pointer->child0;

                else pointer = pointer->child1;
            }

            // pointer is a 3-node
            else if(pointer->nodetype() == NodeClass::THREENODE) {
                if(key < pointer->pivot0->key) pointer = pointer->child0;

                else if(key < pointer->pivot1->key) pointer = pointer->child1;

                else pointer = pointer->child2;
            }
        }
    }*/