#include<iostream>
#include<string>
using namespace std;
class halfmanNode {
	friend class halfman;
private:
	string ans;
	char eng;
	int weight;
	halfmanNode *left;
	halfmanNode *right;
	halfmanNode *parent;
public:
	halfmanNode();
	halfmanNode(const int weight,halfmanNode *left,halfmanNode *right);
	halfmanNode(const char eng, const int weight);
	halfmanNode(const string& ans, const char eng, const int weight);
	~halfmanNode();
	void vlr();
	void lvr();
	void lrv();
};
halfmanNode::halfmanNode() {
	this->weight = -1;
	this->left = NULL;
	this->right = NULL;
	this->parent = NULL;
}
halfmanNode::halfmanNode(const int weight,halfmanNode *left,halfmanNode *right) {
	this->weight = weight;
	this->left = left;
	this->right = right;
	this->parent = NULL;
}
halfmanNode::halfmanNode(const char eng, const int weight) {
	this->weight = weight;
	this->eng = eng;
	this->left = NULL;
	this->right = NULL;
	this->parent = NULL;
}
halfmanNode::halfmanNode(const string& ans, const char eng, const int weight) {
	this->weight = weight;
	this->eng = eng;
	for (int i = 0; i < ans.length(); i++) {
		this->ans[i] = ans[i];
	}
	this->left = NULL;
	this->right = NULL;
	this->parent = NULL;
}
halfmanNode::~halfmanNode() {

}
void halfmanNode::vlr() {
	if (this->eng) {
		cout << this->eng << this->ans[1] << endl;
	}
	if (this->left != NULL) {
		this->left->lvr();
	}
	if (this->right != NULL) {
		this->right->lvr();
	}
}
void halfmanNode::lvr(){
	if (this->left != NULL) {
		for (int i = 0; i < this->ans.length(); i++) {
			this->left->ans.push_back(ans[i]);
		}
		this->left->ans.push_back('0');
		this->left->lvr();
	}
	if (this->eng) {
		cout << this->eng << ":";
		for (int i = 0; i < this->ans.length(); i++) {
			cout << ans[i];
		}
		cout << endl;
	}
	if (this->right != NULL) {
		for (int i = 0; i < this->ans.length(); i++) {
			this->right->ans.push_back(ans[i]);
		}
		this->right->ans.push_back('1');
		this->right->lvr();
	}
}
void halfmanNode::lrv() {
	if (this->left != NULL) {
		this->left->lvr();
	}
	if (this->right != NULL) {
		this->right->lvr();
	}
	if (this->eng) {
		cout << this->eng << endl;
	}
}
class halfman {
	friend class halfmanNode;
private:
	halfmanNode **nodeList;
	halfmanNode *root;
	int sum;
	int size;
public:
	halfman();
	halfman(int size);
	~halfman();
	halfmanNode* getRoot();
};
halfman::halfman() {

}
halfman::halfman(int size) {
	int list;
	char clist;
	this->nodeList = new halfmanNode*[size];
	this->sum = 0;
	for (int i = 0; i < size; i++) {
		cin >> clist >> list;
		this->nodeList[i] = new halfmanNode(clist, list);
		this->sum += list;
	}
	for (int j = 0; j < size - 1; j++) {
		for (int i = 0; i < size - 1; i++) {
			if (this->nodeList[i]->weight < this->nodeList[1 + i]->weight) {
				halfmanNode *temp;
				temp = this->nodeList[i];
				this->nodeList[i] = this->nodeList[i + 1];
				this->nodeList[i + 1] = temp;
			}
		}
	}
	for (int i = size - 1; i > 0; i--) {
		halfmanNode *temp;
		temp = nodeList[i - 1];
		nodeList[i - 1] = new halfmanNode(temp->weight + nodeList[i]->weight, nodeList[i], temp);
		if (i - 1 != 0) {
			for (int j = 1; j <= i; j++) {
				if (i - j - 1 >= 0) {
					if (this->nodeList[i - j]->weight > this->nodeList[i - j - 1]->weight) {
						halfmanNode *cache;
						cache = this->nodeList[i - j];
						this->nodeList[i - j] = this->nodeList[i - j - 1];
						this->nodeList[i - j - 1] = cache;
					}
					else {
						break;
					}
				}
				else {
					break;
				}

			}
		}
		else {
			this->root = nodeList[0];
		}
	}
}
halfman::~halfman() {

}
halfmanNode* halfman::getRoot() {
	return this->root;
}
int main(void) {
	int size;
	cin >> size;
	halfman test(size);
	test.getRoot()->lvr();
	//system("pause");
	return 0;
}

/*
Problem description
�����������Ϣ����������������Ҫ������ʱ��Ƶ�ε͵Ľڵ�����Ƶ�θߵĽڵ����ҡ�������������ȵ��и���������ַ����롣

���룺��������Ҫ������ַ�������Ȼ��˳����������ַ�����char�ַ��������ַ�����Ƶ�Ρ�

�������������ȵ��и�����˳����������ַ�������룬�ַ��������м���ð�Ÿ�����



Annex

Sample of Input and Output
����1
Input:
6
a	267
b	96
c	730
d	787
e	10
f	610
Output:
e:0000
b:0001
a:001
f:01
c:10
d:11
*/
