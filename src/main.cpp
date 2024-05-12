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
#include <fstream>
#include <ctime>
#include <numeric>
#include <string>
using namespace std;




int main() {
	{
		//Inserts
		cout << "\n ---Inserts---\n";
		setlocale(LC_ALL, "Russian");
		std::ofstream f;
		f.open("Inserts.csv", ios::out/*ios::app*/);
		if (f.is_open())cout << "is open\n";
		cout << "Tree " << "N " << "time \n";
		f << "N; BinTree; AvlTree; rbTree\n";
		int n_start = 1000;
		int n_end = 2000000;
		int n_step = (n_end - n_start) / 10;
		for (int l = n_start; l <= n_end; l += n_step) {
			int N = l;

			float t1, t2;
			random_device rd;
			int seed = 5;
			mt19937 g(seed); 
			vector<int> vec_insert(N);
			std::iota(vec_insert.begin(), vec_insert.end(), 0);
			std::shuffle(vec_insert.begin(), vec_insert.end(), g);

			//BinTree
			BinTreeTable<int, int> a;
			t1 = clock();
			for (int i = 0; i < N; i++)
				a.insert(vec_insert[i], 20);
			a.insert(N + 1, 20);
			t2 = clock();
			cout <<"BinTree "<< l << "; " << t2 << "; " << t1 << "; " << t2 - t1 << "\n";
			f << l << ";" << t2 - t1;

			//AvlTree
			AvlTreeTable<int, int> b;
			t1 = clock();
			for (int i = 0; i < N; i++)
				b.insert(vec_insert[i], 20);
			b.insert(N + 1, 20);
			t2 = clock();
			cout << "AvlTree " << l << "; " << t2 << "; " << t1 << "; " << t2 - t1 << "\n";
			f << ";" << t2 - t1;

			//rbTree
			t1 = clock();
			RbTreeTable<int, int> c;
			for (int i = 0; i < N; i++)
				c.insert(vec_insert[i], 20);
			c.insert(N + 1, 20);
			t2 = clock() ;
			cout << "RbTree "<< l << "; " << t2 << "; " << t1 << "; " << t2 - t1 << "\n";
			f << ";" << t2 - t1 << "\n";
		}
		f.close();
	}
	{
		//Removes
		cout << "\n ---REMOVES---\n";
		setlocale(LC_ALL, "Russian");
		std::ofstream f;
		f.open("Removes.csv", ios::out/*ios::app*/);
		if (f.is_open())cout << "is open\n";
		cout << "Tree " << "N " << "time \n";
		f << "N; BinTree; AvlTree; rbTree\n";
		int n_start = 1000;
		int n_end = 2000000;
		int n_step = (n_end - n_start) / 10;
		for (int l = n_start; l <= n_end; l += n_step) {
			int N = l;

			float t1, t2;
			random_device rd;
			int seed = 5;
			mt19937 g(seed);
			vector<int> vec_insert(N);
			std::iota(vec_insert.begin(), vec_insert.end(), 0);
			std::shuffle(vec_insert.begin(), vec_insert.end(), g);

			//BinTree
			
			BinTreeTable<int, int> a;
			for (int i = 0; i < N; i++)
				a.insert(vec_insert[i], 20);
			a.insert(N + 1, 20);
			t1 = clock();
			for (int i = 0; i < N; i++)
				a.remove(vec_insert[i]);
			a.remove(N+1);
			t2 = clock();
			cout << "BinTree " << l << "; " << t2 << "; " << t1 << "; " << t2 - t1 << "\n";
			f << l << ";" << t2 - t1;

			//AvlTree
			AvlTreeTable<int, int> b;
			for (int i = 0; i < N; i++)
				b.insert(vec_insert[i], 20);
			b.insert(N + 1, 20);
			t1 = clock();
			for (int i = 0; i < N; i++)
				b.remove(vec_insert[i]);
			b.remove(N + 1);
			t2 = clock();
			cout << "AvlTree " << l << "; " << t2 << "; " << t1 << "; " << t2 - t1 << "\n";

			f << ";" << t2 - t1;

			//rbTree
			RbTreeTable<int, int> c;
			for (int i = 0; i < N; i++)
				a.insert(vec_insert[i], 20);
			a.insert(N + 1, 20);
			t1 = clock();
			for (int i = 0; i < N; i++)
				a.remove(vec_insert[i]);
			a.remove(N + 1);
			t2 = clock();
			cout << "RbTree " << l << "; " << t2 << "; " << t1 << "; " << t2 - t1 << "\n";

			f << ";" << t2 - t1 << "\n";
		}
		f.close();
	}
}