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
class node {
	int id;
	vector<int> reachableList;
	vector<int> reachableLength;
public:
	node(int ID) {
		this->id = ID;
	}
	void connect(int ID, int length) {
		//printf("Connect in Node.%d %d\n", ID, length);
		this->reachableList.push_back(ID);
		this->reachableLength.push_back(length);
		for (int i = 0; i < this->reachableLength.size(); i++) {
			// printf("%d %d\n", this->reachableLength[i], this->reachableList[i]);
		}
	}
	int getId() {
		return this->id;
	}
	void showReachable() {
		int i;
		for (i = 0; i < this->reachableLength.size(); i++) {
			printf("%d %d\n", this->reachableList[i], this->reachableLength[i]);
		}
	}
	vector<int> getReachableList() {
		return this->reachableList;
	}
	vector<int> getReachableLength() {
		return this->reachableLength;
	}
};
class map {
	// node **list;
	vector<node*> index;
	int nodes;
	int edges;
	int *before;
	int *distance;
	int length;
	int *line;
public:
	map(int nodes, int edges) {
		// this->index = (node**)malloc(nodes * sizeof(node*));
		// this->list = (node**)malloc(nodes * sizeof(node*));
		int i;
		for (i = 0; i < nodes; i++) {
			this->index.push_back(new node(i + 1));
		}
		this->nodes = nodes;
		this->edges = edges;
	}
	~map() {
		// free(this->list);
		int i;
		for (i = 0; i < nodes; i++) {
			delete (this->index[i]);
		}
		// free(this->index);
	}
	void connect(int left, int right, int length) {
//		printf("Connect. %d %d %d\n", left, right, length);
		this->getNodeByIndex(left)->connect(right, length);
		this->getNodeByIndex(right)->connect(left, length);
	}
	void getDistence(int starts, int end, int& length, vector<int>& result) {
		int start = starts;
		this->before = (int*)malloc(this->nodes * sizeof(int));
		this->distance = (int*)malloc(this->nodes * sizeof(int));
		this->length = -1;
		this->line = (int*)malloc(this->nodes * sizeof(int));
		bool *reached;
		int counter = 1;
		reached = (bool*)malloc(this->nodes * sizeof(bool));
		int i;
		for (i = 0; i < nodes; i++) {
			this->before[i] = -1;
			this->distance[i] = -1;
			this->line[i] = -1;
			reached[i] = false;
		}
		minHeap list(this->edges);
		node* Node = this->getNodeByIndex(start);
		reached[start - 1] = true;
		this->distance[start - 1] = 0;
		vector<int> Right = Node->getReachableList();
		vector<int> Length = Node->getReachableLength();
		for (i = 0; i < Length.size(); i++) {
			list.insert(start, Right[i], Length[i]);
		}
		vector<int> Left;
		while (!list.isEmpty() && counter != this->nodes) {
			Left.clear();
			Right.clear();
			Length.clear();
			Left = list.pop();
			// cout << "pop" << endl;
			start = Left[0];
			Node = this->getNodeByIndex(Left[1]);
			int id = Left[1]; // GetID();
			if (!reached[id - 1] || this->distance[id - 1] > Left[2]) {
				if (!reached[id - 1]) {
					counter++;
				}
				reached[id - 1] = true;
				this->before[id - 1] = start;
				this->distance[id - 1] = Left[2];
				//this->distance[id - 1] = this->distance[start - 1] + Left[2];
				Right = Node->getReachableList();
				Length = Node->getReachableLength();
				for (i = 0; i < Right.size(); i++) {
					if (!reached[Right[i] - 1]) {
						// cout << "Insert " << id << " " << Right[i] << " " << Length[i] << endl;
						list.insert(id, Right[i], this->distance[id - 1] + Length[i]);
						//list.insert(id, Right[i], Length[i]);
					}
				}
			}
			// list.dropRightNode(id);
			//for (int j = 0; j < this->nodes; j++) {
				//cout << reached[j] << endl;
			//}
		}

		counter = 0;
		length = this->distance[end - 1];
		if (length != -1) {
			while (this->before[end - 1] != -1) {
				// cout << "Add " << end << endl;
				result.push_back(end);
				this->line[counter++] = end;
				end = this->before[end - 1];
			}
		}
		this->line[counter] = starts;
		result.push_back(starts);
		/*
		cout << endl << "Line";
		for (; counter != -1; counter--) {
			cout << this->line[counter] << " ";
		}
		cout << endl;
		*/
		// cout << list.isEmpty();
		free(this->before);
		free(this->distance);
		free(this->line);
	}
	/*
	void getDistanceByID() {

	}
	node* getNodeByID(int ID) {
		int i;
		for (i = 0; i < this->nodes; i++) {
			if (this->index[i]->id == ID) {
				return this->index[i];
			}
		}
	}
	void initNodes() {
		int i;
		for (i = 0; i < this->nodes; i++) {
			this->list[i] = new node(-1);
		}
	}
	*/
	node* getNodeByIndex(int Index) {
		return this->index[Index - 1];
	}
	void showID() {
		int i;
		for (i = 0; i < this->nodes; i++) {
			printf("%d ", this->index[i]->getId());
			this->index[i]->showReachable();
		}
	}
};
int main(void) {
	int nodes;
	int edges;
	int start;
	int end;
	scanf("%d %d %d %d", &nodes, &edges, &start, &end);
	// int *edgeList;
	// edgeList = (int*)malloc(edges * 3 * sizeof(int));
	map *maps;
	maps = new map(nodes, edges);
	// maps = (map*)malloc(sizeof(map));
	int i;
	for (i = 0; i < edges; i++) {
		int left;
		int right;
		int length;
		scanf("%d %d %d", &left, &right, &length);
		maps->connect(left, right, length);
		//scanf("%d %d %d", &edgeList[i], &edgeList[i + 1], &edgeList[i + 2]);// node0 node1 and length;
	}
	int length = -1;
	vector<int> path;
	maps->getDistence(start, end, length, path);
	printf("%d\n", length);
	if (length != -1) {
		for (i = path.size() - 1; i != 0; i--) {
			printf("%d ", path[i]);
		}
		printf("%d", path[0]);
	}
	delete maps;
	system("pause");
	return 0;
}

