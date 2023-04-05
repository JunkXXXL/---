#pragma once
#include "Iterator.h"
#include "Node.h"
#include "BinaryTree.h"

class BinaryTreeIterator : public Iterator
{
public:
    BinaryTreeIterator(const BinaryTree *tree);
    BinaryTreeIterator(BinaryTree *tree);
    ~BinaryTreeIterator() override = default;

    bool exists() const override;
    int value() const override;
    void moveToNext() override;
    const Node* getNode();

private:
    const Node* _head = nullptr;
    const Node *_tree = nullptr;
    int _position = 0;
    int _treeHigth = 1;
};

