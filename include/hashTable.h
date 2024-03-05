#pragma once

#include <string>
#include "table.h"

template<typename TypeKey,typename TypeData>
class HashTable : public baseTable<TypeKey, TypeData> {
protected:
	vector<vector<pair<TypeKey, TypeData>>> storage;

	int HashFunction(std::string key) {
		int index = 0;
		int p_step = 2;
		int p = p_step;
		for (int i = 0; i < key.size(); i++) {
			index += key[i] * p;
			p *= p_step;
		}
		return index % 1001;
	}
	int HashFunction(int key) {
		return key;
	}

public:
	HashTable(int size) {
		storage = vector<vector<pair<TypeKey, TypeData>>>(size);
	}
	Iterator<TypeKey, TypeData> insert(const TypeKey& key, const TypeData& data) {
		//...
		int index = HashFunction(key)%storage.size();
		for (int i = 0; i < storage[index].size(); i++) {
			if (storage[index][i].first == key) {
				storage[index][i].second = data;
				return Iterator<TypeKey, TypeData>(storage[index][i]);
			}
		}
		storage[index].push_back(make_pair(key, data));
		return Iterator<TypeKey, TypeData>(storage[index].back());
	}
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
	Iterator<TypeKey, TypeData> find(const TypeKey& key) {
		int index = HashFunction(key)%storage.size();
		int it = 0;
		for (int i = 0; i < storage[index].size(); i++) {
			if (storage[index][i].first == key) {
				return Iterator<TypeKey, TypeData>(storage[index][i]);
			}
		}
		return end(); //иначе возвращаем итератор на конец
	}
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
	int size() {
		return storage.size();
	}
	//--------------------------------------------------------------------------------//
	//итератор на начало
	Iterator<TypeKey, TypeData> begin() {
		return Iterator<TypeKey, TypeData>(storage[0][0]);
	}
	//--------------------------------------------------------------------------------//
		//итератор на конец
	Iterator<TypeKey, TypeData> end() {
		Iterator<TypeKey, TypeData> a = begin();
		return a + storage.size();
	}
	//--------------------------------------------------------------------------------//
};