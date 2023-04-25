#include "BinaryTreeTesterClass.h"

void BinaryTreeTesterClass::test(const int size)
{
    m_maxSize = size;
    assign();
    height();
    addAndCount();
    destructor();
    clear();
    remove();
    
}

BinaryTree* BinaryTreeTesterClass::allocateTree()
{
    return new BinaryTree;
}

void BinaryTreeTesterClass::deallocateTree(BinaryTree* tree)
{
    delete tree;
}


void BinaryTreeTesterClass::addAndCount()
{
    BinaryTree* tree = allocateTree();
    check_addAndCount(*tree, 1);

    for (int i = 1; i < m_maxSize; ++i) {
        tree->addNode(i);
        check_addAndCount(*tree, i + 1);
    }

    deallocateTree(tree);
}

void BinaryTreeTesterClass::check_addAndCount(const BinaryTree& tree, const int size)
{
    assert(tree.size() == size);
}

void BinaryTreeTesterClass::destructor()
{
    for (int cycles = 0; cycles < 2000; cycles++)
    {
        BinaryTree* tree = allocateTree();
        for (int i = 0; i < m_maxSize; ++i) {
            tree->addNode(i);
        }
        deallocateTree(tree);
    }

    std::cout << "wait...";
    getchar();
}

void BinaryTreeTesterClass::remove()
{
    int invalidKey = -1;
    std::vector<int> nodeKeys;

    BinaryTree tree;
    tree.deleteNode(invalidKey);

    for (int i = 1; i < m_maxSize; ++i) {
        nodeKeys.push_back(i);
        tree.addNode(i);
    }
    if (_toPrint)
    {
        tree.print();
    }

    while (!nodeKeys.empty()) {
        int removedNodeIndex = rand() % nodeKeys.size(); //3

        tree.deleteNode(invalidKey);
        check_remove(tree, nodeKeys.size());

        if (_toPrint) std::cout << "\n remove" << nodeKeys[removedNodeIndex] << " \n";

        tree.deleteNode(nodeKeys[removedNodeIndex]);
        nodeKeys.erase(nodeKeys.begin() + removedNodeIndex);
        check_remove(tree, nodeKeys.size());

        if (_toPrint)
        {
            tree.print();
        }
    }

    tree.deleteNode(invalidKey);
    check_remove(tree, nodeKeys.size());
}

void BinaryTreeTesterClass::check_remove(const BinaryTree& tree, const int size)
{
    assert(tree.size() == size + 1);
}

void BinaryTreeTesterClass::check_assign(const BinaryTree& firstTree, const BinaryTree& secondTree)
{
    assert(firstTree.getRoot() != secondTree.getRoot());
}

void BinaryTreeTesterClass::assign()
{
    BinaryTree tree1(new Node(5));
    BinaryTree tree2;
    tree2 = tree1;
    check_assign(tree1, tree2);

    BinaryTree tree3(tree2);
    check_assign(tree3, tree2);
}

void BinaryTreeTesterClass::clear()
{
    BinaryTree* tree = allocateTree();
    check_addAndCount(*tree, 1);

    for (int i = 1; i < m_maxSize; ++i) {
        tree->addNode(i);
    }
    tree->clear();
    check_addAndCount(*tree, 1);

    deallocateTree(tree);
}

void BinaryTreeTesterClass::check_height(const BinaryTree& tree, const int size)
{
    assert(tree.getHeigth() == size + 1);
}

void BinaryTreeTesterClass::height()
{
    height_trivialCases();
    height_longOnlyLeftSubtree();
    height_longOnlyRightSubtree();
    height_longOnlyLeftAndRightSubtrees();
    height_longRandomZigzagSubtrees();
}

void BinaryTreeTesterClass::height_trivialCases()
{
    BinaryTree tree;
    check_height(tree, 0);
    tree.addNode(0);
    check_height(tree, 1);
}

void BinaryTreeTesterClass::height_longOnlyLeftSubtree()
{
    Node* node = new Node(0);
    for (int i = 0; i < m_maxSize; ++i) {
        Node* parent;
        parent = new Node(i, node, nullptr);
        node = parent;
    }
    BinaryTree zigZag(node);
    check_height(zigZag, m_maxSize);
}

void BinaryTreeTesterClass::height_longOnlyRightSubtree()
{
    Node* node = new Node(0);
    for (int i = 0; i < m_maxSize; ++i) {
        Node* parent;
        parent = new Node(i, nullptr, node);
        node = parent;
    }
    BinaryTree zigZag(node);
    check_height(zigZag, m_maxSize);
}

void BinaryTreeTesterClass::height_longOnlyLeftAndRightSubtrees()
{
    Node* node = new Node(0);
    for (int i = 1; i < m_maxSize; ++i) {
        Node* parent;
        parent = new Node(i, node, nullptr);
        node = parent;
    }
    Node* node2 = new Node(0);
    for (int i = 1; i < m_maxSize; ++i) {
        Node* parent;
        parent = new Node(i, nullptr, node2);
        node2 = parent;
    }
    BinaryTree zigZag(new Node(-1, node, node2));
    check_height(zigZag, m_maxSize);
}

void BinaryTreeTesterClass::height_longRandomZigzagSubtrees()
{
    Node* node = new Node(0);
    for (int i = 0; i < m_maxSize; ++i) {
        Node* parent;
        if (rand() % 2) {
            parent = new Node(i, node, nullptr);
        }
        else {
            parent = new Node(i, nullptr, node);
        }
        node = parent;
    }
    BinaryTree zigZag(node);
    check_height(zigZag, m_maxSize);
}