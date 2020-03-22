#include<iostream>
using namespace std;
class binaryTreeNode {
private:
	int number;
	int count;
	binaryTreeNode* left;
	binaryTreeNode* right;
	binaryTreeNode* parent;
public:
	binaryTreeNode(int number,binaryTreeNode *parent);
	~binaryTreeNode();
	int getValue();
	binaryTreeNode* getLeft();
	binaryTreeNode* getRight();
	binaryTreeNode* newLeft(int value);
	binaryTreeNode* newRight(int value);
	void counter();
	void decrease();
	int getCount();
	void addRight();
	void check();
	void lvr();
};
binaryTreeNode::binaryTreeNode(int number,binaryTreeNode *parent):number(number),parent(parent),count(0),left(NULL),right(NULL) {}
binaryTreeNode::~binaryTreeNode() {
	if (this->left != NULL) { delete this->left; }
	if (this->right != NULL) { delete this->right; }
}
int binaryTreeNode::getValue() { return this->number; }
binaryTreeNode* binaryTreeNode::getLeft() { return this->left; }
binaryTreeNode* binaryTreeNode::getRight() { return this->right; }
binaryTreeNode* binaryTreeNode::newLeft(int value) { 
	this->left = new binaryTreeNode(value, this);
	return this->left;
}
binaryTreeNode* binaryTreeNode::newRight(int value) { 
	this->right = new binaryTreeNode(value, this);
	return this->right; 
}
void binaryTreeNode::counter() { this->count++; }
void binaryTreeNode::decrease() { this->count--; }
int binaryTreeNode::getCount() { return this->count; }
void binaryTreeNode::lvr() {
	if (this->left != NULL) { this->left->lvr(); }
	cout << this->number << " " << this->count << endl;
	if (this->right!= NULL) { this->right->lvr(); }
}
void binaryTreeNode::addRight() {
	if (this->left != NULL) {
		this->left->addRight();
	}
	if (this->right != NULL) {
		this->right->addRight();
	}
	this->count++;
}
void binaryTreeNode::check() {
	if (this->parent != NULL) {
		if (this->parent->left!=NULL &&this->parent->left->number == this->number) {
			this->parent->counter();
		}
		this->parent->check();
	}
	return;
}
class binaryTree {
private:
	binaryTreeNode* root;
	bool isEmpty;
public:
	binaryTree();
	~binaryTree();
	binaryTreeNode* insert(int value);
	binaryTreeNode* getRoot();
};
binaryTree::binaryTree():root(NULL),isEmpty(true){}
binaryTree::~binaryTree() { 
	if (this->root != NULL) {
		delete root;
	}
}
binaryTreeNode* binaryTree::insert(int value) {
	if (this->isEmpty) {
		this->root = new binaryTreeNode(value, NULL);
		this->isEmpty = false;
		return this->root;
	}
	bool leftPos=false;
//	bool equal = false;
	binaryTreeNode* cache = this->root;
	binaryTreeNode* temp = this->root;
	while (temp!=NULL) {
		cache = temp;
		if (temp->getValue() < value) {
			temp = temp->getRight();
			leftPos = false;
		}
		else {
			if (temp->getValue() == value) {
				temp->decrease();
			}
			if (temp->getRight() != NULL) {
				temp->getRight()->addRight();
			}
			temp = temp->getLeft();
			leftPos = true;
		}
	}
	if (leftPos) {
		temp = cache->newLeft(value);
	}
	else {
		temp = cache->newRight(value);
	}
	temp->check();
	return temp;
}
binaryTreeNode* binaryTree::getRoot() { return this->root; }
int main(void) {

	int n;
	cin >> n;
	binaryTreeNode** list = new binaryTreeNode*[n];
	binaryTree tree;
	for (int i = 0; i < n; i++) {
		int value;
		cin >> value;
		list[i] = tree.insert(value);
	}
	for (int i = 0; i < n; i++) {
		cout<<list[i]->getCount()<<endl;
	}
	return 0;
}
