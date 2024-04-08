#pragma once

#include <string>
#include "table.h"
#include <math.h>

template<typename TypeKey, typename TypeData>
class HashTable;


template<typename TypeKey, typename T>
class hashIterator {
protected:
	pair<TypeKey, T>* iterator;
	HashTable<TypeKey, T>* it_table;
public:
	hashIterator(pair<TypeKey, T>& data, HashTable<TypeKey, T>& new_table) {
		iterator = &data;
		it_table = &new_table;
	}
	hashIterator(const hashIterator& other) {
		iterator = other.iterator;
		it_table = other.it_table;
	}
	T& operator*() const {
		return iterator->second;
	}
	T* operator->() const {
		return iterator.second;
	}
	hashIterator& operator++() {
		int index1 = it_table->HashFunction(iterator->first) % it_table->size();
		int index2 = 0;
		for (index2 = 0; index2 < (it_table->storage)[index1].size(); index2++) {
			if ((it_table->storage)[index1][index2].first == iterator->first) {
				break;
			}
		}
		for (int i = it_table->storage.size()-1; i >= 0; i--) {
			if (it_table->storage[i].size() != 0) {
				if (it_table->storage[index1][index2] == it_table->storage[i].back()) {
					iterator = &((it_table->storage)[index1][index2]) + 1;
					return *this;
				}
				else break;
			}
		}
		
		if (index2 < (it_table->storage)[index1].size() - 1)
			index2++;
		else {
			index1 = (index1 + 1) % it_table->size();
			while ((it_table->storage)[index1].size() == 0)
				index1 = (index1 + 1) % (it_table->storage).size();
			index2 = 0;
		}
		iterator = &((it_table->storage)[index1][index2]);
		return *this;
	}
	hashIterator& operator--() {
		int index1 = it_table->HashFunction(iterator->first) % it_table->size();
		int index2 = 0;
		for (index2 = 0; index2 < it_table->storage[index1].size(); index2++) {
			if (it_table->storage[index1][index2].first == iterator->first) {
				break;
			}
		}
		for (int i = 0; i < it_table->storage.size(); i++) {
			if (it_table->storage[i].size() != 0) {
				if (it_table->storage[index1][index2] == it_table->storage[i].front()) {
					iterator = &((it_table->storage)[index1][index2]);
					return *this;
				}
				else break;
			}
		}
		if (index2 > 0)
			index2--;
		else {
			index1 = (it_table->size() + index1 - 1) % it_table->size();
			while (it_table->storage[index1].size() == 0)
				index1 = (it_table->storage.size() + index1 - 1) % it_table->storage.size();
			index2 = it_table->storage[index1].size() - 1;
		}
		iterator = &((it_table->storage)[index1][index2]);
		return *this;
	}
	hashIterator operator+(int offset) {
		hashIterator<TypeKey, T> tmp = *this;
		for (int i = 0; i < offset; i++) {
			++tmp;
		}
		return tmp;
	}
	bool operator==(const hashIterator& other) {
		return iterator == other.iterator;
	}
	bool operator!=(const hashIterator& other) {
		return iterator != other.iterator;
	}
};



