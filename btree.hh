// "Copyright [2014] <Copyright rkadam>"
/* Binary tree */

#ifndef BTREE_H_
#define BTREE_H_

#include <iostream>
#include <vector>
#include <stack>
#include <chrono>
#include <random>
#include <ctime>
#include <deque>

template <typename T>
class node {
 public:
    T val;
    node *left;
    node *right;
};

template <typename T>
class binary_tree {
 private:
    node<T> *root;
    node<T> *head;
    void insert(T val, node<T> *leaf);
    void destroy_binary_tree(node<T> *leaf);
    void preorder(node<T> *leaf);
    void postorder(node<T> *leaf);
    void inorder(node<T> *leaf);
    void inorder_nonrecursive(node<T> *leaf);
    void postorder_nonrecursive(node<T> *leaf);
    void preorder_nonrecursive(node<T> *leaf);
    bool search(T val, node<T> *leaf);
    node<T> *findmax(node<T> *leaf);
    node<T> *findmin(node<T> *leaf);
    node<T> *delete_node(node<T> *leaf, T val);
    bool isBST(node<T> *root);
    void levelorder(node<T> *leaf);
    int sizeOfTree(node<T> *leaf);
    int height(node<T> *leaf);
    int leafCount(node<T> *leaf);
    int diameter(node<T> *leaf, int *ptr);
    void morrisInorder(node<T> *leaf);
    void bstToDLL(node<T> *leaf, node<T> *end);
    void printAllPathsFromRootToLeaf(node<T> *leaf);
    void printLeafNodes(node<T> *root);
    void printEdgeNodes(node<T> *root);
 public:
    std::vector<T> inorder_vec;
    std::vector<T> preorder_vec;
    std::vector<T> postorder_vec;
    binary_tree();
    ~binary_tree();
    void insert(T val);
    void insert_nonrecursive(T val);
    void destroy_binary_tree();
    void preorder();
    void postorder();
    void inorder();
    void preorder_nonrecursive();
    void postorder_nonrecursive();
    void inorder_nonrecursive();
    bool search(T val);
    bool search_nonrecursive(T val);
    // insert using functor
    void operator()(T val);
    T findmax();
    T findmin();
    void delete_node(T val);
    bool isBST();
    void levelorder();
    int sizeOfTree();
    int height();
    int leafCount();
    int diameter();
    void morrisInorder();
    void bstToDLL();
    void printAllPathsFromRootToLeaf();
    void printLeafNodes();
    void printEdgeNodes();
};


template <typename T>
void binary_tree<T>::printEdgeNodes(node<T> *root) {
    std::deque<node<T> *> btree_queue;

    if (root == nullptr) {
        std::cout << "Tree is empty\n";
        return;
    }

    std::cout << root->val << " ";

    btree_queue.push_back(root);

    auto *temp = root->right;

    // Print right most nodes
    do {
        if (temp) {
            std::cout<< temp->val << " ";
        }

        if (temp->right) {
            temp = temp->right;
            std::cout << temp->val << " ";
        } else if (temp->left) {
            temp = temp->left;
            std::cout << temp->val << " ";
        } else if (temp->right == nullptr && temp->left == nullptr) {
            temp = nullptr;
        }
    } while (temp);

    // Print leaf nodes;
    printLeafNodes(root);

    // Print left most nodes
    temp = root->left;
    do {
        if (temp) {
            std::cout<< temp->val << " ";
        }

        if (temp->right) {
            temp = temp->right;
            std::cout << temp->val << " ";
        } else if (temp->left) {
            temp = temp->left;
            std::cout << temp->val << " ";
        } else if (temp->right == nullptr && temp->left == nullptr) {
            temp = nullptr;
        }
    } while (temp);

    std::cout << "\n";
}


template <typename T>
void binary_tree<T>::printEdgeNodes() {
    std::cout << "edge nodes: ";
    printEdgeNodes(root);
}

template <typename T>
void binary_tree<T>::printLeafNodes(node<T> *root) {
    std::deque<node<T> *> btree_queue;

    if (root == nullptr) {
        std::cout << "tree is empty\n";
        return;
    }

    btree_queue.push_back(root);

    while (!btree_queue.empty()) {
        auto *temp = btree_queue.back();
        btree_queue.pop_back();

        // Leaf nodes have both left and right pointers as null
        if (temp->left == nullptr && temp->right == nullptr) {
            std::cout << temp->val << " ";
        } else {
            if (temp->right) {
                btree_queue.push_back(temp->right);
            }

            if (temp->left) {
                btree_queue.push_back(temp->left);
            }
        }
    }
    std::cout << "\n";
}


