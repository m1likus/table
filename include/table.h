#include <iostream>
#include <algorithm>

using namespace std;

template <typename TypeKey, typename TypeData>
class Table {
	vector <pair<TypeKey, TypeData>> storage;

	TypeData& operator[] (TypeKey& key) {
		for (int i = 0; i < storage.size(); i++) {
			if (storage[i].first == key)
				return *storage.second;
		}
	}
	Iterator& find(const TypeKey& key) {
		for (int i = 0; i < storage.size(); i++) {
			if (storage[i].first == key)
				return Iterator(&storage[i].second());
		}
		return end;
	}
	Iterator& insert(const TypeKey& key, const TypeData& data) {
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
	}
	Iterator& begin() {
		return Iterator(&storage[0].second());
	}
	Iterator& end() {
		return Iterator(&storage[storage.size()+1].second());
	}

};

template<typename T>
class Iterator {
	friend class Table;
protected:
	T* iterator;
public:
	T& operator*() const {
		return *iterator;
	}
	T* operator->() const {
		return iterator;
	}
	Iterator& operator++() {
		iterator++;
		return *this;
	}
	Iterator& operator--() {
		iterator--;
		return *this;
	}

};
