#include<iostream>
#include<string>
#include<cmath>
using namespace std;
int strToInt(string str) {
	int ans = 0;
	for (int i = str.length() - 1; i >= 0; i--) {
		ans += (str[i] - 48) * (pow(10, str.length() - i - 1));
	}
	return ans;
}
//*********************************** node **************************************
class node {
	friend class map;
private:
	int sort;
	int inDegree;
	int outDegree;
	int minTime;//Earliest Start Time
	int maxTime;//Latest Start Time
	int time;// Waste

	int parentSize;
	int parentNumber;
	node **parent;

	int childSize;
	int childNumber;
	node **child;
public:
	node();
	~node();
	void connectParent(node* Number);
	node** expand(node **list, int& number);
};
node::node():inDegree(0),outDegree(0),minTime(-1),maxTime(65535),parentSize(16),parentNumber(0),childSize(16),childNumber(0),time(0){
	parent = new node*[parentSize];
	child = new node*[childSize];
}
node::~node(){}
void node::connectParent(node* Number){
	Number->child[Number->childNumber++] = this;
	if (Number->childNumber == Number->childSize) { Number->child = Number->expand(Number->child, Number->childSize); }
	this->parent[this->parentNumber++] = Number;
	if (this->parentNumber == this->parentSize) { this->parent = this->expand(this->parent, this->parentSize); }
	Number->outDegree++;
	this->inDegree++;
}
node** node::expand(node **list, int& number) {
	node **temp = new node*[number];
	for (int i = 0; i < number; i++) {temp[i] = list[i];}
	delete[]list;
	list = new node*[number * 2];
	for (int i = 0; i < number; i++) {list[i] = temp[i];}
	number *= 2;
	return list;
}
//************************************* map ************************************
class map {
	friend class node;
private:
	int size;
	node *start;
	node *end;
	node **list;
public:
	map();
	map(int size);
	~map();
	node* create(int pos, int value);
	node* find(int pos);
	int path();
	void checkFront(node *Node);
	void checkBack(node *Node);
	void output() {
		for (int i = 0; i < size; i++) {
			cout << i+1 << " " << list[i]->time <<" "<<list[i]->inDegree<<" "<<list[i]->outDegree<< endl ;
			for (int j = 0; j < list[i]->parentNumber; j++) {
				cout <<"parent "<< list[i]->parent[j]->time << " ";
			}
			cout << endl;
			for (int j = 0; j < list[i]->childNumber; j++) {
			cout << "child ";
				cout << list[i]->child[j]->time << " ";
			}
			cout << endl;
		}
	}
};
map::map(){}
map::map(int size) :size(size){
	this->list = new node*[size];
	for (int i = 0; i < size; i++) {
		list[i] = new node;
	}
}
map::~map() {
	for (int i = 0; i < size; i++) {if (this->list[i] != NULL) { delete this->list[i]; }}
}
node* map::create(int pos, int value) { 
	this->list[pos - 1]->time = value;
	return this->list[pos - 1];
}
node * map::find(int pos){return this->list[pos - 1];}
int map::path() {
	this->start = new node();
	this->end = new node();
	for (int i = 0; i < size; i++) {
		this->list[i]->sort = this->list[i]->inDegree;
		if (this->list[i]->inDegree == 0) {
			this->list[i]->connectParent(start);
			list[i]->inDegree = 0;
		}
		if (this->list[i]->outDegree == 0) {
			end->connectParent(this->list[i]);
		}
	}
	for (int i = 0; i < this->size - 1;) {
		bool check = true;
		for (int j = 0; j < this->size; j++) {
			if (this->list[j]->sort == 0) {
				i++;
				check = false;
				for (int k = 0; k < this->list[j]->childNumber; k++) {
					this->list[j]->child[k]->sort--;
				}
				this->list[j]->sort = -1;
			}
		}
		if (check) return -1;
	}
	this->start->minTime = this->start->maxTime = 0;
	checkFront(this->start);
	checkBack(this->end);
	return this->end->minTime;
}
void map::checkFront(node *Node) {
	for (int i = 0; i < Node->parentNumber; i++) {if (Node->minTime < Node->parent[i]->time + Node->parent[i]->minTime) {	Node->minTime = Node->maxTime = Node->parent[i]->time + Node->parent[i]->minTime;}}
	for (int i = 0; i < Node->childNumber;i++) { checkFront(Node->child[i]); }
}
void map::checkBack(node *Node) {
	for (int i = 0; i < Node->childNumber;i++) {if (Node->maxTime > Node->child[i]->maxTime - Node->time) {	Node->maxTime = Node->child[i]->maxTime - Node->time;}}
	for (int i = 0; i < Node->parentNumber; i++) { checkBack(Node->parent[i]); }
}
//************************************ main ************************************
int main(void) {
	//The ";" is the same as the value of 59.//cout << (int)';' << endl;
	int n , m, t;
	cin >> n;
	map ans(n);
	for (int i = 0; i < n; i++) {
		cin >> m >> t;
		node *temp = ans.create(m, t);
		string line;
		getline(cin,line);
		int start, end;
		start = end = 1;
			for (end = start; end < line.length(); end++) {
				if ((int)line[end] == 59) {
					string cache;
					for (int k = start; k < end; k++) {
						cache.push_back(line[k]);
					}
					temp->connectParent(ans.find(strToInt(cache)));
					start = end + 1;
				}
			}
	}
	//cout << ans.path() << endl;
	int result = ans.path();
	if (result == -1)cout << "error";
	else cout << result;
	system("pause");
	return 0;
}
/*
工程规划
Total number of submissions: 1068 timespassing number: 1 timesPassing rate: 0.09%
Memory limit: 62914560(BYTE)Time limit: 10000(MS)Input limit: 1000(ROWS)Output limit: 64(ROWS)
Problem description
工程可以分为N个阶段。每个阶段都可以并行，但是有依赖关系。试计算工程的最短消耗时间。
程序输入格式：输入第一个为整数N，代表阶段个数，随后输入N行，分表包含阶段编号、耗时，以及依赖关系，不同依赖使用";"分割。
程序输出格式：工程的最短消耗时间，如果不为无环图输出error
输入样例：
4
1 3
2 4
3 5 1;2;
4 3 3;
输出样例：
12
样例2
Input:
4
1 3
2 4 3;
3 5 1;2;
4 3 3;
Output:
error
*/