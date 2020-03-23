#include<iostream>
#include<vector>
#include<cmath>
#include"plt.h"

using namespace std;

	PartLineTree::PartLineTree(int number,const vector<int>& valList) {
		
		//for (floor=0; pow(2, this->floor) >= number; this->floor++) {

		//}
		while (pow(2, this->floor) < number) {
			floor += 1;
			cout <<"Floor is :"<< floor << endl;
		}
		length = pow(2, this->floor+1);
		this->tree = new int[length];
		for (int i = 0; i < length; i++) {
			this->tree[i] = 0;
		}
		for (int i = 0; i < number; i++) {
			tree[length / 2 - 1 + i] = valList[i];
		}
		for (int i = (length / 2 - 2); i >= 0; i--) {
			tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
		}
	}
	PartLineTree::~PartLineTree() {

	}
	int PartLineTree::getValue(int pos) {
		return this->tree[length / 2 - 2 + pos];
	}
	void PartLineTree::modValue(int pos, int value) {
		this->tree[length / 2 - 2 + pos] = value;
		this->refresh();
	}
	void PartLineTree::refresh() {
		for (int i = (length / 2 - 2); i >= 0; i--) {
			tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
		}
	}
	bool PartLineTree::isEmpty() {
		return true;
	}
	bool PartLineTree::deleteElement() {
		return true;
	}


	using namespace std;
	int main(void) {
		int number;
		cin >> number;
		vector<int> valList;

		for (int i = 0; i < number; i++) {
			int cache;
			cin >> cache;
			valList.push_back(cache);
		}
		cout << endl;

		PartLineTree tree(number, valList);
		cout <<"tree length:"<< tree.length<<endl;
		for (int i = 0; i < tree.length; i++) {
			cout <<"The tree element is"<< tree.tree[i]<<"- -"<<endl;
		}
		system("pause");
		return 0;
	}