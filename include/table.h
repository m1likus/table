#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
template<typename TypeKey, typename T>
class Iterator {
	friend class Table;
protected:
	pair<TypeKey, T>* iterator;
public:
	Iterator(pair<TypeKey, T>& data) {
		iterator = &data;
	}

	T& operator*() const {
		return iterator->second;
	}
	/* TODO: dodelac
	T& operator->() const {
		return *iterator;
	}*/
	Iterator& operator++() {
		iterator++;
		return *this;
	}
	Iterator& operator--() {
		iterator--;
		return *this;
	}
	Iterator operator+(int offset) {
		Iterator<T> tmp = *this;
		tmp.iterator += offset;
	}
};

template <typename TypeKey, typename TypeData>
class Table {
	vector <pair<TypeKey, TypeData>> storage;

	TypeData& operator[] (TypeKey& key) {
		for (int i = 0; i < storage.size(); i++) {
			if (storage[i].first == key)
				return *storage.second;
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
	Iterator& begin() {
		return Iterator(storage[0]);
	}
	Iterator& end() {
		return begin() + storage.size();
	}

};

