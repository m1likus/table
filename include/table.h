#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template<typename TypeKey, typename T>
class Iterator; //объявление класса итератора

template <typename TypeKey, typename TypeData>
class Table {
protected:
	vector <pair<TypeKey, TypeData>> storage;
public:
//--------------------------------------------------------------------------------//
	Table() { //конструктор по умолчанию
		storage = vector<pair<TypeKey, TypeData>>;
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
	~Table() { //деструктор
		storage=vector<pair<TypeKey, TypeData>>(0);
	}
//--------------------------------------------------------------------------------//
	Table& operator=(const Table& other) { //оператор присваивания
		if (this == other)
			return *this;
		storage = other.storage;
		return this*;
	}
//--------------------------------------------------------------------------------//
	TypeData& operator[] (TypeKey& key) { //оператор []
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
	Iterator<TypeKey, TypeData>& find(const TypeKey& key) { 
		for (int i = 0; i < storage.size(); i++) {
			if (storage[i].first == key) //нашли ключ
				return begin() + i; //возвращаем ссылку на итератор
		}
		return end(); //иначе возвращаем итератор на конец
	}
//--------------------------------------------------------------------------------//
	Iterator<TypeKey, TypeData>& insert(const TypeKey& key, const TypeData& data) {
		//...
		for (int i = 0; i < storage.size(); i++) {
			if (storage[i].first == key) //нашли ключ, перед к-ым надо вставить
				storage.insert(i, make_pair(key, data)); //вставили
			return begin() + i; // ...
		}
	}
//--------------------------------------------------------------------------------//
	//возвращаем true/false
	bool remove(const TypeKey& key) {
		for (int i = 0; i < storage.size(); i++) {
			if (storage[i].first == key) //нашли 
				storage.erase(i); //убрали
			return true;
		}
		return false;
	}
//--------------------------------------------------------------------------------//
	//итератор на начало
	Iterator<TypeKey, TypeData>& begin() {
		return Iterator<TypeKey, TypeData>(storage[0]);
	}
//--------------------------------------------------------------------------------//
	//итератор на конец
	Iterator<TypeKey, TypeData>& end() {
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
	Iterator() { //конструктор по умолчанию
		iterator = nullptr;
	}
//--------------------------------------------------------------------------------//
	Iterator(pair<TypeKey, T>& data) { //конструктор с параметрами
		iterator = &data;
	}
//--------------------------------------------------------------------------------//
	Iterator(const Iterator& other) { //конструктор копирования
		iterator = other.iterator;
	}
//--------------------------------------------------------------------------------//
	~Iterator() { //деструктор
		delete iterator;
	}
//--------------------------------------------------------------------------------//
	T& operator*() const { //получение элемента, на который указывает итератор
		return iterator->second;
	}
//--------------------------------------------------------------------------------//
	T* operator->() const { //->
		return iterator.second;
	}
//--------------------------------------------------------------------------------//
	Iterator& operator++() {
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

template<typename TypeKey, typename TypeData>
class SortTable : protected Table {
	//+сделай пж вывод для table и sort table
};
