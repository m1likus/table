#pragma once

#include <string>
#include "table.h"
#include <math.h>


template<typename TypeKey,typename TypeData>
class HashTable{
protected:
	vector<vector<pair<TypeKey, TypeData>>> storage;
//--------------------------------------------------------------------------------//
	int HashFunction(std::string key) { //хэш-функция для string
		int pos = 0;
		int p_step = 2;
		int p = p_step;
		for (int i = 0; i < key.size(); i++) {
			pos += key[i] * p; // a1*p+a2*p^2+...+a(n-1)*p^(n-1)
			p *= p_step;
		}
		int q = 1009;
		return (pos % q);
	}
//--------------------------------------------------------------------------------//
	int HashFunction(int key) { // хэш-функция для int
		int p1 = 7193, p2 = 1213;
		return (p1 * key) % p2;
	}
//--------------------------------------------------------------------------------//
	int HashFunction(float key) { //хэш-функция для float 
		float mantissa = frexp(key); //frexp returns number's mantissa
		int p = mantissa * 1000000000;
		return (HashFunction(p));
	}
//--------------------------------------------------------------------------------//
	int HashFunction(double key) { //хэш-фукнция для double
		double mantissa = frexp(key);
		int p = mantissa * 1000000000;
		return (HashFunction(p));
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
		//было
		/*hashIterator& operator++() {
			iterator++;
			return *this;
		}*/
		//стало
		hashIterator operator++() {
			hashIterator<TypeKey, T> tmp = *this;
			//todo
			return tmp;
		}
		hashIterator& operator--() {
			iterator--;
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
		int index = HashFunction(key)%storage.size();
		for (int i = 0; i < storage[index].size(); i++) {
			if (storage[index][i].first == key) {
				storage[index][i].second = data;
				return hashIterator<TypeKey, TypeData>(storage[index][i]);
			}
		}
		storage[index].push_back(make_pair(key, data));
		return hashIterator<TypeKey, TypeData>(storage[index].back());
	}
//--------------------------------------------------------------------------------//
	TypeData& operator[] (const TypeKey& key) { //оператор []
		int index = HashFunction(key)%storage.size(); 
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
		int index = HashFunction(key)%storage.size();
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
		if (storage.empty()) return (storage[0][0] + sizeoftable());
		for (int i = 0; i < storage.size(); i++) {
			if (!storage[i].empty()) {
				return hashIterator::iterator(storage[i][*storage.begin()]);
			}
		}
	}
//--------------------------------------------------------------------------------//
	hashIterator<TypeKey, TypeData> end() {
		if (storage.empty()) return (storage[0][0] + sizeoftable());
		for (int i = storage.size(); i > 0; i--) {
			if (!storage[i].empty()) {
				return hashIterator::iterator(storage[i][*storage.end()]);
			}
		}
	}


};


//--------------------------------------------------------------------------------//
//template<typename TypeKey,typename TypeData>
//class HashTable : public baseTable<TypeKey, TypeData> {
//protected:
//	vector<vector<pair<TypeKey, TypeData>>> storage;
////--------------------------------------------------------------------------------//
//	int HashFunction(std::string key) { //хэш-функция для string
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
//	int HashFunction(int key) { // хэш-функция для int
//		int p1 = 7193, p2 = 1213;
//		return (p1*key)%p2;
//	}
////--------------------------------------------------------------------------------//
//	int HashFunction(float key) { //хэш-функция для float 
//		float mantissa = frexp(key); //frexp returns number's mantissa
//		int p = mantissa * 1000000000;
//		return (HashFunction(p));
//	}
////--------------------------------------------------------------------------------//
//	int HashFunction(double key) { //хэш-фукнция для double
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
//	TypeData& operator[] (const TypeKey& key) { //оператор []
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
//	//итератор на начало
//	Iterator<TypeKey, TypeData> begin() {
//		if (storage.empty()) return (storage[0][0] + sizeoftable());
//		for (int i = 0; i < storage.size(); i++) {
//			if (!storage[i].empty()) {
//				return Iterator::iterator(storage[i].begin());
//			}
//		}
//	}
////--------------------------------------------------------------------------------//
//	//итератор на конец
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
