#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include "table.h"
#include "sortTable.h"
#include "hashTable.h"
#include "binTreeTable.h"
#include "avlTreeTable.h"
#include <string>
#include <fstream>
#include <ctime>
#include <numeric>
using namespace std;




int main() {
	{
		setlocale(LC_ALL, "Russian");
		std::ofstream f;
		f.open("binTree_insert.csv", ios::out/*ios::app*/);
		if (f.is_open())cout << "is open\n";
		int n_start = 10;
		int n_end = 1000000;
		int n_step = (n_end - n_start) / 10;
		for (int l = n_start; l <= n_end; l += n_step) {
			float t1 = clock();
			int N = l;
			AvlTreeTable<int, int> a;
			vector<int> vec_insert(N);
			std::iota(vec_insert.begin(), vec_insert.end(), 0);
			random_device rd;
			int seed = 0;
			mt19937 g(seed); // rd
			std::shuffle(vec_insert.begin(), vec_insert.end(), g);
			for (int i = 0; i < N; i++) {
				a.insert(vec_insert[i], 20);
			}//создаем дерево на l элементов
			//float t1 = clock();
			a.insert(N + 1, 20);
			float t2 = clock();
			cout<< l << ";" << t2<<";"<<t1<<";"<<t2 - t1 << "\n";
			f << l << ";" << t2 - t1 << "\n";
		}
		f.close();
	}
}