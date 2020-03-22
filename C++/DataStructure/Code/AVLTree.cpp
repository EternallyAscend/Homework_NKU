#include<iostream>
#include<stdlib.h>
using namespace std;
class AVLNode {
	friend class avlt;
private:
	int value;
	int height;
	AVLNode *left;
	AVLNode *right;
	AVLNode *parent;
public:
	AVLNode(int value,AVLNode *parent):value(value),height(1),left(nullptr),right(nullptr),parent(parent){}
	~AVLNode() { left = right = parent = nullptr; }
	void checkHeight() {
		int l = 0;
		int r = 0;
		if (this->left != nullptr) { l = this->left->height; }
		if (this->right != nullptr) { r = this->right->height; }
		this->height = l > r ? l + 1 : r + 1;
	}
	void Ascend() {
		this->checkHeight();
		if (this->parent != nullptr) { this->parent->Ascend(); }
	}
	void vlr() {
		cout << this->value << " ("<<this->height<<") ";
		if (this->left != nullptr) { this->left->vlr(); }
		if (this->right != nullptr) { this->right->vlr(); }
	}
	void deleteNodes() {
		if (this->left != nullptr) { this->left->deleteNodes(); }
		if (this->right != nullptr) { this->right->deleteNodes(); }
		delete this;
	}
};
class avlt {
	friend class AVLNode;
private:
	AVLNode *root;
public:
	avlt():root(nullptr){}
	~avlt() { if (this->root != nullptr) { this->root->deleteNodes(); } }
	void insert(int value) {
		if (this->root == nullptr) { this->root = new AVLNode(value, nullptr); return; }
		else {
			AVLNode *temp = this->root;
			while (1) {
				if (temp->value > value) {
					if (temp->left != nullptr) { temp = temp->left; }
					else { temp->left = new AVLNode(value, temp); break; }
				}
				else {
					if (temp->right != nullptr) { temp = temp->right; }
					else { temp->right = new AVLNode(value, temp); break; }
				}
			}
			temp->Ascend();
			while (temp != nullptr) { temp = balanceCheck(temp); }
		}
	}
	void del(int value) {
		AVLNode *deleteNode = search(value) ;
		if (deleteNode == nullptr) { return; }
		else {
			bool leftSon = false;
			bool rightSon = false;
			if (deleteNode->left != nullptr) { leftSon = true; }
			if (deleteNode->right != nullptr) { rightSon = true; }
			if (leftSon || rightSon) {
				AVLNode* exchange = nullptr;
				if(!leftSon){
					exchange = deleteNode->right;
					deleteNode->value = exchange->value;
					deleteNode->right = nullptr;
				}
				if (!rightSon) {
					exchange = deleteNode->left;
					deleteNode->value = exchange->value;
					deleteNode->left = nullptr;
				}
				if (leftSon&&rightSon) {
					exchange = deleteNode->right;
					while (exchange->left != nullptr) { exchange = exchange->left; }
					deleteNode->value = exchange->value;
					if (exchange->parent->left == exchange) { exchange->parent->left = exchange->right; }
					if (exchange->parent->right == exchange) { exchange->parent->right = exchange->right; }
					if (exchange->right != nullptr) { exchange->right->parent = exchange->parent; }
					deleteNode = exchange->parent;
				}
				delete exchange;
				deleteNode->Ascend();
				while (deleteNode != nullptr) { deleteNode = balanceCheck(deleteNode); }
			}
			else {
				if (deleteNode->parent == nullptr) { this->root = nullptr; return; }
				else {
					if (deleteNode->parent->left == deleteNode) { deleteNode->parent->left = nullptr; }
					if (deleteNode->parent->right == deleteNode) { deleteNode->parent->right = nullptr; }
				}
				AVLNode *temp = deleteNode->parent;
				delete deleteNode;
				temp->Ascend();
				while (temp != nullptr) { temp = balanceCheck(temp); }
			}
		}
	}
	void output() { if (this->root != nullptr) { this->root->vlr(); cout << endl; } }
	AVLNode* search(int value) {
		if (this->root == nullptr) { return nullptr; }
		else {
			AVLNode *temp = this->root;
			while (temp != nullptr) {
				if (temp->value == value) { break; }
				if (temp->value > value) { temp = temp->left; }
				if (temp == nullptr) { break; }
				if (temp->value < value) { temp = temp->right; }
			}
			return temp;
		}
	}
	AVLNode* balanceCheck(AVLNode* Node){
		int l, r, sl, sr;
		l = r = sl = sr = 0;
		AVLNode* check = Node->parent;
		AVLNode* NodeParent = Node->parent;
		if (Node->left != nullptr) { l = Node->left->height; }
		if (Node->right != nullptr) { r = Node->right->height; }
		if (l - r == 2) {
			if (Node->left->left != nullptr) { sl = Node->left->left->height; }
			if (Node->left->right != nullptr) { sr = Node->left->right->height; }
			if (sl >= sr) { check=LL(Node);}
			else { check=LR(Node);}
		}
		if (l - r == -2) {
			if (Node->right->left != nullptr) { sl = Node->right->left->height; }
			if (Node->right->right != nullptr) { sr = Node->right->right->height; }
			if (sr >= sl) { check=RR(Node);}
			else { check=RL(Node);}
		}
		return check;
		//return NodeParent;
	}
	AVLNode* LL(AVLNode* Node) {
		AVLNode* temps = Node->left;
		if (Node->parent == nullptr) { this->root = temps; }
		else {
			if (Node->parent->left == Node) { Node->parent->left = temps; }
			else { Node->parent->right = temps; }
		}
		temps->parent = Node->parent;
		Node->left = temps->right;
		if (temps->right != nullptr) { temps->right->parent = Node; }
		temps->right = Node;
		Node->parent = temps;
		Node->Ascend();
		return temps;
	}
	AVLNode* LR(AVLNode* Node) {
		AVLNode* tempss = Node->left->right;
		if (Node->parent == nullptr) { this->root = tempss; }
		else {
			if (Node->parent->left == Node) { Node->parent->left = tempss; }
			else { Node->parent->right = tempss; }
		}
		tempss->parent = Node->parent;
		Node->left->right = tempss->left;
		if (tempss->left != nullptr) { tempss->left->parent = Node->left; }
		tempss->left = Node->left;
		Node->left->parent = tempss;
		Node->left = tempss->right;
		if (tempss->right != nullptr) { tempss->right->parent = Node; }
		tempss->right = Node;
		Node->parent = tempss;
		tempss->left->Ascend();
		Node->Ascend();
		return tempss;
	}
	AVLNode* RL(AVLNode* Node) {
		AVLNode* tempss = Node->right->left;
		if (Node->parent == nullptr) { this->root = tempss; }
		else {
			if (Node->parent->left == Node) { Node->parent->left = tempss; }
			else { Node->parent->right = tempss; }
		}
		tempss->parent = Node->parent;
		Node->right->left = tempss->right;
		if (tempss->right != nullptr) { tempss->right->parent = Node->right; }
		tempss->right = Node->right;
		Node->right->parent = tempss;
		Node->right = tempss->left;
		if (tempss->left != nullptr) { tempss->left->parent = Node; }
		tempss->left = Node;
		Node->parent = tempss;
		tempss->right->Ascend();
		Node->Ascend();
		return tempss;
	}
	AVLNode* RR(AVLNode* Node) {
		AVLNode* temps = Node->right;
		if (Node->parent == nullptr) { this->root = temps; }
		else {
			if (Node->parent->left == Node) { Node->parent->left = temps; }
			else { Node->parent->right = temps; }
		}
		temps->parent = Node->parent;
		Node->right = temps->left;
		if (temps->left != nullptr) { temps->left->parent = Node; }
		temps->left = Node;
		Node->parent = temps;
		Node->Ascend();
		return temps;
	}
};
int main(void) {
	int n, m;
	avlt tree;
	cin >> n;
	for (int i = 0; i < n; i++) { cin >> m; tree.insert(m); }
	for (int i = 0; i < n; i++) { cin >> m; tree.del(m); }
	system("pause");
	return 0;
}
