#include "SearchTree.h"

int main()
{
	SearchTree tree(6);
	tree.addNode(5);
	tree.addNode(1);
	tree.addNode(8);
	tree.addNode(9);
	tree.addNode(4);
	tree.addNode(99);
	tree.addNode(3);
	tree.addNode(7);
	tree.addNode(11);
	tree.addNode(10);
	tree.addNode(2);

	tree.print();
	std::cout << "|||||\n";
	tree.deleteNode(6);
	tree.print();
}