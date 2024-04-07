#include <iostream>
#include "table.h"
#include "hashTable.h"
#include "sortTable.h"
#include "binTreeTable.h"
#include <string>
using namespace std;




int main() {
	{

		BinTreeTable<int, int> t;
		t.insert(3, 3);
		t.insert(1, 1);
		t.insert(2, 2);
		t.insert(5, 5);
		t.insert(4, 4);
		t.insert(0, 0);
		for (int i = 0; i < 6; i++) {
			cout << t[i] << "\n";
		}
		cout << t.size();
		//if (t.remove(3))cout << 1;
		//else cout << 0;
		//if (t.remove(3))cout << 1;
		//else cout << 0;

		//BinTreeTable<int, int> t1 = t;
		//
		//BinTreeTable<int, int> t2;
		//t2.insert(3, 3);
		//t2.insert(4, 4);
		//t2.insert(5, 5);
		//for (int i = 3; i < 6; i++) {
		//	cout << t2[i] << "\n";
		//}
		//cout << "\n";
		//t2 = t;
		//for (int i = 0; i < 6; i++) {
		//	cout << t2[i] << "\n";
		//}
		//if (t2.remove(3))cout << 1;
		//else cout << 0;
		//if (t2.remove(3))cout << 1;
		//else cout << 0;
		//int data = 10;
		//int key = 25;
		//HashTable<int, int> a(100);
		//a.insert(key, data);
		//a.insert(key + 20, data + 1);
		//a.insert(key - 20, data - 1);
		//
		//if (a[key] == data)return 1;
		//return 0;
	}
	
	//BinTreeTable<int, int> a;
	//a.insert(2, 2);
	//a.insert(1, 1);
	//a.insert(4, 4);
	//a.insert(3, 3);
	//a.insert(5, 5);
	//a.insert(6, 6);
	//a.remove(4);
	//a.insert(0, 0);
	//a.insert(4, 4);
	//
	//cout << a[4];
	//
	//HashTable<string, int> a(50000);
	//a.insert("apple", 123);
	//a.insert("mango", 432);
	//a.insert("banana", 213);
	//a.insert("guava", 654);//example https://codechick.io/tutorials/dsa/dsa-hash-table
	//a.insert("orange", 345);

	//cout << a["apple"]<<"\n";
	//cout << a["mango"]<<"\n";
	//cout << a["banana"]<<"\n";
	//cout << a["guava"]<<"\n";
	//cout << a["orange"]<<"\n";
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