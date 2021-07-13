
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
	if (aBranch->father && aBranch->father->father) //if it isn't a root and father isn't a root, it should be balanced
	{
		Branch*	grand = aBranch->father->father;
		Branch*	uncle = grand->left;
		if (aBranch->father == uncle)
			uncle = grand->right;
		//family has been determined
		if (uncle && uncle->isRed) //condition for red Uncle
			redUncle(aBranch->father, uncle);
		else if () //condition for black uncle and farther and grandfather are on different sides
			blackUncleFatherGrandDiff();
		else //condition for black uncle and farther and grandfather are on the same side
			blackUnclefatherGrandsame();
	}
	else
		aBranch->isRed = false; // I'm not sure

}

void	Tree::_redUncle(Branch*& father, Branch* uncle)
{
	father->isRed = false;
	uncle->isRed = false;
	father->father->isRed = true;
	_balancer(father->father); // to check, if it isn't a root
}