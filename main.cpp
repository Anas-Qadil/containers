// #include "main.hpp"
#include <iostream>
#include "./map/RBTree.hpp"

int main(void)
{
    // test version 1
	RBTree<int, int> tree;
    tree.insert({10, 10});
    tree.insert({20, 20});
    tree.insert({30, 30});
    tree.insert({40, 40});
    tree.insert({50, 50});

    // check if the tree contains a node with a given key
    std::cout << tree.contains(30) << std::endl; // true
    std::cout << tree.contains(35) << std::endl; // false
    
    // // access the value of a node with a given key
    std::cout << tree[40] << std::endl; // 40

    // // remove a node with a given key
    tree.inorder(); // 10 20 30 40 50
    std::cout << "----------------------------------" << std::endl;
    tree.remove(40);
    std::cout << tree.contains(40) << std::endl; // false

    // // in-order traversal of the tree
    tree.inorder(); // 10 20 30 50

    // -------------tests versions 2------------
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    // Create an empty RBTree
    RBTree<int, std::string> rbtree;
    
    // Insert some key-value pairs
    rbtree.insert({1, "first"});
    rbtree.insert({2, "second"});
    rbtree.insert({3, "third"});
    rbtree.insert({4, "fourth"});
    rbtree.insert({5, "fifth"});
    
    // Print the tree in-order
    std::cout << "In-order traversal:" << std::endl;
    rbtree.inorder();
    std::cout << std::endl;
    
    // Check if a key is in the tree
    std::cout << "Contains key 3: " << rbtree.contains(3) << std::endl;
    std::cout << "Contains key 6: " << rbtree.contains(6) << std::endl;
    
    // Access the value of a key
    std::cout << "Value of key 3: " << rbtree.at(3) << std::endl;
    
    // Remove a key from the tree
    rbtree.remove(3);
    std::cout << "In-order traversal after removing key 3:" << std::endl;
    rbtree.inorder();
    std::cout << std::endl;
    
    // Clear the tree
    rbtree.clear();
    std::cout << "In-order traversal after clearing tree: ";
    rbtree.inorder();
    std::cout << std::endl;
}
