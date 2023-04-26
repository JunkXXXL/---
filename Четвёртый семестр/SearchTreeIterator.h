#pragma once
#include "Iterator.h"
#include "SearchTree.h"
#include <stack>

class SearchTreeIterator: public Iterator
{
public:
    SearchTreeIterator(const SearchTree * tree);
    SearchTreeIterator(SearchTree * tree);
    ~SearchTreeIterator() override = default;

    bool exists() const override;
    int value() const override;
    void moveToNext() override;
    Node* getNode();

private: 
    Node* _tree = nullptr;
    std::stack<Node*> _nodeStack;

    void _writeInStack(Node* node);
};

