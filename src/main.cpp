#include <iostream>
#include "table.h"
using namespace std;

int main() {
	Table<int, int> a(3);
	Iterator<int, int> b(make_pair(0, 0));
	int cnt = 0;
	
	for (auto i = a.begin(); i != a.end(); ++i) {
		cnt++;
	}
	cout << cnt<<"\n";
	
	/*SortTable<int, int> s(3);
	int cnt1 = 0;
	for (auto i = s.begin(); i != s.end(); ++i) {
		cnt1++;
	}
	cout << cnt1;*/

	//Table<int, int> a;
	//for (int i = 0; i < 5; i++) {
	//	a.insert(i,i);
	//}
	//for (int i = 0; i < 5; i++) {
	//	cout << a[i]<<" ";
	//}
	//cout << "\n";
	//
	//cout << *a.find(3) << "\n";
	//
	//if (a.remove(3)) {
	//	if (a.find(3) == a.end())
	//		cout << "yes";
	//}

	/*vector<int> key = { 2,5,3,6,4 };
	vector<int> data = { 1,2,3,4,5 };
	Table<int, int> a;
	for (int i = 0; i < 5; i++) {
		a[key[i]] = data[i];
	}
	int pos = 3;
	if ((a.begin() + pos) == a.find(key[pos]))
		cout << 1;
	else cout << 0;

	return 0;*/
}