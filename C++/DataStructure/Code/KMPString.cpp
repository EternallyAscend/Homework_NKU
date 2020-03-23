#include<iostream>
#include<string>
using namespace std;
class KMPStr {
private:
	int *list;
	char *str;
	int len;
public:
	KMPStr();
	KMPStr(string a);
	~KMPStr();
	friend ostream & operator<<(ostream &out, KMPStr a);
	friend int check(string lstr, KMPStr sstr);
};

ostream & operator<<(ostream &out, KMPStr a) {
	for (int i = 1; i < a.len + 1; i++) {
		cout << a.str[i] << " ";
	}
	cout << endl;
	for (int i = 1; i < a.len + 1; i++) {
		cout << a.list[i] << " ";
	}
	return out;
}

KMPStr::KMPStr() {
	string cache;
	cin >> cache;
	len = cache.length();
	//cout << len << endl;
	//cout << "This is the ans." << endl;
	str = new char[len + 1];
	list = new int[len + 1];
	list[0] = 0;
	list[1] = 0;
	str[1] = cache[0];
	for (int i = 2; i < len + 1; i++) {
		str[i] = cache[i - 1];
		int j = i;
		while (j) {
			if (str[i] == str[list[j - 1]]) {
				list[i] = list[j - 1] + 1;
				break;
			}
			else {
				//j = list[j - 1] + 1;
				j = list[j - 1];
			}
			if (list[j - 1] == 0) {
				list[i] = 1;
				break;
			}
		}

	}
}

KMPStr::KMPStr(string cache) {
	len = cache.length();
	//cout << len << endl;
	//cout << "This is the ans." << endl;
	str = new char[cache.length() + 1];
	list = new int[cache.length() + 1];
	list[0] = 0;
	list[1] = 0;
	list[2] = 1;
	str[1] = cache[0];
	for (int i = 2; i < cache.length() + 1; i++) {
		str[i] = cache[i - 1];
		int j = i;
		while (j) {
			if (str[i - 1] == str[list[j - 1]]) {
				list[i] = list[j - 1] + 1;
				break;
			}
			else {
				//j = list[j - 1] + 1;
				j = list[j - 1];
			}
			if (list[j - 1] == 0) {
				list[i] = 1;
				break;
			}
		}
		
	}
	//cout << *this << endl;
}
KMPStr::~KMPStr() {
	//cout << endl;
}

int check(string lstr, KMPStr sstr) {
	int compare = 1;
	for (int i = 0; i < lstr.length(); i++) {
		if (lstr[i] == sstr.str[compare]) {
			compare++;
		}
		else {
			while (sstr.list[compare]) {
				compare = sstr.list[compare];
				if(lstr[i] == sstr.str[compare]){
					compare++;
					break;
				}
			}
			compare = 1;
		}
		if (compare == sstr.len) {
			return (i - compare + 2);
			break;
		}
	}
	return 0;
}

int main(void) {
	string lstr,sstr;
	cin >> lstr >> sstr;
	KMPStr str(sstr);
	int ans=check(lstr, sstr);
	if (ans) {
		cout << ans;
	}
	else {
		cout << "no";
	}
	system("pause");
	return 0;
}