#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cassert>

enum Color {RED, BLACK};

template <typename Key, typename Value>
struct Node {
	std::pair<const Key, Value> data;
	Color color;
	Node *left, *right, *parent;

	// constructor for a new node
	Node(const std::pair<const Key, Value> &data) : data(data) {
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

public:
	// constructor
	RBTree() : root(NULL) {}
	// insert a new node with a given key-value pair
	void insert(const std::pair<const Key, Value> &data);
	// access the value of a node with a given key
	Value& operator[](const Key &key);
	// remove a node with a given key
	void remove(const Key &key);
	// remove all nodes from the tree
	void clear();
	// check if the tree contains a node with a given key
	bool contains(const Key &key) const;
	// access the value of a node with a given key
	Value& at(const Key &key);
	// access the value of a node with a given
	// key (const version) // check this later
	const Value& at(const Key &key) const;
	// in-order traversal of the tree
	void inorder();
};

template <typename Key, typename Value>
void RBTree<Key, Value>::rotateLeft(Node<Key, Value> *&root, Node<Key, Value> *&pt) {
    Node<Key, Value> *pt_right = pt->right;
    pt->right = pt_right->left;
    if (pt->right != nullptr) {
			pt->right->parent = pt;
    }
    pt_right->parent = pt->parent;
    if (pt->parent == nullptr) {
			root = pt_right;
    } else if (pt == pt->parent->left) {
			pt->parent->left = pt_right;
    } else {
			pt->parent->right = pt_right;
    }
    pt_right->left = pt;
    pt->parent = pt_right;
}


template <typename Key, typename Value>
void RBTree<Key, Value>::rotateRight(Node<Key, Value> *&root, Node<Key, Value> *&pt) {
	Node<Key, Value> *pt_left = pt->left;

	pt->left = pt_left->right;

	if (pt->left != NULL)  
		pt->left->parent = pt;

	pt_left->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_left;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_left;

	else
		pt->parent->right = pt_left;

	pt_left->right = pt;
	pt->parent = pt_left;
}

template <typename Key, typename Value>
void RBTree<Key, Value>::fixViolation(Node<Key, Value> *&root, Node<Key, Value> *&pt) {
	Node<Key, Value> *parent_pt = NULL;
	Node<Key, Value> *grand_parent_pt = NULL;
	while ((pt != root) && (pt->color != BLACK) &&
		(pt->parent->color == RED)) {

		parent_pt = pt->parent;
		grand_parent_pt = pt->parent->parent;

		if (parent_pt == grand_parent_pt->left) {
			Node<Key, Value> *uncle_pt = grand_parent_pt->right;

			if (uncle_pt != NULL && uncle_pt->color == RED) {
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			} else {
				if (pt == parent_pt->right) {
					rotateLeft(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}
				rotateRight(root, grand_parent_pt);
				std::swap(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
			}
		} else {
			Node<Key, Value> *uncle_pt = grand_parent_pt->left;

			if ((uncle_pt != NULL) && (uncle_pt->color == RED)) {
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			} else {
				if (pt == parent_pt->left) {
					rotateRight(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}
				rotateLeft(root, grand_parent_pt);
				std::swap(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
			}
		}
	}
	root->color = BLACK;
}

template <typename Key, typename Value>
Node<Key, Value>* RBTree<Key, Value>::insertBST(Node<Key, Value> *root, Node<Key, Value> *pt) {
	if (root == NULL) {
		// When the tree is empty
		pt->color = BLACK;
		return pt;
	}

	if (pt->data.first < root->data.first) {
		root->left = insertBST(root->left, pt);
		root->left->parent = root;
	} else if (pt->data.first > root->data.first) {
		root->right = insertBST(root->right, pt);
		root->right->parent = root;
	} else {
		// duplicate keys not allowed
		return root;
	}
	// fix violations of Red-Black Tree properties
	fixViolation(root, pt);
	return root;
}

template <typename Key, typename Value>
Node<Key, Value>* RBTree<Key, Value>::minimum(Node<Key, Value> *root) {
	if (root == NULL) {
		return NULL;
	}
	while (root->left != NULL) {
		root = root->left;
	}
	return root;
}

template <typename Key, typename Value>
Node<Key, Value>* RBTree<Key, Value>::maximum(Node<Key, Value> *root) {
	// if the root is null, return null
	if (!root) return NULL;

	// traverse to the right child of the root
	// while there is a right child
	while (root->right != NULL) {
			root = root->right;
	}

	// return the node with the maximum key
	return root;
}


template <typename Key, typename Value>
void RBTree<Key, Value>::insert(const std::pair<const Key, Value> &data) {
	Node<Key, Value> *pt = new Node<Key, Value>(data);
	root = insertBST(root, pt);

	fixViolation(root, pt);
}


template <typename Key, typename Value>
Node<Key, Value>* RBTree<Key, Value>::searchBST(Node<Key, Value> *root, const Key &key) const {
	if (root == NULL || root->data.first == key)
		return root;

	if (root->data.first > key)
		return searchBST(root->left, key);

	return searchBST(root->right, key);
}

template <typename Key, typename Value>
Value& RBTree<Key, Value>::at(const Key &key){
	Node<Key, Value> *result = searchBST(root, key);
	if (result == NULL) {
		throw std::out_of_range("Key notfound");
	}
	return result->data.second;
}

template <typename Key, typename Value>
const Value& RBTree<Key, Value>::at(const Key &key) const {
	Node<Key, Value> *result = searchBST(root, key);
	if (result == NULL) {
		throw std::out_of_range("Key not found");
	}
	return result->data.second;
}

template <typename Key, typename Value>
bool RBTree<Key, Value>::contains(const Key &key) const {
	return searchBST(root, key) != NULL;
}

template <typename Key, typename Value>
Value& RBTree<Key, Value>::operator[](const Key &key) {
	Node<Key, Value> *result = searchBST(root, key);
	if (result == NULL) {
		insert(std::make_pair(key, Value()));
		result = searchBST(root, key);
	}
	return result->data.second;
}

template <typename Key, typename Value>
void RBTree<Key, Value>::clear() {
	clearHelper(root);
	root = nullptr;
}

template <typename Key, typename Value>
void RBTree<Key, Value>::clearHelper(Node<Key, Value> *node) {
	if (node == nullptr) return;
	clearHelper(node->left);
	clearHelper(node->right);
	delete node;
}

template <class Key, class Value>
void RBTree<Key, Value>::inorder() {
	inorderHelper(root);
}

template <typename Key, typename Value>
void RBTree<Key, Value>::inorderHelper(Node<Key, Value> *root) {
    if (root != NULL) {
			inorderHelper(root->left);
			std::cout << "key: " << root->data.first << " value: " << root->data.second << std::endl;
			inorderHelper(root->right);
    }
}

template <typename Key, typename Value>
void RBTree<Key, Value>::fixDoubleBlack(Node<Key, Value> *&root, Node<Key, Value> *&x, Node<Key, Value> *&parent) {
    if (x == root) {
			// if x is the root, it is no longer double black
			return;
    }

    Node<Key, Value> *sibling = (parent->left == x) ? parent->right : parent->left;

    if (sibling == NULL) {
			// if x has no sibling, it is no longer double black
			return;
    }

    if (sibling->color == RED) {
			// if the sibling is red, we perform a rotation
			parent->color = RED;
			sibling->color = BLACK;
			if (parent->left == x) {
				rotateRight(root, parent);
			} else {
				rotateLeft(root, parent);
			}
			fixDoubleBlack(root, x, parent);
    } else {
			// if the sibling is black, we check its children
			if (sibling->left != NULL && sibling->left->color == RED) {
				if (sibling->right != NULL && sibling->right->color == RED) {
					// if both children of the sibling are red
					sibling->color = RED;
					sibling->left->color = BLACK;
					sibling->right->color = BLACK;
					fixDoubleBlack(root, parent, parent->parent);
				} else {
					if (parent->left == x) {
						// if the left child of the sibling is red, we perform a rotation
						sibling->left->color = BLACK;
						sibling->color = RED;
						rotateLeft(root, sibling);
						fixDoubleBlack(root, x, parent);
					} else {
						// if the right child of the sibling is red, we perform a rotation
						sibling->right->color = BLACK;
						sibling->color = RED;
						rotateRight(root, sibling);
						fixDoubleBlack(root, x, parent);
					}
				}
			} else if (sibling->right != NULL && sibling->right->color == RED) {
				if (parent->left == x) {
					// if the right child of the sibling is red, we perform a rotation
					sibling->right->color = BLACK;
					sibling->color = RED;
					rotateRight(root, sibling);
					fixDoubleBlack(root, x, parent);
				} else {
					// if the left child of the sibling is red, we perform a rotation
					sibling->left->color = BLACK;
					sibling->color = RED;
					rotateLeft(root, sibling);
					fixDoubleBlack(root, x, parent);
				}
			} else {
				// if the sibling has no red children
				sibling->color = RED;
				if (parent->color == BLACK) {
						fixDoubleBlack(root, parent, parent->parent);
				} else {
						parent->color = BLACK;
				}
			}
  	}
}

template <typename Key, typename Value>
void RBTree<Key, Value>::remove(const Key &key) {
    Node<Key, Value> *z = searchBST(root, key);
    if (z == nullptr) {
        return;
    }
    Node<Key, Value> *x;
    Node<Key, Value> *y = z;
    Color originalColor = y->color;
    if (z->left == nullptr) {
			x = z->right;
			transplant(root, z, z->right);
    } else if (z->right == nullptr) {
			x = z->left;
			transplant(root, z, z->left);
    } else {
			y = minimum(z->right);
			originalColor = y->color;
			x = y->right;
			if (y->parent == z) {
					x->parent = y;
			} else {
				transplant(root, y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			transplant(root, z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
    }
    if (originalColor == BLACK) {
			fixDoubleBlack(root, x, x->parent);
    }
    delete z;
}

template <typename Key, typename Value>
void RBTree<Key, Value>::transplant(Node<Key, Value> *&root, Node<Key, Value> *u, Node<Key, Value> *v) {
	if (u->parent == nullptr) {
		root = v;
	} else if (u == u->parent->left) {
		u->parent->left = v;
	} else {
		u->parent->right = v;
	}
	if (v != nullptr) {
		v->parent = u->parent;
	}
}