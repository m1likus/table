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
	cout << cnt;
	return 0;
}