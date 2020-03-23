#include<iostream>
#include<cmath>
using namespace std;

//---------------------------------------------------------------  HashList  -----------------
// With the detect x^2 function
class HashList {
private:
	int *list;
	int *ans;
	bool *situationInsertList;
	int TSize;
	int msize, nsize;
	bool start;
	int countNum;
public:
	HashList(int m,int n);
	~HashList();
	int H(int key);
	int insert(int value);
	int search(int value);
	bool del(int value);
	friend ostream & operator<<(ostream& out, HashList a);
};
ostream & operator<<(ostream& out, HashList a) {
	int i = 0;
	//cout << "length of Tsize is" << a.TSize<<endl;
	while (i < a.nsize) {
		if (a.start) {
			cout << " ";
		}
		a.start = true;
		if (a.ans[i] != -1) {
			cout << a.ans[i];
		}
		if (a.ans[i] == -1) {
			cout << "-";
		}
		i++;
	}
	a.start = false;
	return out;
}
HashList::HashList(int m,int n) {
	msize = m;
	nsize = n;
	TSize = m;
	countNum = 0;
	start = false;
	bool cache = false;
	while (!cache) {
		cache = true;
		for (int i = 2; i <= (int)sqrt(TSize); i++) {
			if (TSize%i == 0) {
				cache = false;
			}
		}
		if (!cache) {
			TSize++;
		}
	}
	list = new int[TSize];
	//ans = new int[TSize];
	situationInsertList = new bool[TSize];
	for (int i = 0; i < TSize; i++) {
		list[i] = 0;
		situationInsertList[i] = false;
	}
	int i = 0;
	ans = new int[nsize];
	while (i < nsize) {
		int cache;
		cin >> cache;
		ans[i] = insert(cache);
		i++;
		//cout<<ans[i]<<endl; 
	}
}
HashList::~HashList() {

}
int HashList::H(int key) {
	return key % TSize;
}
int HashList::insert(int value) {
	int position = H(value);
	int i = 0;
	while (i<TSize) {
		position += i * i;
		position%=TSize;
//		cout<<" "<<position<<" position"<<endl;
		if (!situationInsertList[position]) {
			list[position] = value;
			situationInsertList[position] = true;
			countNum++;
			return position;
			break;
		}
		position -= i * i;
		i++;
	}
	return -1;
}
int HashList::search(int value) {
	//Unuse this function in this problem.
	//return 0;
	int position = H(value);
	int i = 0;
	while (i < TSize) {
		position += i * i;
		position%=TSize;
		if (list[position]==value) {
			return position;
			break;
		}
		position -= i * i;
		i++;
	}
	return -1;
}
bool HashList::del(int value) {
	int position = search(value);
	if (position != -1) {
		list[position] = 0;
		situationInsertList[position] = false;
		return true;
	}
	return false;
}


int main(void) {
	int m, n;
	cin >> m >> n;
	HashList a(m, n);
	cout << a;
	
	system("pause");
	return 0;
}

