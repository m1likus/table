#include <iostream>
#include "table.h"
#include "sortTable.h"
#include "hashTable.h"
#include "binTreeTable.h"
#include <string>
using namespace std;




int main() {
    int data = 10;
    BinTreeTable<string, int> a;
    a.insert("key", data);
    a.insert("key + 1", data + 1);
    a.insert("key - 1", data - 1);

    cout<<(a["key"]== data);
	return 0;
}