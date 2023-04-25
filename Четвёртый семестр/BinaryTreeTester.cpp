#include "BinaryTree.h"
#include <iostream>
#include <vector>
#include "BinaryTreeIterator.h"
#include "BinaryTreeTesterClass.h"
#include "SearchTree.h"

void GigaTest()
{
	BinaryTree tree(new Node(0, nullptr, new Node(1, 
		new Node(4, new Node(6, nullptr, new Node(9, nullptr, new Node(15))),
			new Node(5, new Node(17, nullptr, new Node(18)), new Node(10, nullptr, nullptr))),
		new Node(3, new Node(19, nullptr, nullptr), new Node(8, nullptr, nullptr)))
	));
	tree.print();
	auto vector = tree.getVector();
	tree.deleteNode(4);
	//tree.print();
}

int main()
{
	//GigaTest();
	BinaryTreeTesterClass tst(false);
	tst.test(100);
	//GigaTest();

	//SearchTree tree;
	//tree.addNode(-1);
	//tree.addNode(2);
	//tree.print();

	return 0;
}