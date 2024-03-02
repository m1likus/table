template <typename TypeKey, typename TypeData>
class Node {
	TypeData data;
	TypeKey key;
	Node* left;
	Node* right;
	Node* parent;
	
	bool operator==(const Node& other) {
		if (key == other.key && data == other.data)
			return true;
		return false;
	}
	
	bool operator!=(const Node& other) {
		return !(this==other);
	}

};

template <typename TypeKey, typename TypeData>
class binTreeTable {
protected:
	Node* begin = NULL;
public:
	//--------------------------------------------------------------------------------//
	binTreeTable() { //конструктор по умолчанию
		begin = 0;
	}
	//--------------------------------------------------------------------------------//
	binTreeTable(const binTreeTable & other) { //конструктор копирования
		this = other;
	}
	//--------------------------------------------------------------------------------//
	~binTreeTable() { //деструктор
		
	}
	//--------------------------------------------------------------------------------//
	binTreeTable& operator=(const Table& other) { //оператор присваивания
		
	}
	//--------------------------------------------------------------------------------//
	TypeData& operator[] (const TypeKey& key) { //оператор []
		
	}
	//--------------------------------------------------------------------------------//
		//возвращаемое значение - ссылка на итератор на найденный элемент
	Iterator<TypeKey, TypeData> find(const TypeKey& k) {
		Node* n1 = root;
		while (n1 != NULL && n1.key != k) {
			if (n1.key > k)
				n1 = n1.right;
			else
				n1 = n1.left;
		}
		return n1;
	}
	int size() {
		
	}
	//--------------------------------------------------------------------------------//
	Iterator<TypeKey, TypeData> insert(const TypeKey& k, const TypeData& d) {
		//...
		Node* n1 = root;
		Node* n2;
		while (n1 != NULL && n1.key != k) {
			n2 = n1;
			if (n1.key > k)
				n1 = n1.right;
			else
				n1 = n1.left;
		}
		if (n1.key == k) {
			n1.data = d;
		}
		if (n1 == NULL) {
			n1 = new Node();
			n1.key = k;
			n1.data = d;
			n1.left = NULL;
			n1.right = NULL;
			n1.parent = n2;
			if (n2.key > n1.key)
				n2.right = n1;
			else
				n2.left = n1;
		}
		return n1;
	}
	//--------------------------------------------------------------------------------//
		//возвращаем true/false
	bool remove(const TypeKey& key) {
		Node* n1 = root;
		while (n1 != NULL && n1.key != k) {
			if (n1.key > k)
				n1 = n1.right;
			else
				n1 = n1.left;
		}
		if (n1 == NULL)
			return false;
		if (n1.key == k) {
			return true;//недописал
		}
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