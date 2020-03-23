#include<iostream>
#include<string>
using namespace std;
class HuffmanStack;
string bin(int value, int length) {
	string temp;
	while (value / 2) {
		temp.push_back(value % 2 + 48);
		value /= 2;
	}
	temp.push_back(value + 48);
	string ans;
	if (temp.length() < length) {
		for (int i = 0; i < length - temp.length(); i++) {
			ans.push_back('0');
		}
	}
	for (int i = 0; i < temp.length(); i++) {
		ans.push_back(temp[(temp.length() - i - 1)]);
	}
	return ans;
}
class node {
	friend class Huffman;
	friend class HuffmanStack;
private:
	char c;
	int length;
	int height;
	string code;
	node *left;
	node *right;
public:
	void vlr() {
		cout << this->c << " " << this->length << " " << this->height << endl;
		if (this->left != NULL) {
			this->left->vlr();
		}
		if (this->right != NULL) {
			this->right->vlr();
		}
	}
	node();
	node(int length,int height);
	node(char c, int length);
	~node();
	node* operator+(node *add) {
		node *temp;
		int height = this->height > add->height ? this->height : add->height;
		temp = new node(this->length + add->length, height + 1);
			if (this->length > add->length) {
				temp->left = add;
				temp->right = this;
			}
			else {
				temp->left = this;
				temp->right = add;
			}
		return temp;
	}
	void refreshHeight() {
		if (this->left != NULL) {
			this->left->height = this->height + 1;
			this->left->refreshHeight();
		}
		if (this->right != NULL) {
			this->right->height = this->height + 1;
			this->right->refreshHeight();
		}
	}
};
class Huffman {
	friend class node;
	friend class HuffmanStack;
private:
	int size;
	int tail;
	node **list;
	HuffmanStack *Stack;
public:
	Huffman();
	Huffman(int size);
	~Huffman();
	void newNode(char c,int length);
	void output();
	void create();
	void sort();
	void code(node *Node);
};
class HuffmanStack {
	friend class node;
	friend class Huffman;
private:
	node **list;
	int size;
	int tail;
	int head;
public:
	HuffmanStack();
	HuffmanStack(int size);
	~HuffmanStack();
	bool push(node *Node);
	node* pop();
	bool isNotEmpty();
};
//************************************************* Hufnode ****************************************//
node::node() {

}
node::node(int length, int height) {
	c = ' ';
	this->length = length;
	this->height = height;
}
node::node(char c, int length) {
	this->c = c;
	this->length = length;
	this->height = 1;
}
node::~node() {

}
//************************************************* Huffman ****************************************//
Huffman::Huffman() {

}
Huffman::Huffman(int size) {
	tail = 0;
	this->size = size;
	list = new node*[size];
}
Huffman::~Huffman() {
	delete[]list;
}
void Huffman::newNode(char c, int length) {
	list[tail++] = new node(c, length);
}
void Huffman::output() {
	this->list[0]->height = 0;
	this->list[0]->refreshHeight();
	Stack = new HuffmanStack(size * size);
	Stack->push(this->list[0]);
	node* temp;
	bool start=false;
	int height = 0;
	int value = 0;
	while (Stack->isNotEmpty()) {
		temp = Stack->pop();
		if (temp->left != NULL) {
			Stack->push(temp->left);
		}
		if (temp->right != NULL) {
			Stack->push(temp->right);
		}
		if (temp->c != ' '&&start) {
			if (temp->height > height) {
				if (value != 0) {
					value--;
					value = 2 * (value + 1);
				}
			height = temp->height;
			}
			cout << ";" << temp->c << ":" << bin(value,height);
			value++;
		}
		if (temp->c != ' '&&!start) {
			if (temp->height > height) {
				if (value != 0) {
					value--;
					value = 2 * (value + 1);
				}
			height = temp->height;
			}
			cout << temp->c << ":" << bin(value,height);
			value++;
			start = true;
		}
	}
}
void Huffman::create() {
	sort();
	while (tail > 1) {
		node* temp = list[tail - 2];
		list[tail - 2] = *temp + list[tail - 1];
		tail--;
		sort();
	}
}
void Huffman::sort() {
	for (int i = 0; i < tail; i++) {
		for (int j = 0; j < tail - 1; j++) {
			if (list[j]->length < list[j + 1]->length) {
				node* temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}
void Huffman::code(node *Node) {
	if (Node->left != NULL) {
		for (int i = 0; i < Node->code.length(); i++) {
			Node->left->code.push_back(Node->code[i]);
		}
		Node->left->code.push_back('0');
		code(Node->left);
	}
	if (Node->right != NULL) {
		for (int i = 0; i < Node->code.length(); i++) {
			Node->right->code.push_back(Node->code[i]);
		}
		Node->right->code.push_back('1');
		code(Node->right);
	}
}
//*************************************************************** Huffman Stack ************************
HuffmanStack::HuffmanStack() {

}
HuffmanStack::HuffmanStack(int size) {
	this->size = size;
	head = tail = 0;
	list = new node*[size];
}
HuffmanStack::~HuffmanStack() {

}
bool HuffmanStack::push(node* Node) {
	list[tail++] = Node;
	if (tail + 1 == size) {
		if (head != 0) {
			tail = 0;
		}
		else {
			HuffmanStack *temp;
			temp = new HuffmanStack(size);
			for (int i = 0; i < size; i++) {
				temp->list[i] = list[i];
			}
			delete[]this->list;
			this->list = new node*[size * 2];
			for (int i = 0; i < size; i++) {
				list[i] = temp->list[i];
			}
			delete[]temp;
			this->size *= 2;
		}
	}
	if (tail + 1 == head) {
		HuffmanStack *temp;
		temp = new HuffmanStack(size);
		for (int i = head; i < size; i++) {
			temp->list[i - head] = list[i];
		}
		for (int i = 0; i <= tail; i++) {
			temp->list[size - head + i] = list[i];
		}
		delete[]this->list;
		this->list = new node*[size * 2];
		for (int i = 0; i < size; i++) {
			list[i] = temp->list[i];
		}
		head = 0;
		tail = size - 1;
		delete[]temp;
		this->size *= 2;
	}
	return true;
}
node* HuffmanStack::pop() {
	if (head == tail) {
		return NULL;
	}
	if (head + 1 == size) {
		int temp = head;
		head = 0;
		return list[temp];
	}
	return list[head++];
}
bool HuffmanStack::isNotEmpty() {
	if (head == tail) {
		return false;
	}
	return true;
}
// ************************************ main ************************************************
int main(void) {
	int n, length;
	char c;
	cin >> n;
	Huffman tree(n);
	for (int i = 0; i < n; i++) {
		cin >> c >> length;
		tree.newNode(c,length);
	}
	tree.create();
	tree.output();
	return 0;
}
