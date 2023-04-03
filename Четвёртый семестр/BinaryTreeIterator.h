#pragma once
#include "Iterator.h"
#include "Node.h"
#include "BinaryTree.h"

class BinaryTreeIterator : public Iterator
{
public:
    BinaryTreeIterator(BinaryTree *tree);
    ~BinaryTreeIterator() override = default;

    bool exists() const override;
    int value() const override;
    bool hasNext() const override;
    void moveToNext() override;

private:
    const Node* _head = nullptr;
    const Node *_tree = nullptr;
    int _position = 0;
    int _treeHigth = 1;
};