template <typename T>
void binary_tree<T>::printLeafNodes() {
    std::cout << "leaf nodes: ";
    printLeafNodes(root);
}

template <typename T>
void binary_tree<T>::printAllPathsFromRootToLeaf(node<T> *leaf) {
    std::deque<T> btree_queue;
    // Not implemented
}


template <typename T>
void binary_tree<T>::printAllPathsFromRootToLeaf() {
    printAllPathsFromRootToLeaf(root);
}

template <typename T>
void binary_tree<T>::bstToDLL() {
    // Not implemented
}

// Morris traversal
// 1. Initialize current as root
// 2. While current is not nullptr
//   If current does not have left child
//      a) Print current’s data
//      b) Go to the right, i.e., current = current->right
//   Else
//      a) Make current as right child of the rightmost node in
//         current's left subtree
//      b) Go to this left child, i.e., current = current->left
template <typename T>
void binary_tree<T>::morrisInorder(node<T> *leaf) {
    auto *p = leaf;
    node<T> *temp;

    while (p != nullptr) {
        if (p->left == nullptr) {
            std::cout << p->val << " ";
            p = p->right;
        } else {
            temp = p->left;
            while (temp->right != nullptr && temp->right != p) {
                temp = temp->right;
            }
            if (temp->right == nullptr) {
                temp->right = p;
                p = p->left;
            } else {
                std::cout << p->val << " ";
                temp->right = nullptr;
                p = p->right;
            }
        }
    }
}

template <typename T>
void binary_tree<T>::morrisInorder() {
    std::cout << "morris inorder :";
    morrisInorder(root);
    std::cout << std::endl;
}

template <typename T>
int binary_tree<T>::diameter(node<T> *leaf, int *ptr) {
    if (leaf == nullptr) {
        return 0;
    }

    auto left = diameter(leaf->left, ptr);
    auto right = diameter(leaf->right, ptr);

    if (left + right > *ptr) {
        *ptr = left + right;
    }

    return left > right ? left + 1 : right + 1;
}

template <typename T>
int binary_tree<T>::diameter() {
    auto min = 0;

    return diameter(root, &min);
}

template <typename T>
int binary_tree<T>::leafCount(node<T> *leaf) {
    std::deque<node<T> *> btree_queue;
    int count = 0;

    if (leaf == nullptr) {
        return 0;
    }

    btree_queue.push_front(root);

    while (!btree_queue.empty()) {
        auto *temp = btree_queue.back();
        btree_queue.pop_back();

        if (temp->left == nullptr && temp->right == nullptr) {
            count++;
        } else {
            if (temp->left) {
                btree_queue.push_front(temp->left);
            }
            if (temp->right) {
                btree_queue.push_front(temp->right);
            }
        }
    }
    return count;
}

template <typename T>
int binary_tree<T>::leafCount() {
    return leafCount(root);
}

template <typename T>
int binary_tree<T>::height(node<T> *leaf) {
    if (leaf == nullptr) {
        return 0;
    } else {
        auto leftHeight = height(leaf->left);
        auto rightHeight = height(leaf->right);

        return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
    }
}

template <typename T>
int binary_tree<T>::height() {
    return height(root);
}

template <typename T>
int binary_tree<T>::sizeOfTree(node<T> *leaf) {
    if (leaf == nullptr) {
        return 0;
    } else {
        return sizeOfTree(leaf->left) + sizeOfTree(leaf->right) + 1;
    }
}

template <typename T>
int binary_tree<T>::sizeOfTree() {
    return sizeOfTree(root);
}


template <typename T>
void binary_tree<T>::levelorder(node<T> *leaf) {
    std::deque<node<T> *> btree_queue;

    if (leaf == nullptr) {
        return;
    }

    btree_queue.push_front(leaf);

    while (!btree_queue.empty()) {
        auto *temp = btree_queue.back();
        btree_queue.pop_back();
        std::cout << temp->val << " ";

        if (temp->left) {
            btree_queue.push_front(temp->left);
        }
        if (temp->right) {
            btree_queue.push_front(temp->right);
        }
    }
}

template <typename T>
void binary_tree<T>::levelorder() {
    std::cout << "level order traversal : ";
    levelorder(root);
    std::cout << std::endl;
}

template <typename T>
void binary_tree<T>::preorder_nonrecursive(node<T> *leaf) {
    std::stack<node<T> *> btree_stack;

    while (1) {
        while (leaf) {
            std::cout << leaf->val << " ";
            btree_stack.push(leaf);
            leaf = leaf->left;
        }
        if (btree_stack.empty()) {
            break;
        }
        leaf = btree_stack.top();
        btree_stack.pop();
        leaf = leaf->right;
    }
}