/*
6 8 1 6
1 2 10
1 4 30
1 5 90
2 3 50
3 4 20
3 5 10
4 5 70
5 6 99

Problem description
There are n nodes and m undirected edges in the graph (n < 1000, m < 10000). Each edge has a fixed length. Please find the shortest path between two given nodes sand t in the graph.

Input
The first line has 4 integers: n (the number of nodes), m (the number of edges), s (the ID of the start node), and t (the ID of the destination node).
Each of the following m lines contain 3 integers, the IDs of two nodes, and the length of the edge between these two nodes (each length is greater than 0).

Output
The first line is the length of the shortest path from s to t.
The second line contains the IDs of each node on the shortest path. If there are multiple shortest paths, the one with the smallest lexicographic order is required.

If there is no path from the start node to the destination node, please output -1.

Annex

Sample of Input and Output
样例1
Input:
3 3 1 3
1 3 3
1 2 1
2 3 1
Output:
2
1 2 3

问题描述
图中有n个节点和m个无向边（n <1000，m <10000）。 每个边缘都有固定的长度。 请在图中找到两个给定节点之间的最短路径。

输入值
第一行有4个整数：n（节点数），m（边数），s（起始节点的ID）和t（目标节点的ID）。
接下来的m行中的每行包含3个整数，两个节点的ID以及这两个节点之间的边的长度（每个长度大于0）。

输出量
第一行是从s到t的最短路径的长度。
第二行包含最短路径上每个节点的ID。 如果有多个最短路径，则需要按字典顺序最小的路径。

如果没有从起始节点到目标节点的路径，请输出-1。

可达的
*/
