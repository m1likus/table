#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template<typename TypeKey, typename T>
class Iterator;

template <typename TypeKey, typename TypeData>
class Table {
	vector <pair<TypeKey, TypeData>> storage;
public:
	Table() {
		storage = vector<pair<TypeKey, TypeData>>;
	}
	Table(int size) {
		storage = vector<pair<TypeKey, TypeData>>(size);
	}
	
	Table(const Table& other) {
		storage = other.storage;
	}
	~Table() {
		storage=vector<pair<TypeKey, TypeData>>(0);
	}

	Table& operator=(const Table& other) {
		if (this != other)
			return *this;
		storage = other.storage;
		return this*;
	}
	TypeData& operator[] (TypeKey& key) {
		for (int i = 0; i < storage.size(); i++) {
			if (storage[i].first == key)
				return storage[i].second;
		}
		storage.push_back(make_pair(key, TypeData()));
		return storage.back().second;
	}

	Iterator<TypeKey, TypeData>& find(const TypeKey& key) {
		for (int i = 0; i < storage.size(); i++) {
			if (storage[i].first == key)
				return begin() + i;
		}
		return end();
	}
	/*Iterator& insert(const TypeKey& key, const TypeData& data) {
		for (int i = 0; i < storage.size(); i++) {
			if (storage[i].first == key)
				storage.insert(i, <key, data>);
			return Iterator(&storage[i].second());
		}
		
	}
	bool remove(const TypeKey& key) {
		for (int i = 0; i < storage.size(); i++) {
			if (storage[i].first == key)
				storage.erase(i);
			return true;
		}
		return false;
	}*/
	Iterator<TypeKey, TypeData>& begin() {
		return Iterator<TypeKey, TypeData>(storage[0]);
	}
	Iterator<TypeKey, TypeData>& end() {
		Iterator<TypeKey, TypeData> a = begin();
		return a + storage.size();
	}

};

template<typename TypeKey, typename T>
class Iterator {
	friend class Table< TypeKey, T>;
protected:
	pair<TypeKey, T>* iterator;
public:
	Iterator(pair<TypeKey, T>& data) {
		iterator = &data;
	}

	T& operator*() const {
		return iterator->second;
	}
	// TODO: dodelac
	T& operator->() const {
		return *iterator.second;
	}
	Iterator& operator++() {
		iterator++;
		return *this;
	}
	Iterator& operator--() {
		iterator--;
		return *this;
	}
	Iterator operator+(int offset) {
		Iterator<TypeKey, T> tmp = *this;
		tmp.iterator += offset;
		return tmp;
	}
	bool operator==(const Iterator& other) {
		if (iterator == other.iterator)
			return true;
		return false;
	}
	bool operator!=(const Iterator& other) {
		if (iterator != other.iterator)
			return true;
		return false;
	}
};
