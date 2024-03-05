#pragma once

#include "table.h"

template<typename TypeKey, typename TypeData>
class SortTable : public Table<TypeKey, TypeData> {
public:
	SortTable(){}
	SortTable(int s): Table<TypeKey, TypeData>(s){}
	Iterator<TypeKey, TypeData> insert(const TypeKey& key, const TypeData& data)  {
		//...
		for (int i = 0; i < storage.size(); i++) {
			if (storage[i].first > key) {
				storage.insert(storage.begin() + i, make_pair(key, data));
				return Table<TypeKey, TypeData>::begin() + i;
			}
		}
		int x = storage.size();
		storage.insert(storage.begin() + x, make_pair(key, data));
		return Table<TypeKey, TypeData>::begin() + x;
	}
	TypeData& operator[] (const TypeKey& key) { //оператор []
		for (int i = 0; i < storage.size(); i++) {
			if (storage[i].first == key) //если нашли ключ
				return storage[i].second; //возвращаем данные
		}
		//если нет, то создаем данные с таким ключом
		insert(key, TypeData());
		//и возвращаем их
		return *find(key);
	}
};