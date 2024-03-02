#include <iostream>
#include "table.h"
#include "hashTable.h"
#include "sortTable.h"
#include "binTreeTable.h"
#include <string>
using namespace std;




int main() {
	HashTable<string, int> a(50000);
	a.insert("apple", 123);
	a.insert("mango", 432);
	a.insert("banana", 213);
	a.insert("guava", 654);//example https://codechick.io/tutorials/dsa/dsa-hash-table
	a.insert("orange", 345);

	cout << a["apple"]<<"\n";
	cout << a["mango"]<<"\n";
	cout << a["banana"]<<"\n";
	cout << a["guava"]<<"\n";
	cout << a["orange"]<<"\n";
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