template<typename TypeKey,typename TypeData>
class HashTable {
protected:
	vector<vector<pair<TypeKey, TypeData>>> storage;
	double averageCollisions = 0;
	double percentageFilling = 0;
	int p = 10103;
	int q = 10133;
	friend hashIterator<TypeKey,TypeData>;
//--------------------------------------------------------------------------------//
	double calculateAverageCollisions() {
		double ans = 0;
		for (int i = 0; i < size(); i++) {
			if(storage[i].size())
				ans += (double)(storage[i].size() - 1);
		}
		return ans;
	}
	double calculatePercentageFilling() {
		double ans = (double)sizeoftable();
		return (ans / size()) * 100;
	}
	bool check() {
		averageCollisions = calculateAverageCollisions();
		percentageFilling = calculatePercentageFilling();
		if ((averageCollisions >= ((double)sizeoftable() / 2))||(percentageFilling > 150)) 
				return true;
		return false;
	}
	void rebalancing(int offset) {
		vector<vector<pair<TypeKey,TypeData>>> new_storage(size() + offset);
		int primeNumbers[10] = { 10103, 10133, 10141, 10169, 10177, 10211, 10243, 10247, 10259, 13187 };
		int last_p = p;
		int last_q = q;
		for (int i = 0; i < 10; i++) {
			if (i == 9) {
				if (primeNumbers[i] == last_p) p = primeNumbers[0];
				else if (primeNumbers[i] == last_q) q = primeNumbers[0];
			}
			else {
				if (primeNumbers[i] == last_p) p = primeNumbers[i + 1];
				else if (primeNumbers[i] == last_q) q = primeNumbers[i + 1];
			}
		}
		int a = sizeoftable();
		for (int i = 0; i < storage.size(); i++) {
			for (int j = 0; j < storage[i].size(); j++) {
				TypeKey key = storage[i][j].first;
				TypeData data = storage[i][j].second;
				int index = HashFunction(key) % new_storage.size();
				
				new_storage[index].push_back(make_pair(key, data));
			}
		}
		//cout << "-1-";
		storage = new_storage;
	}
public:
	int HashFunction(std::string key) { //хэш-функция для string
		int pos = 0;
		int p_step = 2;
		int hashP = p_step;
		for (int i = 0; i < key.size(); i++) {
			pos += key[i] * hashP; // a1*p+a2*p^2+...+a(n-1)*p^(n-1)
			hashP *= p_step;
		}
		return (pos % this->q);
	}
//--------------------------------------------------------------------------------//
	int HashFunction(std::vector<int> key) { //хэш-функция для string
		int pos = 0;
		int p_step = 2;
		int hashP = p_step;
		for (int i = 0; i < key.size(); i++) {
			pos += key[i] * hashP; // a1*p+a2*p^2+...+a(n-1)*p^(n-1)
			hashP *= p_step;
		}
		return (pos % q);
	}
//--------------------------------------------------------------------------------//
	int HashFunction(int key) { // хэш-функция для int
		return (p * key) % q;
	}
//--------------------------------------------------------------------------------//
	int HashFunction(size_t key) { // хэш-функция для int
		size_t p1 = p, q1 = q;
		return (p1 * key) % q1;
	}
//--------------------------------------------------------------------------------//
	int HashFunction(float key) { //хэш-функция для float 
		size_t* a = (size_t*)(&key);
		size_t mask = 1;
		size_t result = 0;
		for (int i = 0; i < 64; i++) {
			if (((size_t)mask & (*a)) != 0)
				result += mask;
			mask << 1;
		}
		return HashFunction(result);
	}
//--------------------------------------------------------------------------------//
	int HashFunction(double key) { //хэш-фукнция для double 
		size_t* a = (size_t*)(&key);
		size_t mask = 1;
		size_t result = 0;
		for (int i = 0; i < 64; i++) {
			if (((size_t)mask & (*a)) != 0)
				result += mask;
			mask << 1;
		}
		return HashFunction(result);

	}
//--------------------------------------------------------------------------------//
	HashTable() {
		storage = vector<vector<pair<TypeKey, TypeData>>>();
	}
	HashTable(const HashTable& other) {
		storage = other.storage;
	}
	~HashTable() {
		storage = vector<vector<pair<TypeKey, TypeData>>>(0);
	}
	HashTable(int size) {
		storage = vector<vector<pair<TypeKey, TypeData>>>(size);
	}
	HashTable& operator=(const HashTable& other) {
		if (this == &other)
			return *this;
		storage = other.storage;
		return *this;
	}
//--------------------------------------------------------------------------------//
	hashIterator<TypeKey, TypeData> insert(const TypeKey& key, const TypeData& data) {
		if (size() == 0) rebalancing(1);
		int index = HashFunction(key) % storage.size();
		for (int i = 0; i < storage[index].size(); i++) {
			if (storage[index][i].first == key) {
				storage[index][i].second = data;
				return hashIterator<TypeKey, TypeData>(storage[index][i],*this);
			}
		}
		storage[index].push_back(make_pair(key, data));
		int a = sizeoftable();
		if (check()) rebalancing(1);
		index = HashFunction(key) % storage.size();
		return hashIterator<TypeKey, TypeData>(storage[index].back(),*this);
	}
//--------------------------------------------------------------------------------//
	TypeData& operator[] (const TypeKey& key) { //оператор []
		int index = HashFunction(key) % storage.size();
		for (int i = 0; i < storage[index].size(); i++) {
			if (storage[index][i].first == key) {
				return storage[index][i].second;
			}
		}
		storage[index].push_back(make_pair(key, TypeData()));
		return storage[index].back().second;
	}
//--------------------------------------------------------------------------------//
	hashIterator<TypeKey, TypeData> find(const TypeKey& key) {
		int index = HashFunction(key) % storage.size();
		for (int i = 0; i < storage[index].size(); i++) {
			if (storage[index][i].first == key) {
				return hashIterator<TypeKey, TypeData>(storage[index][i],*this);
			}
		}
		return end();
	}
//--------------------------------------------------------------------------------//
	bool remove(const TypeKey& key) {
		int index = HashFunction(key) % storage.size();
		for (int i = 0; i < storage[index].size(); i++) {
			if (storage[index][i].first == key) {
				storage[index].erase(storage[index].begin() + i);
				return true;
			}
		}
		if (check()) rebalancing(-1);
		return false;
	}
//--------------------------------------------------------------------------------//
	int size() {
		return storage.size();
	}
//--------------------------------------------------------------------------------//
	int sizeoftable() {
		int sum = 0;
		for (int i = 0; i < size(); i++) {
			sum += storage[i].size();
		}
		return sum;
	}
//--------------------------------------------------------------------------------//
	hashIterator<TypeKey, TypeData> begin() {
		if (storage.empty()) return hashIterator<TypeKey, TypeData>(storage[storage.size() - 1][0],*this);
		int index = 0;
		while (storage[index].size() == 0)
			index++;
		return hashIterator<TypeKey, TypeData>(storage[index][0],*this);
	}
//--------------------------------------------------------------------------------//
	hashIterator<TypeKey, TypeData> end() {
		if (storage.empty()) return hashIterator<TypeKey, TypeData>(storage[storage.size() - 1][0],*this);
		//int index = storage.size()-1;
		//while (storage[index].size() == 0)
		//	index--;
		//return hashIterator<TypeKey, TypeData>(storage[index][storage[index].size() - 1],*this)+1;
		return begin() + sizeoftable();
	}
};

