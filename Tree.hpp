
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
	Branch*	createElement(int newdata);
	void 	addElement(int newdata);
private:
	Branch*	_branch;

};


#endif //REDBLACKTREE_TREE_HPP
