#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

#include<iostream>
#include<string>
#include<vector>

using namespace std;

class node {
	int id;
	vector<int> reachableNodes;
	vector<int> reachabelLength;

public:
	node(int id) :id(id) {

	}

	void connect(int node, int length) {
		this->reachableNodes.push_back(node);
		this->reachabelLength.push_back(length);
	}

	int refresh(vector<int>& distance, vector<bool>& reached, vector<vector<int>>& front) {
		reached[this->id - 1] = true;
		int nextNode = -1;
		int minLength = -1;
		for (int i = 0; i < this->reachableNodes.size(); i++) {
			if (reached[this->reachableNodes[i]]) {
				continue;
			}
			if (distance[this->reachableNodes[i]] == -1 || distance[this->reachableNodes[i]] >= distance[this->id - 1] + this->reachabelLength[i]) {
				if (distance[this->reachableNodes[i]] != distance[this->id - 1] + this->reachabelLength[i]) {
					distance[this->reachableNodes[i]] = distance[this->id - 1] + this->reachabelLength[i];
					front[this->reachableNodes[i]].clear();
				}
				front[this->reachableNodes[i]].push_back(this->id - 1);
			}
		}
		for (int i = 0; i < distance.size(); i++) {
			if (reached[i] || distance[i] == -1) {
				//if (distance[i] == -1 || distance[i] == 0) {
				continue;
			}
			else {
				if (minLength == -1) {
					minLength = distance[i];
					nextNode = i;
				}
				else {
					if (minLength > distance[i]) {
						minLength = distance[i];
						nextNode = i;
					}
				}
			}
		}
		return nextNode;
	}
};

class map {
	int nodes;
	vector<node*> list;
	vector<int> distance;
	vector<bool> reached;
	vector<vector<int>> front;
public:
	map(int nodes) :nodes(nodes) {
		for (int i = 0; i < this->nodes; i++) {
			this->list.push_back(new node(i + 1));
		}
	}

	~map() {
		for (int i = 0; i < this->nodes; i++) {
			delete this->list[i];
		}
	}

	void connectSingle(int left, int right, int length) {
		this->list[left]->connect(right, length);
	}

	void connectDouble(int left, int right, int length) {
		this->list[left]->connect(right, length);
		this->list[right]->connect(left, length);
	}

	int getDistanceAndPath(int start, int end, string& path) {
		this->distance.clear();
		this->reached.clear();
		this->front.clear();
		int connectCounter = 1;
		int length = -1;
		vector<vector<int>>temp(this->nodes);
		this->front = temp;
		for (int i = 0; i < this->nodes; i++) {
			this->distance.push_back(-1);
			this->reached.push_back(false);
		}
		this->distance[start] = 0;
		this->reached[start] = true;
		int nextNode;
		nextNode = this->list[start]->refresh(this->distance, this->reached, this->front);
		while (nextNode != -1) {
			nextNode = this->list[nextNode]->refresh(this->distance, this->reached, this->front);
		}
		length = this->distance[end];
		path = getPath(start, end);
		return length;
	}

	string getPath(int start, int end) {
		if (start == end) {
			return to_string(start + 1);
		}
		string result;
		string temp;
		for (int i = 0; i < this->front[end].size(); i++) {
			temp = getPath(start, (this->front[end][i]));
			temp += " ";
			temp += to_string(end + 1);
			if (temp < result || result.empty()) {
				result = temp;
			}
		}
		return result;
	}
};


int main(void) {
	int nodes, edges, start, end;
	scanf("%d %d %d %d", &nodes, &edges, &start, &end);
	int left, right, length;
	map graph(nodes);
	for (int i = 0; i < edges; i++) {
		scanf("%d %d %d", &left, &right, &length);
		graph.connectDouble(left - 1, right - 1, length);
	}
	string path = "";
	length = graph.getDistanceAndPath(start - 1, end - 1, path);
	printf("%d\n", length);
	if (length != -1) {
		printf("%s\n", path.c_str());
	}
	return 0;
}