template <typename T>
void binary_tree<T>::preorder_nonrecursive() {
    std::cout << "preorder non recursive: ";
    preorder_nonrecursive(root);
    std::cout << std::endl;
}

// Steps for postorder non recursive traversal
// 1.1 Create an empty stack
// 2.1 Do following while root is not nullptr
//    a) Push root's right child and then root to stack
//    b) Set root as root's left child
// 2.2 Pop an item from stack and set it as root
//    a) If the popped item has a right child and the right child
//       is at top of stack, then remove the right child from stack,
//       push the root back and set root as root's right child
//    b) Else print root's data and set root as nullptr
// 2.3 Repeat steps 2.1 and 2.2 while stack is not empty
template <typename T>
void binary_tree<T>::postorder_nonrecursive(node<T> *leaf) {
    std::stack<node<T> *> btree_stack;

    do {
        while (leaf) {
            if (leaf->right) {
                btree_stack.push(leaf->right);
            }
            btree_stack.push(leaf);
            leaf = leaf->left;
        }

        leaf = btree_stack.top();
        btree_stack.pop();

        if (leaf->right && (btree_stack.top() == leaf->right)) {
            btree_stack.pop();
            btree_stack.push(leaf);
            leaf = leaf->right;
        } else {
            std::cout << leaf->val << " ";
            leaf = nullptr;
        }
    } while (!btree_stack.empty());
}

template <typename T>
void binary_tree<T>::postorder_nonrecursive() {
    std::cout << "postorder non recursive: ";
    postorder_nonrecursive(root);
    std::cout << std::endl;
}

template <typename T>
void binary_tree<T>::inorder_nonrecursive(node<T> *leaf) {
    std::stack<node<T> *> btree_stack;

    while (1) {
        while (leaf) {
            btree_stack.push(leaf);
            leaf = leaf->left;
        }
        if (btree_stack.empty()) {
            break;
        }
        leaf = btree_stack.top();
        btree_stack.pop();
        std::cout << leaf->val << " ";
        leaf = leaf->right;
    }
}

template <typename T>
void binary_tree<T>::inorder_nonrecursive() {
    std::cout << "inorder non recursive: ";
    inorder_nonrecursive(root);
    std::cout << std::endl;
}

template <typename T>
bool binary_tree<T>::isBST(node<T> *root) {
    static node<T> *prev = NULL;

    if (root) {
        if (!isBST(root->left)) {
            return false;
        }

        if (prev != nullptr && root->val <= prev->val) {
            return false;
        }

        prev = root;

        return isBST(root->right);
    }

    return true;
}

template <typename T>
bool binary_tree<T>::isBST() {
    return isBST(root);
}

template <typename T>
node<T> *binary_tree<T>::delete_node(node<T> *leaf, T val) {
    if (leaf == nullptr) {
        std::cout << val << " not found!" << std::endl;
        return nullptr;
    } else if (val < leaf->val) {
        leaf->left = delete_node(leaf->left, val);
    } else if (val > leaf->val) {
        leaf->right = delete_node(leaf->right, val);
    } else {
        if (leaf->left && leaf->right) {
            auto *temp = findmax(leaf->left);
            leaf->val = temp->val;
            leaf->left = delete_node(leaf->left, leaf->val);
        } else {
            auto *temp = leaf;
            if (temp->left == nullptr &&
                temp->right == nullptr) {
                delete temp;
                return nullptr;
            }
            if (leaf->left == nullptr) {
                leaf = leaf->right;
            }
            if (leaf->right == nullptr) {
                leaf = leaf->left;
            }
            delete temp;
        }
    }
    return leaf;
}

template <typename T>
void binary_tree<T>::delete_node(T val) {
    delete_node(root, val);
}

template <typename T>
node<T> *binary_tree<T>::findmax(node<T> *leaf) {
    while (leaf->right != nullptr) {
        leaf = leaf->right;
    }
    return leaf;
}

template <typename T>
T binary_tree<T>::findmax() {
    return findmax(root)->val;
}

template <typename T>
node<T> *binary_tree<T>::findmin(node<T> *leaf) {
    while (leaf->left != nullptr) {
        leaf = leaf->left;
    }
    return leaf;
}

template <typename T>
T binary_tree<T>::findmin() {
    return findmin(root)->val;
}

template <typename T>
bool binary_tree<T>::search(T val, node<T> *leaf) {
    if (leaf != nullptr) {
        if (val == leaf->val) {
            return true;
        } else if (val < leaf->val) {
            return search(val, leaf->left);
        } else if (val > leaf->val) {
            return search(val, leaf->right);
        }
    } else {
        return false;
    }
    return false;
}

