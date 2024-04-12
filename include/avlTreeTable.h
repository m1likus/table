#pragma once

#include "binTreeTable.h"

template <typename TypeKey, typename TypeData>
class AvlTreeTable : public BinTreeTable<TypeKey, TypeData> {
private:
	void check() {
	}
public:
	//--------------------------------------------------------------------------------//
	binTreeIterator<TypeKey, TypeData> insert(const TypeKey& key, const TypeData& d) {
		auto r = BinTreeTable<TypeKey, TypeData>::insert(key, d);
		check();
		return r;
	}
//--------------------------------------------------------------------------------//
	bool remove(const TypeKey& key) {
		auto r = BinTreeTable<TypeKey, TypeData>::remove(key);
		check();
		return r;
	}
//--------------------------------------------------------------------------------//
};