#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
class node {
	friend class disktree;
private:
	string name;
	node *parent;
	node **child;
	int height;
	int tail;
	int size;
public:
	node();
	node(string name, node* parent);
	~node();
	void expand();
	node* insert(string name);
	void sort();
	void output();
	node* find(string name);
};
class disktree {
	friend class node;
private:
	int tail;
	node *root;
	int total;
	node **point;
public:

	disktree();
	~disktree();
	node* insert(string name, node *parent);
	node* findParent(string name);
	void print();
	node* getRoot() { return this->root; }
};
//************************************* node *******************************************************************
node::node() :tail(0), parent(NULL), size(10) ,height(0){}
node::node(string name, node* parent) : name(name), parent(parent), tail(0), size(10) {
	if (parent != NULL) this->height = parent->height + 1;
	else this->height = 0;
	this->child = new node*[size];
}
node::~node() {}
void node::expand() {
	node** temp;
	temp = new node*[size];
	for (int i = 0; i < this->size; i++) {
		temp[i] = child[i];
	}
	delete[]child;
	child = new node*[size * 2];
	for (int i = 0; i < size; i++) {
		child[i] = temp[i];
	}
	size *= 2;
}
node* node::insert(string childName) {
	node *ans = this->find(childName);
	if (ans != NULL) {
		return ans;
	}
	child[tail++] = new node(childName, this);
	if (tail == size) this->expand();
	return child[tail - 1];
}
void node::sort() {
	for (int i = 0; i < this->tail; i++) {
		for (int j = 0; j < this->tail - 1; j++) {
			int length = child[j]->name.length() < child[j + 1]->name.length() ? child[j]->name.length() : child[j + 1]->name.length();
			bool check = true;
			for (int k = 0; k < length; k++) {
				if (child[j]->name[k] < child[j + 1]->name[k]) {
					check = false;
					break;
				}
				if (child[j]->name[k] > child[j + 1]->name[k]) {
					node *temp;
					temp = child[j];
					child[j] = child[j + 1];
					child[j + 1] = temp;
					check = false;
					break;
				}
			}
			if (child[j]->name.length() > child[j + 1]->name.length() && check) {
				node *temp;
				temp = child[j];
				child[j] = child[j + 1];
				child[j + 1] = temp;
			}
			/*
			if (child[j]->name > child[j + 1]->name) {
				node *temp = child[j];
				child[j] = child[j + 1];
				child[j + 1] = temp;
			}
			*/
		}
	}
	for (int i = 0; i < this->tail; i++) {
		this->child[i]->sort();
	}
}
void node::output() {
	for (int i = 1; i < this->height; i++) {
		cout << " ";
	}
	cout << name << endl;
	if (tail) {
		for (int i = 0; i < this->tail; i++) {
			child[i]->output();
		}
	}
}
node* node::find(string name) {
	node* ans = NULL;
	for (int i = 0; i < this->tail; i++) {
		if (this->child[i]->name == name) {
			ans = this->child[i];
			return ans;
		}
	}
	return ans;
}
//************************************* disk *******************************************************************
disktree::disktree() :tail(0), total(0) {
	this->root = new node();
	this->root->child = new node*[10];
}
disktree::~disktree() {}
node* disktree::insert(string Name, node* Parent) {
	return Parent->insert(Name);
}
node* disktree::findParent(string Name) {
	node* ans = NULL;
	for (int i = 0; i < tail; i++) {
		if (point[i]->name == Name) {
			ans = point[i]->parent;
			break;
		}
	}
	return ans;
}
void disktree::print() {
	this->root->sort();
	for (int i = 0; i < this->root->tail; i++) this->root->child[i]->output();
}
//************************************* main *******************************************************************
int main(void) {
	int n;
	string m;
	disktree ans;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> m;
		int height = 0;
		int head, tail;
		head = tail = 0;
		node* parent = ans.getRoot();
		while (tail != m.length()) {
			for (tail = head; tail < m.length(); tail++) {
				if (m[tail] == '\\') break;
			}
			string name;
			for (head; head < tail; head++) {
				name.push_back(m[head]);
			}
			head++;
			parent = ans.insert(name, parent);
		}
	}
	ans.print();
	system("pause");
	return 0;
}

/*
Sample of Input and Output
ÑùÀý1
Input:
7
WINNT\SYSTEM32\CONFIG
GAMES
WINNT\DRIVERS
HOME
WIN\SOFT
GAMES\DRIVERS
WINNT\SYSTEM32\CERTSRV\CERTCO~1\X86
Output:
GAMES
 DRIVERS
HOME
WIN
 SOFT
WINNT
 DRIVERS
 SYSTEM32
  CERTSRV
   CERTCO~1
	X86
  CONFIG
*/

/*
13
AAAA
AAAA\AAAA
AAA\AA\AAA
A\AAA\AAA
AA\A\AAAA
AAA\A\AAAA
AA\AAA
A\A\A\A
AA\AA\AA\AA
AAA\AAA\AAA\AAA
AAAA\AAAA\AAAA\AAAA
AA\AA\AA
A\AA\A\AA
*/
