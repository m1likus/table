#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include "table.h"
#include "sortTable.h"
#include "hashTable.h"
#include "binTreeTable.h"
#include "avlTreeTable.h"
#include "rbTreeTable.h"
#include <string>
using namespace std;




int main() {
	AvlTreeTable <int, int> a;
	a.insert(100, 0);
	a.insert(50, 0);
	a.insert(160, 0);
	a.insert(130, 0);
	a.insert(170, 0);

	a.remove(50);
}