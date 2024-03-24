#pragma once
#include "iterator.hpp"
#include <iostream>
using namespace std;

//--------------------------------------------------------------------------------//
template<typename TypeKey, typename TypeData>
TableImpl<TypeKey, TypeData>::TableImpl(){
	iterator = 0;
};
//--------------------------------------------------------------------------------//
template<typename TypeKey, typename TypeData>
TableImpl<TypeKey, TypeData>::TableImpl(pair<TypeKey, TypeData>& data) {
	iterator = &a;
};
//--------------------------------------------------------------------------------//
//template<typename TypeKey, typename TypeData>
//TypeData& TableImpl<TypeKey, TypeData>::operator*() const {
//	return iterator->second;
//}
//--------------------------------------------------------------------------------//
//template<typename TypeKey, typename TypeData>
//TypeData* TableImpl<TypeKey, TypeData>::operator->() const {
//	return iterator.second;
//}
//--------------------------------------------------------------------------------//
template<typename TypeKey, typename TypeData>
Impl<TypeKey, TypeData>& TableImpl<TypeKey, TypeData>::operator++() {
	iterator++;
	return *this;
}
//--------------------------------------------------------------------------------//
template<typename TypeKey, typename TypeData>
Impl<TypeKey, TypeData>& TableImpl<TypeKey, TypeData>::operator--() {
	iterator--;
	return *this;
}
//--------------------------------------------------------------------------------//
template<typename TypeKey, typename TypeData>
Impl<TypeKey, TypeData> TableImpl<TypeKey, TypeData>::operator+(int offset) {
	iterator = iterator + offset;
	return *this;
}
//--------------------------------------------------------------------------------//
template<typename TypeKey, typename TypeData>
bool TableImpl<TypeKey, TypeData>::operator==(const Impl<TypeKey, TypeData>& other) {
	if (iterator == other.iterator)
		return true;
	return false;
}
//--------------------------------------------------------------------------------//
template<typename TypeKey, typename TypeData>
bool TableImpl<TypeKey, TypeData>::operator!=(const Impl<TypeKey, TypeData>& other) {
	if (iterator != other.iterator)
		return true;
	return false;
}
//--------------------------------------------------------------------------------//
template<typename TypeKey, typename TypeData>
TableIterator<TypeKey, TypeData>::TableIterator() {
	p = new TableImpl();
}
//--------------------------------------------------------------------------------//
template<typename TypeKey, typename TypeData>
TableIterator<TypeKey, TypeData>::TableIterator(pair<TypeKey, TypeData>& data) {
	p = new TableImpl(a);
}
//--------------------------------------------------------------------------------//
template<typename TypeKey, typename TypeData>
TableIterator<TypeKey, TypeData>::TableIterator(const TableIterator& other) {
	p(other.p);
}
//--------------------------------------------------------------------------------//
//template<typename TypeKey, typename TypeData>
//TypeData& TableIterator<TypeKey, TypeData>::operator*() const {
//	return p->operator*;
//}
//--------------------------------------------------------------------------------//
//template<typename TypeKey, typename TypeData>
//TypeData* TableIterator<TypeKey, TypeData>::operator->() const {
//	return p*;
//}
//--------------------------------------------------------------------------------//
template<typename TypeKey, typename TypeData>
Iterator<TypeKey, TypeData>& TableIterator<TypeKey, TypeData>::operator++() {
	p->operator++;
	return *this;
}
//--------------------------------------------------------------------------------//
template<typename TypeKey, typename TypeData>
Iterator<TypeKey, TypeData>& TableIterator<TypeKey, TypeData>::operator--() {
	p->operator--;
	return *this;
}
//--------------------------------------------------------------------------------//
template<typename TypeKey, typename TypeData>
Iterator<TypeKey, TypeData> TableIterator<TypeKey, TypeData>::operator+(int offset) {
	p->operator+(offset);
	return this;
}
//--------------------------------------------------------------------------------//
template<typename TypeKey, typename TypeData>
bool TableIterator<TypeKey, TypeData>::operator==(const Iterator<TypeKey, TypeData>& other) {
	if (p == other.p)
		return true;
	return false;
}
//--------------------------------------------------------------------------------//
template<typename TypeKey, typename TypeData>
bool TableIterator<TypeKey, TypeData>::operator!=(const Iterator<TypeKey, TypeData>& other) {
	if (p != other.p)
		return true;
	return false;
}