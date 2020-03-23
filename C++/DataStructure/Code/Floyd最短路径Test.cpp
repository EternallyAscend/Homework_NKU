#include<iostream>
#include<vector>
using namespace std;
class map {
private:
	int size;
	int *fare;
	int **list;
	int **parent;
public:
	map(int);
	~map();
	void insert(int, int, int);
	void insert(int, int);
	int check(int, int);
	void create();
	vector<int> find(int, int);
	void print();
};
map::map(int size) :size(size) {
	this->fare = new int[size];
	this->list = new int*[size];
	this->parent = new int*[size];
	for (int i = 0; i < size; i++) {
		this->list[i] = new int[size];
		this->parent[i] = new int[size];
		for (int j = 0; j < size; j++) {
			this->list[i][j] = 65535;
			this->parent[i][j] = -1;
		}
	}
}
map::~map() {}
void map::insert(int x, int y, int length)
{
	//this->list[x][y] = this->list[y][x] = length;
	if (length != -1) this->list[x][y] = length;
}
void map::insert(int x, int fare)
{
	this->fare[x] = fare;
}
int map::check(int x, int y)
{
	if (this->list[x][y] != 65535) return this->list[x][y];
	else return -1;
}
void map::create()
{
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			if (j == i)continue;
			if (this->list[j][i] == 65535)continue;
			for (int k = 0; k < this->size; k++) {
				if (k == i)continue;
				if (this->list[i][k] == 65535)continue;
				if (this->list[j][i] + this->list[i][k] + this->fare[i] <= this->list[j][k]) {
					this->list[j][k] = this->list[j][i] + this->fare[i] + this->list[i][k];
					this->parent[j][k] = i;
				}
			}
		}
	}
}
vector<int> map::find(int x, int y)
{
	vector<int> ans;
	if (this->list[x][y] == 65535) ans.push_back(-1);
	else {
		int temp = y;
		while (temp != -1) {
			ans.push_back(temp);
			if (this->parent[x][temp] != -1) {
				vector<int> cache = find(this->parent[x][temp], temp);
				for (int i = 1; i < cache.size() - 1; i++) {
					ans.push_back(cache[i]);
				}
			}
			temp = this->parent[x][temp];
		}
		ans.push_back(x);
	}
	return ans;
}
void map::print()
{
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			cout << this->list[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			cout << this->parent[i][j] << " ";
		}
		cout << endl;
	}
}
int main(void) {
	int n, m, x, y;
	cin >> n;
	map ans(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> m;
			ans.insert(i, j, m);
		}
	}
	for (int i = 0; i < n; i++) {
		cin >> m;
		ans.insert(i, m);
	}
	ans.create();
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		vector<int> test;
		test = ans.find(x, y);
		if (test[0] != -1) {
			for (int j = test.size() - 1; j > 0; j--) {
				cout << test[j] << "->";
			}
			cout << test[0] << endl << ans.check(x, y);
		}
		else cout << "No Path";
		cout << endl;
	}
	system("pause");
	return 0;
}
/*
vector<int> Graph::find(int start,int end){
    /*
    vector<int> ans;
		int temp = end;
		while (temp != -1) {
			ans.push_back(temp);
			if (this->front[start][temp] != -1) {
				vector<int> cache = find(this->front[start][temp], temp);
				for (int i = 1; i < cache.size() - 1; i++) {
					ans.push_back(cache[i]);
				}
			}
			temp = this->front[start][temp];
		}
		ans.push_back(start);
	return ans;
    */
    /*
    vector<int> ans;
    if(front[start][end]==-1){
        ans.push_back(start);
        ans.push_back(end);
    }
    else{
        int temp=front[start][end];
        vector<int> tempLeft=find(start,temp);
        vector<int> tempRight=find(temp,end);
        for(int i=0;i<tempLeft.size();i++){
            ans.push_back(tempLeft[i]);
        }
        for(int i=1;i<tempRight.size();i++){
            ans.push_back(tempRight[i]);
        }
    }

    return ans;
}
*/
