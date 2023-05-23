#pragma once
#include "BinaryTreeTesterClass.h"
#include "SearchTree.h"

class SearchTreeTester: public BinaryTreeTesterClass
{
public:
    SearchTreeTester(const bool toPrint) : BinaryTreeTesterClass(toPrint) {};
    ~SearchTreeTester() override = default;

protected:
    BinaryTree* allocateTree() override;
    void check_addAndCount(const BinaryTree& tree, const int size) override;
    void check_remove(const BinaryTree& tree, const int size) override;
    void check_assign(const BinaryTree& firstTree, const BinaryTree& secondTree) override;

private:
    bool isSearchTree(const BinaryTree tree);
    void getKeysLnr(std::vector<int>& keys, Node* node);
};

