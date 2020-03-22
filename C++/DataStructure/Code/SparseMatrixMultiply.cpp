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
	}
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
						cacheans += (count[j] * a.count[p]);
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
	test0*test1;
	return 0;
}
