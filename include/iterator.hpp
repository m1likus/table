#pragma once
#include <iostream>
#include "iterator.cpp"

using namespace std;

template<typename TypeKey, typename TypeData>
class Iterator;

template<typename TypeKey, typename TypeData>
class Impl {
private:
	pair<TypeKey, TypeData>* iterator;
public:
	//virtual TypeData& operator*() const = 0;
	//virtual TypeData* operator->() const = 0;
	virtual Impl& operator++() = 0;
	virtual Impl& operator--() = 0;
	virtual Impl operator+(int offset) = 0;
	virtual bool operator==(const Impl& other) = 0;
	virtual bool operator!=(const Impl& other) = 0;
};

template<typename TypeKey, typename TypeData>
class TableImpl : public Impl<TypeKey, TypeData> {
public:
	TableImpl();
	TableImpl(pair<TypeKey, TypeData>& data);
	virtual ~TableImpl() { delete iterator; };
	//TypeData& operator*() const;
	//TypeData* operator->() const;
	Impl& operator++();
	Impl& operator--();
	Impl operator+(int offset);
	bool operator==(const Impl& other);
	bool operator!=(const Impl& other);
};

template<typename TypeKey, typename TypeData>
class Iterator {
private:
	Impl<TypeKey, TypeData>* p;
public:
	//virtual TypeData& operator*() const = 0;
	//virtual TypeData* operator->() const = 0;
	virtual Iterator& operator++() = 0;
	virtual Iterator& operator--() = 0;
	virtual Iterator operator+(int offset) = 0;
	virtual bool operator==(const Iterator& other) = 0;
	virtual bool operator!=(const Iterator& other) = 0;

};

template<typename TypeKey, typename TypeData>
class TableIterator : public Iterator<TypeKey, TypeData> {
public:
	TableIterator();
	TableIterator(pair<TypeKey, TypeData>& data);
	TableIterator(const TableIterator& other);
	virtual ~TableIterator() { delete p; }
	//TypeData& operator*() const;
	//TypeData* operator->() const;
	Iterator& operator++();
	Iterator& operator--();
	Iterator operator+(int offset);
	bool operator==(const Iterator& other);
	bool operator!=(const Iterator& other);
};