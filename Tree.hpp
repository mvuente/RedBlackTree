
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
	void 		insertElement(int newdata);

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
	void		_blackUncleFatherGrandDifSides(Branch*& son, Branch* father, Branch* grand);
	void	_blackUnclefatherGrandsame(Branch*& aBranch);
	void		_smallRotor(Branch*& son, Branch*& father, Branch*& grand, std::string side);
	void		_sonsReplacer(Branch*& fromWhom, Branch*& toWhom);
	void		_sonChanger(Branch*& older, Branch*& younger, std::string side);
			//-----end of balancer mechanic------------------
	//-----end of inserting mechanic------------------
};


#endif //REDBLACKTREE_TREE_HPP
