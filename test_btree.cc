#include "btree.hh"

#define SIZE 1000

void btree_tests() {
    binary_tree<long> *btree = new binary_tree<long>;
    using timepoint = std::chrono::time_point<std::chrono::system_clock>;
    timepoint start;
    timepoint end;
    std::chrono::duration<double> elapsed_seconds;

    // Set random seed
    std::srand(std::time(0));

    // Measure insert time
    start = std::chrono::system_clock::now();
    for (long i=0; i < SIZE; i++) {
        btree->insert_nonrecursive(std::rand());
    }
    end = std::chrono::system_clock::now();

    elapsed_seconds = end - start;
    std::cout << "time taken(non-recursive insert): "
              << elapsed_seconds.count() << "s\n";

    // Measure search time
    bool found;
    start = std::chrono::system_clock::now();
    long key = std::rand();
    found = btree->search_nonrecursive(key);
    end = std::chrono::system_clock::now();
    if (!found) {
        std::cout << "key " << key << " was not found" << std::endl;
    } else {
        std::cout << "key " << key << " was found" << std::endl;
    }
    elapsed_seconds = end - start;
    std::cout << "time taken(non-recursive search): "
              << elapsed_seconds.count() << "s\n";

    delete btree;
    btree = NULL;

    // Measure insert time
    btree = new binary_tree<long>;
    start = std::chrono::system_clock::now();
    for (long i=0; i < SIZE; i++) {
        btree->insert(std::rand());
    }
    end = std::chrono::system_clock::now();

    elapsed_seconds = end - start;
    std::cout << "time taken(recursive): "
              << elapsed_seconds.count() << "s\n";

    // Measure search time
    start = std::chrono::system_clock::now();
    found = btree->search(key);
    end = std::chrono::system_clock::now();

    if (!found) {
        std::cout << "key " << key << " was not found" << std::endl;
    } else {
        std::cout << "key " << key << " was found" << std::endl;
    }
    elapsed_seconds = end - start;
    std::cout << "time taken(recursive search): "
              << elapsed_seconds.count() << "s\n";

    delete btree;
}

int main(int argc, char *argv[]) {
    binary_tree<long> *btree = new binary_tree<long>;
    std::vector<int> vec{4, 2, 1, 3, 10};

    std::cout << "original list: ";
    for (auto iter : vec) {
        std::cout << iter << " ";
    }
    std::cout << std::endl;

    for (auto iter : vec) {
        btree->insert_nonrecursive(iter);
    }

    btree->printLeafNodes();
    btree->printEdgeNodes();
    btree->preorder();
    btree->inorder();
    btree->postorder();

    btree->levelorder();

    btree->morrisInorder();

    std::cout << "size of tree = " << btree->sizeOfTree() << std::endl;
    std::cout << "height of tree = " << btree->height() << std::endl;
    std::cout << "no. of leaves = " << btree->leafCount() << std::endl;
    std::cout << "diameter = " << btree->diameter() << std::endl;

    btree->postorder_nonrecursive();
    btree->preorder_nonrecursive();
    btree->inorder_nonrecursive();

    auto key = 8;
    if (btree->search(key)) {
        std::cout << key << " found" << std::endl;
    } else {
        std::cout << key << " not found" << std::endl;
    }

    key = 100;
    if (btree->search(key)) {
        std::cout << key << " found" << std::endl;
    } else {
        std::cout << key << " not found" << std::endl;
    }

    (*btree)(key);

    std::cout << "max " << btree->findmax() << std::endl;
    std::cout << "min " << btree->findmin() << std::endl;

    btree->inorder();

    btree->delete_node(2);
    btree->delete_node(1000);

    btree->inorder();
    btree->preorder();
    btree->postorder();

    std::cout << "isBST " << (btree->isBST() ? "Yes" : "No") << std::endl;

    btree->bstToDLL();

    delete btree;

    btree_tests();

    return 0;
}
