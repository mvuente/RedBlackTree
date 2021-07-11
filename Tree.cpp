
#include "Tree.hpp"

Tree::Tree()
{}

Tree::~Tree()
{}

void Tree::addElement(int newdata)
{
	if (!_branch)
	{
		_branch = new Branch;
		_branch->data = newdata;
		std::cout << _branch->data << std::endl;
	}
	else
		std::cout << "WRONG" << std::endl;
}