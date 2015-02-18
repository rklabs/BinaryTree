#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "btree.hh"

TEST_CASE( "Test insertion", "[insertion]" ) {
    binary_tree<long> *btree = new binary_tree<long>;
    std::vector<long> inputVector{4, 2, 1, 3, 10};
    std::vector<long> inorderVector{1, 2, 3, 4, 10};
    std::vector<long> preorderVector{4, 2, 1, 3, 10};
    std::vector<long> postorderVector{1, 3, 2, 10, 4};

    for (auto iter : inputVector) {
        btree->insert_nonrecursive(iter);
    }

    btree->inorder();
    btree->preorder();
    btree->postorder();

    for (std::size_t i = 0 ; i < inputVector.size() ; i++) {
        REQUIRE( btree->inorder_vec[i] == inorderVector[i] );
    }

    for (std::size_t i = 0 ; i < inputVector.size() ; i++) {
        REQUIRE( btree->preorder_vec[i] == preorderVector[i] );
    }

    for (std::size_t i = 0 ; i < inputVector.size() ; i++) {
        REQUIRE( btree->postorder_vec[i] == postorderVector[i] );
    }

    REQUIRE( btree->sizeOfTree() == inputVector.size() );
    REQUIRE( btree->height() == 3 );
    REQUIRE( btree->leafCount() == 3 );

    delete btree;
}
