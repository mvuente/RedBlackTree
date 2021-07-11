
#include "Tree.hpp"

Tree::Tree()
{
	_branch = nullptr;
}

Tree::~Tree()
{}

void 	Tree::insertElement(int newdata)
{
	_addElement(newdata, _branch);
}

Branch*	Tree::_createElement(int newdata)
{
	Branch*	newbranch = new Branch;
	newbranch->data = newdata;
	newbranch->right = nullptr;
	newbranch->left = nullptr;
	newbranch->isRed = false;
	return newbranch;
}

void 	Tree::_addElement(int newdata, Branch*& aBranch)
{
	if (!aBranch)
	{
		aBranch = _createElement(newdata);
		std::cout << aBranch->data << std::endl; //just for check
		_balancer(aBranch);
	}
	else if (aBranch->data == newdata)
		std::cout << "value for the key will be renovated" << std::endl;
	else if (aBranch->data > newdata)
	{
		std::cout << "MAKING LEFT BRANCH" << std::endl;
		_addElement(newdata, aBranch->left);
	}
	else
	{
		std::cout << "MAKING RIGHT BRANCH" << std::endl;
		_addElement(newdata, aBranch->right);
	}


}

void	Tree::_balancer(Branch*& aBranch)
{

}