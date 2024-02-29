#include <string>

template<typename TypeKey,typename TypeData>
class HashTable : public Table<TypeKey, TypeData> {
private:
	int HashFunction(TypeKey key) {
		if (typeid(TypeKey) == typeid(string)) {
			int index = 0;
			int p_step = storage.size() - 1;
			int p = p_step;
			for (int i = 0; i < key.size(); i++) {
				index += key[i] * p;
				p *= p_step;
			}
			return index % storage.size();
		}
	}

	int HashFunctionStep(TypeKey key) {
		//int index = 0;
		//for (int i = 0; i < key.size(); i++) {
		//	index += key[i];
		//}
		//return index;
		return storage.size()-1;
	}
public:
	HashTable(int size) : Table<TypeKey, TypeData>(size) {}
	Iterator<TypeKey, TypeData> insert(const TypeKey& key, const TypeData& data) {
		//...
		int index = HashFunction(key);
		int step = HashFunctionStep(key);
		while (storage[index].first != "" && storage[index].first != key)
			index = (index + step) % storage.size();
		if (storage[index].first == "")
			storage[index] = make_pair(key, data);
		else if (storage[index].first == key) {
			storage[index].second = data;
		}
		return Table<TypeKey, TypeData>::begin() + index;
	}
	TypeData& operator[] (const TypeKey& key) { //оператор []
		int index = HashFunction(key);
		int step = HashFunctionStep(key);
		while(storage[index].first!=key)
			index = (index + step) % storage.size();		
		return storage[index].second;
	}
	Iterator<TypeKey, TypeData> find(const TypeKey& key) {
		int index = HashFunction(key);
		int step = HashFunctionStep(key);
		int it = 0;
		while (storage[index].first != key && it < storage.size()) {
			index = (index + step) % storage.size();
			it++;
		}
		if(it < storage.size())
			return Table<TypeKey, TypeData>::begin() + index;
		return Table<TypeKey, TypeData>::end(); //иначе возвращаем итератор на конец
	}
	bool remove(const TypeKey& key) {
		int index = HashFunction(key);
		int step = HashFunctionStep(key);
		int it = 0;
		while (storage[index].first != key && it < storage.size()) {
			index = (index + step) % storage.size();
			it++;
		}
		if (it < storage.size()) {
			storage[index] = make_pair(NULL, NULL);
			return true;
		}
		return false;
	}
};