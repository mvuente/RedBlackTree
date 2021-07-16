
#include "Tree.hpp"

Tree::Tree()
{
	_branch = nullptr;
}

Tree::~Tree()
{}

void 	Tree::myswap(int* a, int* b)
{
	int		c;
	c = *a;
	*a = *b;
	*b = c;
}

Branch*	Tree::findElement(int data, int dataifchanged, Branch*& branch)
{
	Branch*	tempNode = branch;
	int 	datatofind = data;
	if (data != dataifchanged)
		datatofind = dataifchanged;
	while (tempNode)
	{
		if (datatofind == tempNode->data)
		{
			//std::cout << branch->data << " AND " << branch->left->data << std::endl;
			if (data == dataifchanged)
			return tempNode;
			if (tempNode->left->data == data)
				return tempNode->left;
			return tempNode->right;

		}
		else if (datatofind < tempNode->data)
			tempNode = tempNode->left;
		else
			tempNode = tempNode->right;
	}
		return nullptr;
}

void 	Tree::deleteElement(int data1, int data2)
{
	Branch*	toDel = findElement(data1, data2, _branch);
	if (!toDel)
	{
		std::cout << "not found" << std::endl;//for debug
		return;
	}
	if (toDel->isRed && !toDel->left && !toDel->right) //R0 case
		_deleteR0case(toDel);
	else if (!toDel->isRed && !toDel->left && !toDel->right) // B0 case, should be made
	{
		_deleteB0case(toDel);
	}

	else if (toDel->left && toDel->right) // 2 children case
	{
		_delete2case(toDel);
	}

	else if ((toDel->left && !toDel->right) || (!toDel->left && toDel->right)) // 1 child
		_delete1case(toDel);

}

//----------insert mechanic-------------------------------------------

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

void		Tree::_rePainting(Branch*& younger, Branch*& older)
{
	younger->isRed = !younger->isRed;
	older->isRed = !older->isRed;
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

//-----end of insert mechanic--------------------------------------------------------



//-----internal mechanic for deleteElement()------------------------------------------
void 	Tree::_deleteR0case(Branch*& toDel)
{
	Branch*	father = toDel->father;
	if (father->left == toDel)
		father->left = nullptr;
	else
		father->right = nullptr;
	delete(toDel);
}

void	Tree::_delete2case(Branch*& toDel)
{
	int 	delval = toDel->data;
	myswap(&(toDel->data), &(_findReplacer(toDel->right)->data));
	deleteElement(delval, toDel->data);
}

void	Tree::_delete1case(Branch*& toDel)
{
	Branch*	replacer;
	if (toDel->right)
		replacer = toDel->right;
	else
		replacer = toDel->left;
	myswap(&(toDel->data), &(replacer->data));
	deleteElement(replacer->data, toDel->data);
}

Branch*	Tree::_findReplacer(Branch*& node)
{
	while (node->left)
		node = node->left;
	//std::cout << &node << std::endl;
	return node;
}

void 	Tree::_deleteB0case(Branch*& toDel) // need to be made
{
	std::cout << "this method isn't made yet" << toDel->data << std::endl;
	Branch*	parentBeBalanced = toDel->father;
	if (parentBeBalanced->left == toDel)
		parentBeBalanced->left = nullptr;
	else
		parentBeBalanced->right = nullptr;
	delete(toDel);
	_balancerAfterDelete(parentBeBalanced);
}

void 	Tree::_balancerAfterDelete(Branch*& node)
{
	Branch*	son = _oppositeSon(node);
	if (node->isRed && !son->isRed && son->left && !son->left->isRed && son->right && !son->right->isRed)
		_rePainting(son, node);
}

Branch*	Tree::_oppositeSon(Branch*& node)
{
	if (node && node->left)
		return node->left;
	return node->right;
}