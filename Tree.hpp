
#ifndef REDBLACKTREE_TREE_HPP
#define REDBLACKTREE_TREE_HPP

#include <iostream>
typedef struct branch
{
	int 			data;
	bool 			isRed;
	struct branch	*left;
	struct branch	*right;
	struct branch	*father;
} Branch;

class Tree {
public:
	Tree();
	~Tree();
	void 		myswap(int* a, int* b); // put to utilities?
	void 		insertElement(int newdata);
	void 		deleteElement(int data);
	Branch*		findElement(int data, Branch*& branch);

	//----debug functions ---------
	Branch*		getTree() const;
	//----end of debug functions---

private:
	Branch*	_branch;

	//-----internal mechanic for insertElement()------
	Branch*		_createElement(int newdata, Branch*& father);
	void 		_addElement(int newdata, Branch*& aBranch, Branch* father); // 3-rd argument isn't a referense, because I need to use nullptr!
	void		_balancer(Branch*& aBranch);
			//-----internal mechanic for balancer()------
	void		_redUncle(Branch*& father, Branch* uncle);
	bool		_isFatherandGrandontheSameSide(Branch*& aBranch);
	std::string _sideChecker(Branch*& son, Branch*& father);
	void		_blackUncleFatherGrandDifSides(Branch* son, Branch* father, Branch* grand);
	void		_blackUncleFatherGrandSameSides(Branch* son, Branch* father, Branch* grand);
	void		_smallRotor(Branch*& son, Branch*& father, Branch*& grand, std::string side);
	void		_rePainting(Branch*& father, Branch*& grand);
	void		_sonsReplacer(Branch*& fromWhom, Branch*& toWhom);
	void		_sonChanger(Branch*& older, Branch*& younger, std::string side);
			//-----end of balancer mechanic------------------
	//-----end of inserting mechanic------------------

	//-----internal mechanic for deleteElement()------
	void 		_deleteR0case(Branch*& toDel);
	void 		_deleteB0case(Branch*& toDel); // not made
	void		_deleteR2case(Branch*& toDel);
	Branch*		_findReplacer(Branch*& node);
};


#endif //REDBLACKTREE_TREE_HPP
