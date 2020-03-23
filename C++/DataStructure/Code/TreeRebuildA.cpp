#include<iostream>
#include<string>
using namespace std;
class node {
private:
	char value;
	node *left;
	node *right;
	node *parent;
public:
	node();
	node(char value, node* parent);
	~node();
	node* getLeft();
	node* getRight();
	node* getParent();
	bool newLeft(char value);
	bool newRight(char value);
	void vlr();
	void lvr();
	void lrv();
};
node::node() {
	this->value = 0;
	this->left = NULL;
	this->right = NULL;
	this->parent = NULL;
}
node::node(char value,node* parent) {
	this->value = value;
	this->left = NULL;
	this->right = NULL;
	this->parent = parent;
}
node::~node() {

}
node* node::getLeft() {
	return this->left;
}
node* node::getRight() {
	return this->right;
}
node* node::getParent() {
	return this->parent;
}
bool node::newLeft(char value) {
	this->left = new node(value, this);
	return true;
}
bool node::newRight(char value) {
	this->right = new node(value, this);
	return true;
}

class binTree {
private:
	node *root;
	int floor;
public:
	binTree();
	binTree(int floor);
	binTree(int floor, char value);
	~binTree();
	node* getRoot();
};
binTree::binTree() {
	this->root = NULL;
	this->floor = 0;
}
binTree::binTree(int floor) {
	this->root = new node();
	this->floor = floor;
}
binTree::binTree(int floor, char value) {
	this->root = new node(value,NULL);
	this->floor = floor;
}
binTree::~binTree() {

}
node* binTree::getRoot() {
	return this->root;
}
void node::vlr() {
	cout << this->value << " ";
	if (this->left != NULL) {
		(this->left)->vlr();
	}
	if (this->right != NULL) {
		(this->right)->vlr();
	}
}
void node::lvr() {
	if (this->left != NULL) {
		(this->left)->lvr();
	}
	cout << this->value << " ";
	if (this->right != NULL) {
		(this->right)->lvr();
	}
}
void node::lrv() {
	if (this->left != NULL) {
		cout << "left" << endl;
		(this->left)->lrv();
	}
	if (this->right != NULL) {
		cout << "right" << endl;
		(this->right)->lrv();
	}
	cout << this->value << " ";
}
bool build(int& i, string& value, node * myself,int maxsize) {
	if (i > maxsize - 1) {
		return false;
	}
	if (value[i] != '#') {
		myself->newLeft(value[i]);
		i++;
		if (i <= maxsize - 1) {
			build(i, value, myself->getLeft(), maxsize);
		}
	}
	if (i > maxsize - 1) {
		return false;
	}
	if (value[i] == '#') {
		i++;
	}
	if (i > maxsize - 1) {
		return false;
	}
	if (value[i] != '#') {
		myself->newRight(value[i]);
		i++;
		if (i <= maxsize - 1) {
			build(i, value, myself->getRight(), maxsize);
		}		
	}
	if (i > maxsize - 1) {
		return false;
	}
	return true;
}
int main(void) {
	string vlr;
	cin >> vlr;
	int i;
	i = 1;
	int &j = i;
	binTree test(vlr.length(), vlr[0]);
	build(j, vlr, test.getRoot(),vlr.length());
	test.getRoot()->lvr();
	//system("pause");
	return 0;
}

//  ABDG##H###CE#I##F##

/*
ÑùÀý1
Input:
ABDG##H###CE#I##F##
Output:
G D H B A E I C F
ÑùÀý2
Input:
ach##id#j###wy##qs#x##
Output:
h c d j i a y w s x q
ÑùÀý3
Input:
&!#fae###c#g##*$+###@##
Output:
! e a f c g & + $ * @
*/
