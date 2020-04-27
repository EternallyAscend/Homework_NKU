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
