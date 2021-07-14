
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
		_balancer(aBranch);
	}
	else if (aBranch->data == newdata)
		std::cout << "value for the key will be renovated" << std::endl;
	else if (aBranch->data > newdata)
	{
		_addElement(newdata, aBranch->left, aBranch);
	}
	else
	{
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
			_redUncle(aBranch->father, uncle);
		else if ((!uncle || (uncle && !uncle->isRed)) && !_isFatherandGrandontheSameSide(aBranch)) //condition for black uncle and farther and grandfather are on different sides
			_blackUncleFatherGrandDifSides(aBranch, aBranch->father, aBranch->father->father);
		else if ((!uncle || (uncle && !uncle->isRed)) && _isFatherandGrandontheSameSide(aBranch))//condition for black uncle and farther and grandfather are on the same side
			_blackUncleFatherGrandSameSides(aBranch, aBranch->father, aBranch->father->father);
	}
	else if (!aBranch->father)// check further
		aBranch->isRed = false;
}

void	Tree::_redUncle(Branch*& father, Branch* uncle)
{
	father->isRed = false;
	uncle->isRed = false;
	father->father->isRed = true;
	_balancer(father->father); // to check, if it isn't a root
}

bool	Tree::_isFatherandGrandontheSameSide(Branch*& aBranch)
{
	if (_sideChecker(aBranch->father, aBranch->father->father) == _sideChecker(aBranch, aBranch->father))
		return true;
	return false;
}

std::string Tree::_sideChecker(Branch*& son, Branch*& father)
{
	if (father->left == son)
		return "left";
	return "right";
}

void		Tree::_blackUncleFatherGrandDifSides(Branch* son, Branch* father, Branch* grand)
{
	//1. small rotation
	_smallRotor(son, father, grand, _sideChecker(son, father));
	//2. samesides = big rotor
	_blackUncleFatherGrandSameSides(father, son, grand);
}

void		Tree::_blackUncleFatherGrandSameSides(Branch* son, Branch* father, Branch* grand)
{
	std::string newside = _sideChecker(son, father);
	Branch*	tempRoot = grand->father;
	std::string newsideforlast = _sideChecker(grand, tempRoot);
	Branch*	temp;
	if (newside == "left")
	{
		temp = father->right;
		father->right = grand;
		grand->left = temp;
	}
	else
	{
		temp = father->left;
		father->left = grand;
		grand->right = temp;
	}
	grand->father = father;
	_rePainting(father, grand);
	father->father = tempRoot;
	if (!tempRoot)
	{
		_branch = father;
	}
	else if (newsideforlast == "left")
		tempRoot->left = father;
	else
		tempRoot->right = father;
}

void		Tree::_rePainting(Branch*& father, Branch*& grand)
{
	father->isRed = !father->isRed;
	grand->isRed = !grand->isRed;
}

void		Tree::_smallRotor(Branch*& son, Branch*& father, Branch*& grand, std::string side)
{
	std::string newside;
	if (side == "left")
		newside = "right";
	else
		newside = "left";
	_sonChanger(grand, son, newside);
	_sonsReplacer(son, father);
	_sonChanger(son, father, newside);
}

void		Tree::_sonsReplacer(Branch*& fromWhom, Branch*& toWhom)
{
	toWhom->left = fromWhom->left;
	toWhom->right = fromWhom->right;
}

void		Tree::_sonChanger(Branch*& older, Branch*& younger, std::string side)
{
	if (side == "left")
		older->left = younger;
	else
		older->right = younger;
	younger->father = older;
}

// --- for debug-----------

Branch*	Tree::getTree() const
{
	return _branch;
}


//---- end of fro debug----