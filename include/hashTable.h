#pragma once

#include <string>
#include "table.h"
#include <math.h>


template<typename TypeKey,typename TypeData>
class HashTable {
protected:
	vector<vector<pair<TypeKey, TypeData>>> storage;
	double averageCollisions = 0;
	double percentageFilling = 0;
	int p = 10103;
	int q = 10133;
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
	int HashFunction(std::string key) { //���-������� ��� string
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
	int HashFunction(std::vector<int> key) { //���-������� ��� string
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
	int HashFunction(int key) { // ���-������� ��� int
		return (p * key) % q;
	}
	//--------------------------------------------------------------------------------//
	int HashFunction(size_t key) { // ���-������� ��� int
		size_t p1 = p, q1 = q;
		return (p1 * key) % q1;
	}
	//--------------------------------------------------------------------------------//
	int HashFunction(float key) { //���-������� ��� float 
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
	int HashFunction(double key) { //���-������� ��� double 
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

	template<typename TypeKey, typename T>
	class hashIterator {
	protected:
		pair<TypeKey, T>* iterator;
	public:
		hashIterator(pair<TypeKey, T>& data) {
			iterator = &data;
		}
		hashIterator(const hashIterator& other) {
			iterator = other.iterator;
		}
		T& operator*() const {
			return iterator->second;
		}
		T* operator->() const {
			return iterator.second;
		}
		hashIterator& operator++() {
			int index1 = HashFunction(iterator.first) % storage.size();
			int index2;
			for (int index2 = 0; index2 < &storage[index1].size(); index2++) {
				if (storage[index1][index2].first == iterator.first) {
					break;
				}
			}
			if (index2 < storage[index1].size() - 1)
				index2++;
			else {
				index1 = (index1 + 1) % storage.size();
				while (storage[index1].size() == 0)
					index1 = (index1 + 1) % storage.size();
				index2 = 0;
			}
			iterator = &storage[index1][index2];
			return *this;
		}
		hashIterator& operator--() {
			int index1 = HashFunction(iterator.first) % storage.size();
			int index2;
			for (int index2 = 0; index2 < storage[index1].size(); index2++) {
				if (storage[index1][index2].first == iterator.first) {
					break;
				}
			}
			if (index2 > 0)
				index2--;
			else {
				index1 = (storage.size() + index1 - 1) % storage.size();
				while (storage[index1].size() == 0)
					index1 = (storage.size() + index1 - 1) % storage.size();
				index2 = storage[index1]size() - 1;
			}
			iterator = &storage[index1][index2];
			return *this;
		}
		hashIterator operator+(int offset) {
			hashIterator<TypeKey, T> tmp = *this;
			for (int i = 0; i < offset; i++) {
				tmp++;
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
	//--------------------------------------------------------------------------------//
public:
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
		int index = HashFunction(key) % storage.size();
		for (int i = 0; i < storage[index].size(); i++) {
			if (storage[index][i].first == key) {
				storage[index][i].second = data;
				return hashIterator<TypeKey, TypeData>(storage[index][i]);
			}
		}
		storage[index].push_back(make_pair(key, data));
		int a = sizeoftable();
		if (check()) rebalancing(1);
		index = HashFunction(key) % storage.size();
		return hashIterator<TypeKey, TypeData>(storage[index].back());
	}
	//--------------------------------------------------------------------------------//
	TypeData& operator[] (const TypeKey& key) { //�������� []
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
				return hashIterator<TypeKey, TypeData>(storage[index][i]);
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
		if (storage.empty()) return hashIterator<TypeKey, TypeData>(storage[storage.size() - 1][0]);
		int index = 0;
		while (storage[index].size() == 0)
			index++;
		return hashIterator<TypeKey, TypeData>(storage[index][0]);
	}
	//--------------------------------------------------------------------------------//
	hashIterator<TypeKey, TypeData> end() {
		if (storage.empty()) return hashIterator<TypeKey, TypeData>(storage[storage.size() - 1][0]);
		int index = storage.size();
		while (storage[index].size() == 0)
			index++;
		return hashIterator<TypeKey, TypeData>(storage[index][storage[index].size() - 1]);
	}

};


//--------------------------------------------------------------------------------//
//template<typename TypeKey,typename TypeData>
//class HashTable : public baseTable<TypeKey, TypeData> {
//protected:
//	vector<vector<pair<TypeKey, TypeData>>> storage;
////--------------------------------------------------------------------------------//
//	int HashFunction(std::string key) { //���-������� ��� string
//		int pos = 0;
//		int p_step = 2;
//		int p = p_step;
//		for (int i = 0; i < key.size(); i++) {
//			pos += key[i] * p; // a1*p+a2*p^2+...+a(n-1)*p^(n-1)
//			p *= p_step;
//		}
//		int q = 1009;
//		return (pos % q);
//	}
////--------------------------------------------------------------------------------//
//	int HashFunction(int key) { // ���-������� ��� int
//		int p1 = 7193, p2 = 1213;
//		return (p1*key)%p2;
//	}
////--------------------------------------------------------------------------------//
//	int HashFunction(float key) { //���-������� ��� float 
//		float mantissa = frexp(key); //frexp returns number's mantissa
//		int p = mantissa * 1000000000;
//		return (HashFunction(p));
//	}
////--------------------------------------------------------------------------------//
//	int HashFunction(double key) { //���-������� ��� double
//		double mantissa = frexp(key);
//		int p = mantissa * 1000000000;
//		return (HashFunction(p));
//	}
////--------------------------------------------------------------------------------//
//	Iterator<TypeKey, TypeData>& operator++() {
//
//		return Iterator<TypeKey, TypeData>::iterator;
//	}
//public:
//	HashTable(int size) {
//		storage = vector<vector<pair<TypeKey, TypeData>>>(size);
//	}
////--------------------------------------------------------------------------------//
//	Iterator<TypeKey, TypeData> insert(const TypeKey& key, const TypeData& data) {
//		int index = HashFunction(key)%storage.size();
//		for (int i = 0; i < storage[index].size(); i++) {
//			if (storage[index][i].first == key) {
//				storage[index][i].second = data;
//				return Iterator<TypeKey, TypeData>(storage[index][i]);
//			}
//		}
//		storage[index].push_back(make_pair(key, data));
//		return Iterator<TypeKey, TypeData>(storage[index].back());
//	}
////--------------------------------------------------------------------------------//
//	TypeData& operator[] (const TypeKey& key) { //�������� []
//		int index = HashFunction(key)%storage.size(); 
//		for (int i = 0; i < storage[index].size(); i++) {
//			if (storage[index][i].first == key) {
//				return storage[index][i].second;
//			}
//		}
//		storage[index].push_back(make_pair(key, TypeData()));
//		return storage[index].back().second;
//	}
////--------------------------------------------------------------------------------//
//	Iterator<TypeKey, TypeData> find(const TypeKey& key) {
//		int index = HashFunction(key)%storage.size();
//		for (int i = 0; i < storage[index].size(); i++) {
//			if (storage[index][i].first == key) {
//				return Iterator<TypeKey, TypeData>(storage[index][i]);
//			}
//		}
//		return end(); 
//	}
////--------------------------------------------------------------------------------//
//	bool remove(const TypeKey& key) {
//		int index = HashFunction(key) % storage.size();
//		for (int i = 0; i < storage[index].size(); i++) {
//			if (storage[index][i].first == key) {
//				storage[index].erase(storage[index].begin() + i);
//				return true;
//			}
//		}
//		return false;
//	}
////--------------------------------------------------------------------------------//
//	int size() {
//		return storage.size();
//	}
////--------------------------------------------------------------------------------//
//	int sizeoftable() {
//		int sum = 0;
//		for (int i = 0; i < size(); i++) {
//			sum += storage[i].size();
//		}
//		return sum;
//	}
////--------------------------------------------------------------------------------//
//	//�������� �� ������
//	Iterator<TypeKey, TypeData> begin() {
//		if (storage.empty()) return (storage[0][0] + sizeoftable());
//		for (int i = 0; i < storage.size(); i++) {
//			if (!storage[i].empty()) {
//				return Iterator::iterator(storage[i].begin());
//			}
//		}
//	}
////--------------------------------------------------------------------------------//
//	//�������� �� �����
//	Iterator<TypeKey, TypeData> end() {
//		if (storage.empty()) return (storage[0][0] + sizeoftable());
//		for (int i = storage.size(); i > 0; i--) {
//			if (!storage[i].empty()) {
//				return Iterator::iterator(storage[i].end());
//			}
//		}
//	}
////--------------------------------------------------------------------------------//
//	
//};
