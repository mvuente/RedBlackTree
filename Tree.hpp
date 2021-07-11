
#ifndef REDBLACKTREE_TREE_HPP
#define REDBLACKTREE_TREE_HPP

#include <iostream>
typedef struct branch
{
	int 			data;
	bool 			isRed;
	struct branch	*left;
	struct branch	*right;
} Branch;

class Tree {
public:
	Tree();
	~Tree();
	void 	insertElement(int newdata);

private:
	Branch*	_branch;

	//-----internal mechanic for insertElement()------
	Branch*	_createElement(int newdata);
	void 	_addElement(int newdata, Branch*& aBranch);
	//-------------------------------------------------
};


#endif //REDBLACKTREE_TREE_HPP