template <typename T>
bool binary_tree<T>::search(T val) {
    return search(val, root);
}

template <typename T>
bool binary_tree<T>::search_nonrecursive(T val) {
    node<T> *temp = root;

    bool found = false;
    while (!found && temp != nullptr) {
        if (temp->val == val) {
            found = true;
            return found;
        } else if (val < temp->val) {
            temp = temp->left;
        } else if (val >= temp->val) {
            temp = temp->right;
        }
    }
    return false;
}

template <typename T>
void binary_tree<T>::operator()(T val) {
    insert(val);
}

template <typename T>
void binary_tree<T>::preorder(node<T> *leaf) {
    if (leaf) {
        std::cout << leaf->val << " ";
        preorder_vec.push_back(leaf->val);
        preorder(leaf->left);
        preorder(leaf->right);
    }
}

template <typename T>
void binary_tree<T>::postorder(node<T> *leaf) {
    if (leaf) {
        postorder(leaf->left);
        postorder(leaf->right);
        std::cout << leaf->val << " ";
        postorder_vec.push_back(leaf->val);
    }
}

template <typename T>
void binary_tree<T>::inorder(node<T> *leaf) {
    if (leaf) {
        inorder(leaf->left);
        std::cout << leaf->val << " ";
        inorder_vec.push_back(leaf->val);
        inorder(leaf->right);
    }
}

template <typename T>
void binary_tree<T>::preorder() {
    preorder_vec.clear();
    std::cout << "preorder traversal: ";
    preorder(root);
    std::cout << std::endl;
    std::cout << "preorder_vec : ";
    for (auto iter : preorder_vec) {
        std::cout << iter << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void binary_tree<T>::postorder() {
    postorder_vec.clear();
    std::cout << "postorder traversal: ";
    postorder(root);
    std::cout << std::endl;
    std::cout << "postorder_vec : ";
    for (auto iter : postorder_vec) {
        std::cout << iter << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void binary_tree<T>::inorder() {
    inorder_vec.clear();
    std::cout << "inorder traversal: ";
    inorder(root);
    std::cout << std::endl;
    std::cout << "inorder_vec : ";
    for (auto iter : inorder_vec) {
        std::cout << iter << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void binary_tree<T>::destroy_binary_tree(node<T> *leaf) {
    if (leaf != nullptr) {
        destroy_binary_tree(leaf->left);
        destroy_binary_tree(leaf->right);
        delete leaf;
    }
}

template <typename T>
void binary_tree<T>::destroy_binary_tree() {
    destroy_binary_tree(root);
}

template <typename T>
binary_tree<T>::binary_tree() : root(nullptr) {
    std::cout << "Inside constructor" << std::endl;
}

template <typename T>
binary_tree<T>::~binary_tree() {
    std::cout << "Inside destructor" << std::endl;
    destroy_binary_tree();
}

template <typename T>
void binary_tree<T>::insert(T val, node<T> *leaf) {
    if (val < leaf->val) {
        if (leaf->left != nullptr) {
            insert(val, leaf->left);
        } else {
            leaf->left = new node<T>;
            leaf->left->val = val;
            leaf->left->left = nullptr;
            leaf->left->right = nullptr;
        }
    } else if (val >= leaf->val) {
        if (leaf->right != nullptr) {
            insert(val, leaf->right);
        } else {
            leaf->right = new node<T>;
            leaf->right->val = val;
            leaf->right->left = nullptr;
            leaf->right->right = nullptr;
        }
    }
}

template <typename T>
void binary_tree<T>::insert(T val) {
    if (!root) {
        root = new node<T>;
        root->val = val;
        root->left = nullptr;
        root->right = nullptr;
    } else {
        insert(val, root);
    }
}

template <typename T>
void binary_tree<T>::insert_nonrecursive(T val) {
    node<T> *n = new node<T>;
    n->val = val;
    n->left = nullptr;
    n->right = nullptr;

    if (!root) {
        root = n;
        return;
    }

    node<T> *temp = root;

    bool inserted = false;
    while (!inserted) {
        if (val < temp->val) {
            if (temp->left == nullptr) {
                temp->left = n;
                inserted = true;
                return;
            } else {
                temp = temp->left;
            }
        }
        if (val >= temp->val) {
            if (temp->right == nullptr) {
                temp->right = n;
                inserted = true;
                return;
            } else {
                temp = temp->right;
            }
        }
    }
}

#endif  // BTREE_H_
