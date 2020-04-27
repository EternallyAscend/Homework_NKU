/*
Problem description
Imagine:

There are n bookstores located in your area and you want to visit all of them.
Each bookstore can be reached via another bookstore.
Every path has a positive distance (>0).
The sum of the distances of all chosen paths must be minimal.
Please find out the minimum sum of distances of the paths that connect all bookstores.
Input
The first line is an integer n  (n < 100) ,indicating how many bookstores are in your area.
The following n lines are the adjacency matrix of the undirected graph consists of all bookstores.
Output
The minimum sum of distances of the paths that connect all bookstores.
Annex

Sample of Input and Output
样例1
Input:
4
0 2 4 0
2 0 3 5
4 3 0 1
0 5 1 0
Output:
6
您所在地区有n家书店，您想参观所有这些书店。
每个书店都可以通过另一家书店到达。
每个路径的距离都为正值（> 0）。
所有选定路径的距离之和必须最小。
请找出连接所有书店的路径的最小距离总和。
输入值
第一行是整数n（n <100），表示您所在地区有多少家书店。
以下n行是由所有书店组成的无向图的邻接矩阵。
输出量
连接所有书店的路径的最小距离总和。
*/


#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<iostream>
using namespace std;
class minHeap {
private:
	// int head;
	int tail;
	int edges;
	int *left;
	int *right;
	int *length;
public:
	minHeap(int Edges) {
		// this->head = 0;
		this->tail = 0;
		this->edges = Edges;
		this->left = (int*)malloc(this->edges * sizeof(int));
		this->right = (int*)malloc(this->edges * sizeof(int));
		this->length = (int*)malloc(this->edges * sizeof(int));
	}
	~minHeap() {
		free(this->left);
		free(this->right);
		free(this->length);
	}
	void insert(int left, int right, int length) {
		this->left[tail] = left;
		this->right[tail] = right;
		this->length[tail++] = length;
		// Adjust Tail; Order by length.
		int pos = tail - 1;
		while (pos > 0) {
			if (this->length[pos] < this->length[(pos - 1) / 2]) {
				exchange(pos, (pos - 1) / 2);
				pos = (pos - 1) / 2;
			}
			else {
				break;
			}
		}
		// this->show();
	}
	vector<int> pop() {
		vector<int> temp;
		if (this->isEmpty()) {
			temp.assign(3, 0);
		}
		temp.push_back(left[0]);
		temp.push_back(right[0]);
		temp.push_back(length[0]);
		// Adjust Top.
		this->drop(0);
		/*
		for (int i = 0; i < 3; i++) {
			cout << temp[i] << " ";
		}
		cout << endl;
		this->show();
		*/
		return temp;
	}
	bool isEmpty() {
		if (this->tail == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	void exchange(int left, int right) {
		int temp;
		temp = this->left[left];
		this->left[left] = this->left[right];
		this->left[right] = temp;
		temp = this->right[left];
		this->right[left] = this->right[right];
		this->right[right] = temp;
		temp = this->length[left];
		this->length[left] = this->length[right];
		this->length[right] = temp;
	}
	void show() {
		printf("\nShow ");
		int i;
		for (i = 0; i < this->tail; i++) {
			printf("%d ", this->length[i]);
		}
		printf("\n");
	}
	void extend() {
		int i;
		int *lef;
		int *rig;
		int *len;
		lef = (int*)malloc(this->edges * sizeof(int));
		rig = (int*)malloc(this->edges * sizeof(int));
		len = (int*)malloc(this->edges * sizeof(int));
		for (i = 0; i < this->edges; i++) {
			lef[i] = this->left[i];
			rig[i] = this->right[i];
			len[i] = this->length[i];
		}
		free(this->left);
		free(this->right);
		free(this->length);
		this->left = (int*)malloc(this->edges * 2 * sizeof(int));
		this->right = (int*)malloc(this->edges * 2 * sizeof(int));
		this->length = (int*)malloc(this->edges * 2 * sizeof(int));
		for (i = 0; i < this->edges; i++) {
			this->left[i] = lef[i];
			this->right[i] = rig[i];
			this->length[i] = len[i];
		}
		free(lef);
		free(rig);
		free(len);
		this->edges = this->edges * 2;
	}
	void dropRightNode(int node) {
		int i;
		int deleteCounter = 0;
		for (i = 0; i < this->tail; i++) {
			if (this->right[i] == node) {
				deleteCounter++;
			}
		}
		if (deleteCounter > 0) {
			for (i = 0; i < this->tail - deleteCounter; i++) {
				while (this->right[i] == node) {
					this->drop(i);
				}
			}
		}
		this->tail = this->tail - deleteCounter;
		//this->show();
	}
	void drop(int position) {
		this->tail--;
		this->left[position] = this->left[tail];
		this->right[position] = this->right[tail];
		this->length[position] = this->length[tail];
		int pos = position;
		while (pos < this->tail) {
			int left;
			int right;
			bool rightExist = false;
			if (pos * 2 + 2 < this->tail) {
				rightExist = true;
				right = this->length[pos * 2 + 2];
			}
			if (pos * 2 + 1 < this->tail) {
				left = this->length[pos * 2 + 1];
			}
			else {
				break;
			}
			if (rightExist) {
				if (left <= right) {
					if (left < this->length[pos]) {
						this->exchange(pos, pos * 2 + 1);
						pos = pos * 2 + 1;
						continue;
					}
				}
				else {
					if (right < this->length[pos]) {
						this->exchange(pos, pos * 2 + 2);
						pos = pos * 2 + 2;
						continue;
					}
				}
			}
			else {
				if (left < this->length[pos]) {
					exchange(pos, pos * 2 + 1);
					pos = pos * 2 + 1;
					continue;
				}
			}
			break;
		}
	}
};
class mapNode {
private:
	int id;
	vector<int> reachedIdList;
	vector<int> reachedLength;
public:
	mapNode(int ID) {
		this->id = ID;
	}
	void connect(int id, int length) {
		this->reachedIdList.push_back(id);
		this->reachedLength.push_back(length);
	}
	vector<int> getReachedIdList() {
		return this->reachedIdList;
	}
	vector<int> getReachedLength() {
		return this->reachedLength;
	}
};
class map {
private:
	vector<mapNode*> list;
	int nodeNum;
	int left;
	int right;
	int length;
	bool* reached;
public:
	map(int nodeNumbers) {
		this->nodeNum = nodeNumbers;
		int i;
		for (i = 0; i < this->nodeNum; i++) {
			this->list.push_back(new mapNode(i));
			//this->list[i] = new mapNode(i);
		}
		this->left = -1;
		this->right = -1;
		this->length = -1;
	}
	~map() {
		int i;
		for (i = 0; i < this->list.size(); i++) {
			delete list[i];
		}
	}
	void getMin(int Left, int Right, int Length) {
		if (this->length > Length || this->length == -1) {
			this->left = Left;
			this->right = Right;
			this->length = Length;
		}
	}
	void connectSingle(int Left, int Right, int Length) {
		this->getMin(Left, Right, Length);
		this->list[Left]->connect(Right, Length);
	}
	void connectTwoWay(int Left, int Right, int Length) {
		this->getMin(Left, Right, Length);
		this->list[Left]->connect(Right, Length);
		this->list[Right]->connect(Left, Length);
	}
	int getMinLength() {
		minHeap pool(this->nodeNum*(this->nodeNum - 1));
		this->reached = (bool*)malloc(this->nodeNum * sizeof(bool));
		int i;
		for (i = 0; i < this->nodeNum; i++) {
			this->reached[i] = false;
		}

		this->reached[this->left] = true;
		this->reached[this->right] = true;

		vector<int> reachNode = this->list[this->left]->getReachedIdList();
		vector<int> reachLength = this->list[this->left]->getReachedLength();
		for (i = 0; i < reachNode.size(); i++) {
			if (!reached[reachNode[i]]) {
				pool.insert(this->left, reachNode[i], reachLength[i]);
			}
		}

		reachNode = this->list[this->right]->getReachedIdList();
		reachLength = this->list[this->right]->getReachedLength();
		for (i = 0; i < reachNode.size(); i++) {
			if (!reached[reachNode[i]]) {
				pool.insert(this->right, reachNode[i], reachLength[i]);
			}
		}

		int counter = 2;
		while (counter < this->nodeNum && !pool.isEmpty()) {
			vector<int> temp = pool.pop();
			if (!reached[temp[1]]) {
				reached[temp[1]] = true;
				this->length += temp[2];
				counter++;
				reachNode = this->list[temp[1]]->getReachedIdList();
				reachLength = this->list[temp[1]]->getReachedLength();
				for (i = 0; i < reachNode.size(); i++) {
					if (!reached[reachNode[i]]) {
						pool.insert(temp[1], reachNode[i], reachLength[i]);
					}
				}
			}
		}
		free(this->reached);
		return this->length;
	}
};
int main(void) {
	int nodes;
	int length;
	int i;
	int j;
	scanf("%d", &nodes);
	map distributedMap(nodes);
	for (i = 0; i < nodes; i++) {
		for (j = 0; j < nodes; j++) {
			scanf("%d", &length);
			if (length && i != j) {
				distributedMap.connectSingle(i, j, length);
			}
		}
	}
	length = distributedMap.getMinLength();
	printf("%d", length);
	system("pause");
	return 0;
}

/*
int main(void) {
	int nodes;
	int length;
	int i;
	int lef;
	int rig;
	int lines;
	scanf("%d %d", &nodes, &lines);
	map distributedMap(nodes);
	for (i = 0; i < lines; i++) {
		scanf("%d %d %d", &lef, &rig, &length);
		// distributedMap.connectSingle(lef-1, rig-1, length);
		distributedMap.connectTwoWay(lef - 1, rig - 1, length);
	}
	length = distributedMap.getMinLength();
	printf("%d", length);
	system("pause");
	return 0;
}
*/
