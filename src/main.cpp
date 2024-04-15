#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include "table.h"
#include "sortTable.h"
#include "hashTable.h"
#include "binTreeTable.h"
#include <string>
using namespace std;




int main() {
    int N = 1000;
    vector<int> b(N);
    for (int i = 0; i < N; i++) {
        b[i] = i;
    }
    random_device rd;
    mt19937 g(rd());
    std::shuffle(b.begin(), b.end(), g);
    BinTreeTable<int, int> a;
    for (int i = 0; i < N; i++) {
        a.insert(b[i], b[i]);
    }
    cout << a.getHeight();
}