
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
	void 	insertElement(int newdata);

private:
	Branch*	_branch;

	//-----internal mechanic for insertElement()------
	Branch*	_createElement(int newdata, Branch*& father);
	void 	_addElement(int newdata, Branch*& aBranch, Branch* father); // 3-rd argument isn't a referense, because I need to use nullptr!
	void	_balancer(Branch*& aBranch);
			//-----internal mechanic for balancer()------
	void	_redUncle(Branch*& father, Branch* uncle);
	void	_blackUncleFatherGrandDiff(Branch*& aBranch);
	void	_blackUnclefatherGrandsame(Branch*& aBranch);
			//-----end of balancer mechanic------------------
	//-----end of inserting mechanic------------------
};


#endif //REDBLACKTREE_TREE_HPP
