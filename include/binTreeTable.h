#pragma once

#include <string>
#include "table.h"

template <typename TypeKey, typename TypeData>
class Node {
public:
	pair<TypeData,TypeKey> storage;
	Node* left;
	Node* right;
	Node* parent;

	bool operator==(const Node& other) {
		if (key == other.key && data == other.data)
			return true;
		return false;
	}

	bool operator!=(const Node& other) {
		return !(this == other);
	}

};

template <typename TypeKey, typename TypeData>
class BinTreeTable {
private:

protected:
	Node<TypeKey, TypeData>* root;
public:
	//--------------------------------------------------------------------------------//
	BinTreeTable() { //конструктор по умолчанию
		root = 0;
	}
	//--------------------------------------------------------------------------------//
	BinTreeTable(const BinTreeTable& other) { //конструктор копирования
		if (other.root == 0) {
			root = 0;
		}
		else {
			root = new Node<TypeKey, TypeData>();
			root->parent = 0;
			root->left = 0;
			root->right = 0;
			root->storage = other.root->storage;
			Node<TypeKey, TypeData>* n1 = root;
			Node<TypeKey, TypeData>* n2 = root;
			Node<TypeKey, TypeData>* other_n1 = other.root;
			Node<TypeKey, TypeData>* other_n2 = other.root;
			while (n2 != 0) {
				n1 = n2;
				other_n1 = other_n2;
				if (other_n1->left != 0 && n1->left == 0) {
					other_n2 = other_n1->left;
					n2 = new Node<TypeKey, TypeData>();
					n2->parent = n1;
					n2->left = 0;
					n2->right = 0;
					n2->storage = other_n2->storage;
					n1->left = n2;
				}
				else if (other_n1->right != 0 && n1->right == 0) {
					other_n2 = other_n1->right;
					n2 = new Node<TypeKey, TypeData>();
					n2->parent = n1;
					n2->left = 0;
					n2->right = 0;
					n2->storage = other_n2->storage;
					n1->right = n2;
				}
				else {
					n2 = n1->parent;
					other_n2 = other_n1->parent;
				}
			}

		}
	}
	//--------------------------------------------------------------------------------//
	~BinTreeTable() { //деструктор
		if (root == 0) {
			delete root;// = nullptr;
		}
		else {
			Node<TypeKey,TypeData>* n1 = root;
			Node<TypeKey, TypeData>* n2 = root;
			while (n2 != NULL) {
				n1 = n2;
				if (n1->left != 0) {
					n2 = n1->left;
					n1->left = 0;
				}
				else if (n2->right != 0) {
					n2 = n1->right;
					n1->right = 0;
				}
				else {
					n2 = n1->parent;
					delete n1;
				}
			}
		}
		root = 0;
		//delete root;
	}
	//--------------------------------------------------------------------------------//
	BinTreeTable& operator=(const BinTreeTable& other) { //оператор присваивания
		if (&other != this) {
			if (root == 0) {
				if (other.root == 0) {
					root = 0;
				}
				else {
					root = new Node<TypeKey, TypeData>();
					root->parent = 0;
					root->left = 0;
					root->right = 0;
					root->storage = other.root->storage;
					Node<TypeKey, TypeData>* n1 = root;
					Node<TypeKey, TypeData>* n2 = root;
					Node<TypeKey, TypeData>* other_n1 = other.root;
					Node<TypeKey, TypeData>* other_n2 = other.root;
					while (n2 != 0) {
						n1 = n2;
						other_n1 = other_n2;
						if (other_n1->left != 0 && n1->left == 0) {
							other_n2 = other_n1->left;
							n2 = new Node<TypeKey, TypeData>();
							n2->parent = n1;
							n2->left = 0;
							n2->right = 0;
							n2->storage = other_n2->storage;
							n1->left = n2;
						}
						else if (other_n1->right != 0 && n1->right == 0) {
							other_n2 = other_n1->right;
							n2 = new Node<TypeKey, TypeData>();
							n2->parent = n1;
							n2->left = 0;
							n2->right = 0;
							n2->storage = other_n2->storage;
							n1->right = n2;
						}
						else {
							n2 = n1->parent;
							other_n2 = other_n1->parent;							
						}
					}

				}
			}
			else {
				if (other.root == 0) {
					Node<TypeKey, TypeData>* n1 = root;
					Node<TypeKey, TypeData>* n2 = root;
					while (n2 != NULL) {
						n1 = n2;
						if (n1->left != 0) {
							n2 = n1->left;
							n1->left = 0;
						}
						else if (n2->right != 0) {
							n2 = n1->right;
							n1->right = 0;
						}
						else {
							n2 = n1->parent;
							delete n1;
						}
					}
					delete n1;
					delete n2;
					root = 0;
				}
				else {
					root->storage = other.root->storage;
					Node<TypeKey, TypeData>* n1 = root;
					Node<TypeKey, TypeData>* n2 = root;
					Node<TypeKey, TypeData>* other_n1 = other.root;
					Node<TypeKey, TypeData>* other_n2 = other.root;
					while (n2 != 0) {
						n1 = n2;
						other_n1 = other_n2;
						if (other_n1->left != 0 && n1->left == 0) {
							other_n2 = other_n1->left;
							n2 = new Node<TypeKey, TypeData>();
							n2->parent = n1;
							n2->left = 0;
							n2->right = 0;
							n2->storage = other_n2->storage;
							n1->left = n2;
						}
						else if (other_n1->right != 0 && n1->right == 0) {
							other_n2 = other_n1->right;
							n2 = new Node<TypeKey, TypeData>();
							n2->parent = n1;
							n2->left = 0;
							n2->right = 0;
							n2->storage = other_n2->storage;
							n1->right = n2;
						}
						else if (other_n1->left == 0 && n1->left != 0) {
							Node<TypeKey, TypeData>* n_n1 = n1->left;
							Node<TypeKey, TypeData>* n_n2 = n1->left;
							while (n_n2 != NULL) {
								n_n1 = n_n2;
								if (n_n1->left != 0) {
									n_n2 = n_n1->left;
									n_n1->left = 0;
								}
								else if (n_n2->right != 0) {
									n_n2 = n_n1->right;
									n_n1->right = 0;
								}
								else {
									n_n2 = n_n1->parent;
									delete n_n1;
								}
							}
							delete n_n1;
							delete n_n2;
							n1->left = 0;
						}
						else if (other_n1->right == 0 && n1->right != 0) {
							Node<TypeKey, TypeData>* n_n1 = n1->right;
							Node<TypeKey, TypeData>* n_n2 = n1->right;
							while (n_n2 != NULL) {
								n_n1 = n_n2;
								if (n_n1->left != 0) {
									n_n2 = n_n1->left;
									n_n1->left = 0;
								}
								else if (n_n2->right != 0) {
									n_n2 = n_n1->right;
									n_n1->right = 0;
								}
								else {
									n_n2 = n_n1->parent;
									delete n_n1;
								}
							}
							delete n_n1;
							delete n_n2;
							n1->right = 0;
						}
						else {
							n2 = n1->parent;
							other_n2 = other_n1->parent;
						}
					}
				}
			}
		}
		return *this;
	}
	//--------------------------------------------------------------------------------//
	TypeData& operator[] (const TypeKey& key) { //оператор []
		Node<TypeKey, TypeData>* n1 = root;
		while (n1 != 0 && n1->storage.first != key) {
			if (n1->storage.first < key)
				n1 = n1->right;
			else
				n1 = n1->left;
		}
		if (n1 == 0)
			throw "not_found";
		if (n1->storage.first != key)
			return n1->storage.second;
	}
	//--------------------------------------------------------------------------------//
		//возвращаемое значение - ссылка на итератор на найденный элемент
	Iterator<TypeKey, TypeData> find(const TypeKey& key){
		Node<TypeKey, TypeData>* n1 = root;
		while (n1 != 0 && n1->storage.first != key) {
			if (n1->storage.first < key)
				n1 = n1->right;
			else
				n1 = n1->left;
		}
		return Iterator<TypeKey, TypeData>(n1->storage);
	}
	int size() {

	}
	//--------------------------------------------------------------------------------//
	Iterator<TypeKey, TypeData> insert(const TypeKey& key, const TypeData& d) {
		//...
		if (root == 0) {
			root = new Node<TypeKey, TypeData>();
			root->parent = 0;
			root->left = 0;
			root->right = 0;
			root->storage = make_pair(key, d);
			return Iterator<TypeKey, TypeData>(root->storage);
		}
		else {
			Node<TypeKey, TypeData>* n1 = root;
			Node<TypeKey, TypeData>* n2 = 0;
			while (n1 != 0 && n1->storage.first != key) {
				n2 = n1;
				if (n1->storage.first < key)
					n1 = n1->right;
				else
					n1 = n1->left;
			}
			if (n1 == 0) {
				n1 = new Node<TypeKey, TypeData>();
				n1->storage = make_pair(key, d);
				n1->left = 0;
				n1->right = 0;
				n1->parent = n2;
				if (n2->storage.first < n1->storage.first)
					n2->right = n1;
				else
					n2->left = n1;
			}
			else if (n1->storage.first == key) {
				n1->storage.second = d;
			}
			return Iterator<TypeKey, TypeData>(n1->storage);
		}
	}
	//--------------------------------------------------------------------------------//
		//возвращаем true/false
	bool remove(const TypeKey& key) {
		Node<TypeKey, TypeData>* n1 = root;
		while (n1 != 0 && n1->storage.first != key) {
			if (n1->storage.first < key)
				n1 = n1->right;
			else
				n1 = n1->left;
		}
		if (n1 == 0)
			return false;
		if (n1->storage.first == key) {
			Node<TypeKey, TypeData>* nr;
			if (n1->right != 0) {
				nr = n1->right;
				Node<TypeKey, TypeData>* n2 = nr;
				while (n2->left != 0)
					n2 = n2->left;
				n2->left = n1->left;
				n1->left->parent = n2;
			}
			else
				nr = n1->left;
			if (n1->parent == 0) {
				nr->parent = 0;
				root = nr;
			}
			else {
				nr->parent = n1->parent;
				if (n1->parent->left->storage.first == key)
					n1->parent->left = nr;
				else
					n1->parent->right = nr;
			}
			return true;
		}
	}
	//--------------------------------------------------------------------------------//
		//итератор на начало
	//Iterator<TypeKey, TypeData> begin() {
	//	return Iterator<TypeKey, TypeData>(storage[0]);
		//итераторы вообще не трогал, мне ещё подумать надо как реализовать, 
		//скорее всего черновой вариант будет как у хэша, тоесть совй собственный итератор, 
		//а потом если нам будет не лень, то сделаем задумку, о которой на паре говорили
	//}
	//--------------------------------------------------------------------------------//
		//итератор на конец
	//Iterator<TypeKey, TypeData> end() {
	//	Iterator<TypeKey, TypeData> a = begin();
	//	return a + storage.size();
	//}
	//--------------------------------------------------------------------------------//
};