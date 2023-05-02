#pragma once
#include "Iterator.h"
#include "Node.h"
#include "BinaryTree.h"

class BinaryTreeIterator : public Iterator
{
public:
    BinaryTreeIterator(const BinaryTree *tree);
    BinaryTreeIterator(BinaryTree *tree);
    ~BinaryTreeIterator() override;

    bool exists() const override;
    int value() const override;
    void moveToNext() override;
    Node* getNode();

private:
    Node *_tree = nullptr;
    int _position = 0;
    std::vector<Node*> _nodeVec;

    void _writeVector();
};

