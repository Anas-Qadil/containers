//123
	enum Color {RED, BLACK};

	template <typename Key, typename Value>
	struct Node {
		ft::pair<const Key, Value> data;
		Color color;
		Node *left, *right, *parent;

		// constructor for a new node
		Node(const ft::pair<const Key, Value> &data) : data(data) {
			color = RED;
			left = right = parent = NULL;
		}
	};

	template <typename Key, typename Value>
	class RBTree {
		private:
			Node<Key, Value> *root;

			// left rotation helper function
			void rotateLeft(Node<Key, Value> *&root, Node<Key, Value> *&pt);
			// right rotation helper function
			void rotateRight(Node<Key, Value> *&root, Node<Key, Value> *&pt);
			// fix any violations of the Red-Black Tree properties
			void fixViolation(Node<Key, Value> *&root, Node<Key, Value> *&pt);
			// insert a new node to the tree (in a BST fashion)
			Node<Key, Value>* insertBST(Node<Key, Value> *root, Node<Key, Value> *pt);
			// search for a node with a given key
			Node<Key, Value>* searchBST(Node<Key, Value> *root, const Key &key) const;
			// find the minimum key in the tree
			Node<Key, Value>* minimum(Node<Key, Value> *root);
			// find the maximum key in the tree
			Node<Key, Value>* maximum(Node<Key, Value> *root);
			// find the next largest key (successor)
			Node<Key, Value>* successor(Node<Key, Value> *root);
			// find the next smallest key (predecessor)
			Node<Key, Value>* predecessor(Node<Key, Value> *root);
			// helper function for in-order traversal
			void inorderHelper(Node<Key, Value> *root);
			// helper function for clearing the tree
			void clearHelper(Node<Key, Value> *root);
			// fix the double black violation
			void fixDoubleBlack(Node<Key, Value> *&root, Node<Key, Value> *&x, Node<Key, Value> *&parent);
			void transplant(Node<Key, Value> *&root, Node<Key, Value> *u, Node<Key, Value> *v);
	};