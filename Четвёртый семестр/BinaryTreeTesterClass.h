#pragma once
#include "BinaryTree.h"
#include <assert.h>
#include <time.h>

class BinaryTreeTesterClass
{

public:
    BinaryTreeTesterClass(bool toPrint = false) { _toPrint = toPrint; };
    virtual ~BinaryTreeTesterClass() = default;

    void test(const int size, const bool toPrint);

protected:
    virtual BinaryTree* allocateTree();
    void deallocateTree(BinaryTree * tree);
    virtual void check_addAndCount(const BinaryTree & tree, const int size);
    virtual void check_remove(const BinaryTree & tree, const int size);
    virtual void check_assign(const BinaryTree& firstTree, const BinaryTree& secondTree);
    void check_height(const BinaryTree & tree, const int size);

private:
    void addAndCount();
    void destructor();
    void remove();
    void clear();
    void assign();
    void height();
    void height_trivialCases();
    void height_longOnlyLeftSubtree();
    void height_longOnlyRightSubtree();
    void height_longOnlyLeftAndRightSubtrees();
    void height_longRandomZigzagSubtrees();

private:
    int m_maxSize = 0;
    bool _toPrint = false;
};

