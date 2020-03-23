#include<iostream>
using namespace std;

class SparseMatrixSequence {
private:
	int rowLength, coloumLength, countNum;
	int *count, *row, *coloum;
	int size, rowSize;
	int *positionListOfRow;
public:
	SparseMatrixSequence();
	SparseMatrixSequence(int ranks);
	SparseMatrixSequence(int r, int c, int num);
	~SparseMatrixSequence();
	void transpose();
	void push(int r, int c, int value);
	void expand();
	void createPositionList();
	friend ostream & operator<<(ostream &out, SparseMatrixSequence a);
	SparseMatrixSequence & operator=(const SparseMatrixSequence &a);
	SparseMatrixSequence operator*(const SparseMatrixSequence &a);
};
//---------------------------SparseMatrix SequenseList---------------------------
ostream & operator<<(ostream &out, SparseMatrixSequence a) {
	for (int i = 0; i < a.countNum; i++) {
		cout << a.row[i] << " " << a.coloum[i] << " " << a.count[i] << endl;
	}//
	 /*
	for (int i = 0; i < a.rowLength + 1; i++) {
		cout << a.positionListOfRow[i] << " ";
	}
	cout << endl;//
	*/
	return out;
}

SparseMatrixSequence::SparseMatrixSequence() {
	rowLength = 20;
	coloumLength = 20;
	countNum = 0;
	rowLength = 0;
	coloumLength = 0;
	size = 20;
	row = new int[size];
	coloum = new int[size];
	count = new int[size];
	rowSize = 20;
	positionListOfRow = new int[rowSize + 1];
	for (int i = 0; i < size + 1; i++) {
		positionListOfRow[i] = 0;
	}
}
SparseMatrixSequence::SparseMatrixSequence(int ranks) {
	rowLength = ranks;
	coloumLength = ranks;
	countNum = 0;
	rowLength = 0;
	coloumLength = 0;
	size = 20;
	row = new int[size];
	coloum = new int[size];
	count = new int[size];
	rowSize = 20;
	positionListOfRow = new int[rowSize + 1];
	for (int i = 0; i < size + 1; i++) {
		positionListOfRow[i] = 0;
	}
}
SparseMatrixSequence::SparseMatrixSequence(int r, int c, int num) {
	count = new int[num];
	row = new int[num];
	coloum = new int[num];
	size = countNum;
	rowSize = rowLength;
	positionListOfRow = new int[r + 1];
	for (int i = 0; i < r + 1; i++) {
		positionListOfRow[i] = 0;
	}
	int cache;
	rowLength = r;
	coloumLength = c;
	countNum = num;
	for (int i = 0; i < num; i++) {
		cin >> cache;
		positionListOfRow[cache]++;
		row[i] = cache;
		cin >> cache;
		coloum[i] = cache;
		cin >> cache;
		count[i] = cache;
	}
	for (int i = 0; i < r; i++) {
		positionListOfRow[i + 1] += positionListOfRow[i];
	}
}
SparseMatrixSequence::~SparseMatrixSequence() {
}
void SparseMatrixSequence::transpose() {
	int value;
	int *coloumcache = new int[countNum];
	int *cacheList = new int[countNum];
	for (int i = 0; i < countNum; i++) {
		coloumcache[i] = coloum[i];
		cacheList[i] = count[i];
	}
	int *positionList = new int[coloumLength + 1];
	for (int i = 0; i < coloumLength + 1; i++) {
		positionList[i] = 0;
	}
	for (int i = 0; i < countNum; i++) {
		positionList[coloum[i]]++;
	}
	for (int i = 1; i <= coloumLength; i++) {
		positionList[i] += positionList[i - 1];
	}

	/*/----------------------------------------test
	cout << "----------------------------------  Test  -------------------------------"<<endl;
	for (int i = 0; i < countNum; i++) {
		cout << coloumcache[i] << "    " << cacheList[i] << endl;
	}
	cout << "----------------------------------  Posi  -------------------------------"<<endl;
	for (int i = 0; i < coloumLength+1; i++) {
		cout << i << " is " << positionList[i] << endl;
	}
	cout << "----------------------------------  Tend  -------------------------------"<<endl;
	//-----------------------------------------end*/

	for (int i = 0; i < countNum; i++) {
		count[positionList[coloumcache[i] - 1]] = cacheList[i];
		coloum[positionList[coloumcache[i] - 1]++] = row[i];
	}
	int key = 0;
	for (int i = 0; i < coloumLength; i++) {
		for (int j = key; j < positionList[i]; j++) {
			row[j] = i + 1;
			key = positionList[i];
		}
	}
	value = rowLength;
	rowLength = coloumLength;
	coloumLength = value;
	delete[]positionListOfRow;
	positionListOfRow = new int[rowLength + 1];
	rowSize = rowLength;
	for (int i = 0; i < rowLength + 1; i++) {
		positionListOfRow[i] = 0;
	}
	for (int i = 0; i < countNum; i++) {
		positionListOfRow[row[i]]++;
	}
	for (int i = 0; i < rowLength; i++) {
		positionListOfRow[i + 1] += positionListOfRow[i];
	}
}
void SparseMatrixSequence::push(int r, int c, int value) {
	row[countNum] = r;
	coloum[countNum] = c;
	count[countNum++] = value;
	if (r > rowLength) {
		rowLength = r;
	}
	/*
	if (r > rowSize) {
		int *cache;
		cache = new int[rowSize+2];
		for (int i = 0; i < rowSize + 1; i++) {
			cache[i] = positionListOfRow[i];
		}
		cache[rowSize + 1] = 1;
		delete[]positionListOfRow;
		positionListOfRow = new int[rowSize * 2 + 1];
		for (int i = 0; i < rowSize + 2;i++) {
			positionListOfRow[i] = cache[i];
		}
		delete[]cache;
		for (int i = rowSize + 2; i < rowSize * 2 + 1; i++) {
			positionListOfRow[i] = 0;
		}
		rowSize *= 2;
	}
	*/
	if (c > coloumLength) {
		coloumLength = c;
	}
	if (countNum == size) {
		expand();
	}
}
void SparseMatrixSequence::expand() {
	int *cache = new int[3 * size];

	for (int i = 0; i < countNum; i++) {
		cache[i] = row[i];
		cache[i + size] = coloum[i];
		cache[i + 2 * size] = count[i];
	}
	delete[]row;
	delete[]coloum;
	delete[]count;
	row = new int[size * 2];
	coloum = new int[size * 2];
	count = new int[size * 2];
	for (int i = 0; i < countNum; i++) {
		row[i] = cache[i];
		coloum[i] = cache[i + size];
		count[i] = cache[i + size * 2];
	}
	size *= 2;
	delete[]cache;
}
void SparseMatrixSequence::createPositionList() {
	if (positionListOfRow) {
		delete[]positionListOfRow;
	}
	positionListOfRow = new int[rowLength + 1];
	for (int i = 0; i < countNum; i++) {
		positionListOfRow[row[i]]++;
	}
	for (int i = 0; i < rowLength; i++) {
		positionListOfRow[i + 1] += positionListOfRow[i];
	}
}
SparseMatrixSequence & SparseMatrixSequence::operator=(const SparseMatrixSequence &a) {

	rowLength = a.rowLength;
	coloumLength = a.coloumLength;
	countNum = a.countNum;
	delete[]row;
	delete[]coloum;
	delete[]count;
	row = new int[countNum];
	coloum = new int[countNum];
	count = new int[countNum];
	for (int i = 0; i < countNum; i++) {
		row[i] = a.row[i];
		coloum[i] = a.coloum[i];
		count[i] = a.count[i];
	}
	delete[]positionListOfRow;
	positionListOfRow = new int[rowLength + 1];
	for (int i = 0; i < rowLength + 1; i++) {
		positionListOfRow[i] = a.positionListOfRow[i];
	}
	return *this;
}
SparseMatrixSequence SparseMatrixSequence::operator*(const SparseMatrixSequence &an) {
	SparseMatrixSequence a;
	a = an;
	a.transpose();
	//cout << "They are" << endl;
	//cout << *this << endl;
	//cout << a << endl;
	//cout << this->rowLength << endl << a.rowLength << endl;
	SparseMatrixSequence ans(coloumLength);
	if (rowLength != a.rowLength || coloumLength != a.coloumLength) {
		ans.coloumLength = 0;
		ans.rowLength = 0;
		cout << "ERROR";
		return ans;
	}
	for (int i = 0; i < rowLength; i++) {
		for (int k = 0; k < a.rowLength; k++) {
			int cacheans = 0;
			for (int j = positionListOfRow[i]; j < positionListOfRow[i + 1]; j++) {

				for (int p = a.positionListOfRow[k]; p < a.positionListOfRow[k + 1]; p++) {
					if (coloum[j] == a.coloum[p]) {
						//cout << "cacheans+=" << count[j] << "*" << a.count[p] << "  " << j << "and" << p << endl;
						cacheans += (count[j] * a.count[p]);
						//cout << "anscache is" << cacheans << endl;
						break;
					}
					if (a.coloum[p] > coloum[j]) {
						break;
					}
				}

			}
			if (cacheans) {
				ans.push(i + 1, k + 1, cacheans);
			}
		}
	}
	if (ans.countNum) {
		//cout << endl << "ans is" << endl;
		cout << ans;
	}
	else {
		cout << "The answer is a Zero Matrix";
	}
	return ans;
}
//---------------------------------- main ------------------------------------------
int main(void) {
	int r, c, countNumber;
	cin >> r >> c >> countNumber;
	SparseMatrixSequence test0(r, c, countNumber);
	cin >> r >> c >> countNumber;
	SparseMatrixSequence test1(r, c, countNumber);
	//SparseMatrixSequence test4;
	test0*test1;
	//system("pause");
	return 0;
}


/*
1 2 3
1 4 7
2 2 8
3 1 6
3 3 9

//

1 1 1
1 3 3
1 4 4
1 7 7
2 2 8
2 4 9
2 6 1
3 1 2
3 4 3
3 7 4
4 2 5
4 3 6
4 5 7
4 6 8
5 1 9
5 4 1
5 6 2
6 2 3
6 5 4
6 7 4
*/
