
#include "Tree.hpp"

Tree::Tree()
{
	_branch = nullptr;
}

Tree::~Tree()
{}

void 	Tree::insertElement(int newdata)
{
	_addElement(newdata, _branch, nullptr);
}

void 	Tree::_addElement(int newdata, Branch*& aBranch, Branch* father)
{
	if (!aBranch)
	{
		aBranch = _createElement(newdata, father);
		std::cout << aBranch->data << " red is " << aBranch->isRed << std::endl; //just for check
		_balancer(aBranch);
	}
	else if (aBranch->data == newdata)
		std::cout << "value for the key will be renovated" << std::endl;
	else if (aBranch->data > newdata)
	{
		std::cout << "MAKING LEFT BRANCH" << std::endl;
		_addElement(newdata, aBranch->left, aBranch);
	}
	else
	{
		std::cout << "MAKING RIGHT BRANCH" << std::endl;
		_addElement(newdata, aBranch->right, aBranch);
	}


}

Branch*	Tree::_createElement(int newdata, Branch*& father)
{
	Branch*	newbranch = new Branch;
	newbranch->data = newdata;
	newbranch->right = nullptr;
	newbranch->left = nullptr;
	newbranch->father = father;
	newbranch->isRed = true;
	if (!father)
		newbranch->isRed = false; // root is always black
	return newbranch;
}



void	Tree::_balancer(Branch*& aBranch)
{
	if () //condition for red Uncle
		redUncle();
	else if () //condition for black uncle and farther and grandfather are on different sides
		blackUncleFatherGrandDiff();
	else //condition for black uncle and farther and grandfather are on the same side
		blackUnclefatherGrandsame();
}