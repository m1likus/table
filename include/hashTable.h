#pragma once

#include <string>
#include "table.h"
#include <math.h>

template<typename TypeKey, typename T>
class hashIterator; //объявление итератора для hashTable

template<typename TypeKey,typename TypeData>
class HashTable : public baseTable<TypeKey, TypeData> {
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
		return (p1*key)%p2;
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
//--------------------------------------------------------------------------------//
public:
	HashTable(int size) {
		storage = vector<vector<pair<TypeKey, TypeData>>>(size);
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
	//итератор на начало
	hashIterator<TypeKey, TypeData> begin() {
		//TODO
	}
//--------------------------------------------------------------------------------//
	//итератор на конец
	hashIterator<TypeKey, TypeData> end() {
		//TODO
	}
//--------------------------------------------------------------------------------//
};

template<typename TypeKey, typename T>
class hashIterator : public Iterator<TypeKey,T> {
	friend class HashTable<TypeKey, T>;
protected: 
	pair<TypeKey, T>* iterator;
public:
	hashIterator(pair<TypeKey, T>& data) {
		iterator = &data;
	}
	hashIterator(const hashIterator& other) { 
		iterator = other.iterator;
	}
	T& operator*() const override { 
		return iterator->second;
	}
	T* operator->() const override { 
		return iterator.second;
	}
	hashIterator& operator++() {
		//TODO
	}



};
