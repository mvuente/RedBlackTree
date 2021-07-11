
#include "Tree.hpp"

Tree::Tree()
{
	_branch = nullptr;
}

Tree::~Tree()
{}

Branch*	Tree::createElement(int newdata)
{
	Branch*	newbranch = new Branch;
	newbranch->data = newdata;
	newbranch->right = nullptr;
	newbranch->left = nullptr;
	newbranch->isRed = false;
	return newbranch;
}

void 	Tree::addElement(int newdata)
{
	if (!_branch)
	{

		_branch = createElement(newdata);
		std::cout << _branch->data << std::endl;

	}
	else
		std::cout << "WRONG" << std::endl;
}