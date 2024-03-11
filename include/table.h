#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


template<typename TypeKey, typename T>
class Iterator; //объявление итератора для table, sortTable


template <typename TypeKey, typename TypeData>
class baseTable {
public:
	virtual Iterator<TypeKey, TypeData> find(const TypeKey& key)=0;
	virtual Iterator<TypeKey, TypeData> insert(const TypeKey& key, const TypeData& data)=0;
	virtual bool remove(const TypeKey& key)=0;
	virtual Iterator<TypeKey, TypeData> begin()=0;
	virtual Iterator<TypeKey, TypeData> end()=0;
	virtual int size() = 0;
};

template <typename TypeKey, typename TypeData>
class Table : public baseTable<TypeKey,TypeData>{
protected:
	vector <pair<TypeKey, TypeData>> storage;
public:
//--------------------------------------------------------------------------------//
	Table() { //конструктор по умолчанию
		storage = vector<pair<TypeKey, TypeData>>();
	}
//--------------------------------------------------------------------------------//
	Table(int size) { //конструктор с параметрами
		storage = vector<pair<TypeKey, TypeData>>(size);
	}
//--------------------------------------------------------------------------------//
	Table(const Table& other) { //конструктор копирования
		storage = other.storage;
	}
//--------------------------------------------------------------------------------//
	virtual ~Table() { //деструктор
		storage.clear();
	}
//--------------------------------------------------------------------------------//
	Table& operator=(const Table& other) { //оператор присваивания
		if (this == &other)
			return *this;
		storage = other.storage;
		return *this;
	}
//--------------------------------------------------------------------------------//
	virtual TypeData& operator[] (const TypeKey& key) { //оператор []
		for (int i = 0; i < storage.size(); i++) {
			if (storage[i].first == key) //если нашли ключ
				return storage[i].second; //возвращаем данные
		}
		//если нет, то создаем данные с таким ключом
		storage.push_back(make_pair(key, TypeData())); 
		//и возвращаем их
		return storage.back().second;
	}
//--------------------------------------------------------------------------------//
	//возвращаемое значение - ссылка на итератор на найденный элемент
	Iterator<TypeKey, TypeData> find(const TypeKey& key) { 
		for (int i = 0; i < storage.size(); i++) {
			if (storage[i].first == key) //нашли ключ
				return begin() + i; //возвращаем ссылку на итератор
		}
		return end(); //иначе возвращаем итератор на конец
	}
	int size() {
		return storage.size();
	}
//--------------------------------------------------------------------------------//
	Iterator<TypeKey, TypeData> insert(const TypeKey& key, const TypeData& data) {
		int i = storage.size();
		storage.push_back(make_pair(key, data));
		i--;
		return begin() + i;
	}
//--------------------------------------------------------------------------------//
	bool remove(const TypeKey& key) {
		for (int i = 0; i < storage.size(); i++) {
			if (storage[i].first == key) { //нашли 
				storage.erase(storage.begin()+i); //убрали
				return true;
			}
		}
		return false;
	}
//--------------------------------------------------------------------------------//
	//итератор на начало
	Iterator<TypeKey, TypeData> begin() {
		return Iterator<TypeKey, TypeData>(storage[0]);
	}
//--------------------------------------------------------------------------------//
	//итератор на конец
	Iterator<TypeKey, TypeData> end() {
		Iterator<TypeKey, TypeData> a = begin();
		return a + storage.size();
	}
//--------------------------------------------------------------------------------//
};

template<typename TypeKey, typename T>
class Iterator {
	friend class Table< TypeKey, T>; //https://ru.cppreference.com/w/cpp/language/friend
protected:
	pair<TypeKey, T>* iterator;
public:
//--------------------------------------------------------------------------------//
	Iterator(pair<TypeKey, T>& data) { //конструктор с параметрами
		iterator = &data;
	}
//--------------------------------------------------------------------------------//
	Iterator(const Iterator& other) { //конструктор копирования
		iterator = other.iterator;
	}
//---------------------------------------------------------------------//
	T& operator*() const { //получение элемента, на который указывает итератор
		return iterator->second;
	}
//--------------------------------------------------------------------------------//
	T* operator->() const { //->
		return iterator.second;
	}
//--------------------------------------------------------------------------------//
	virtual Iterator& operator++() {
		iterator++;
		return *this;
	}
//--------------------------------------------------------------------------------//
	Iterator& operator--() {
		iterator--;
		return *this;
	}
//--------------------------------------------------------------------------------//
	Iterator operator+(int offset) { //смещение
		Iterator<TypeKey, T> tmp = *this;
		tmp.iterator += offset;
		return tmp;
	}
//--------------------------------------------------------------------------------//
	bool operator==(const Iterator& other) {
		return iterator == other.iterator;
	}
//--------------------------------------------------------------------------------//
	bool operator!=(const Iterator& other) {
		return iterator != other.iterator;
	}
//--------------------------------------------------------------------------------//
};