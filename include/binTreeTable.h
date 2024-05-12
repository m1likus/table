#pragma once
#include <string>
#include "table.h"

template <typename TypeKey, typename T>
class binTreeIterator;

enum TwoColours {
	black,
	red
};


template <typename TypeKey, typename TypeData>
class Node {
public:
	TwoColours colour;
	pair<TypeKey, TypeData> storage;
	Node* left;
	Node* right;
	Node* parent;
	int height;

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
protected:
	inline bool HasLeftChild(Node <TypeKey, TypeData>* node) {
		if (node->left == 0) return false;
		return true;
	}
	inline bool HasRightChild(Node <TypeKey, TypeData>* node) {
		if (node->right == 0) return false;
		return true;
	}
	inline bool HasParent(Node <TypeKey, TypeData>* node) {
		if (node->parent == 0) return false;
		return true;
	}

	Node<TypeKey, TypeData>* root;
	friend binTreeIterator<TypeKey, TypeData>;
public:
//--------------------------------------------------------------------------------//
	BinTreeTable() { //конструктор по умолчанию
		root = 0;
	}
//--------------------------------------------------------------------------------//
	BinTreeTable(const BinTreeTable& other) { //конструктор копирования
		if (other.root == 0) { //если пустое - то будет пустое
			root = 0;
		}
		else {
			root = new Node<TypeKey, TypeData>(); //создаем узел корня
			root->parent = 0; //пустой корень
			root->left = 0;
			root->right = 0;
			root->storage = other.root->storage;  //скопировали хранилище
			Node<TypeKey, TypeData>* n1 = root; //где были
			Node<TypeKey, TypeData>* n2 = root; //куда идем
			Node<TypeKey, TypeData>* other_n1 = other.root; //где были в other
			Node<TypeKey, TypeData>* other_n2 = other.root; //куда идем в other
			while (n2 != 0) { //пока есть куда идти
				n1 = n2;
				other_n1 = other_n2;
				if (other_n1->left != 0 && n1->left == 0) { 
					//если левый потомок в other не пуст, а в this пуст, то
					other_n2 = other_n1->left; //приходим в левый потомок other
					n2 = new Node<TypeKey, TypeData>(); //раз пуст, то создадим новый узел
					n2->parent = n1; //заполним его
					n2->left = 0;
					n2->right = 0;
					n2->storage = other_n2->storage;
					n1->left = n2; //переходим в потомок this
				}
				else if (other_n1->right != 0 && n1->right == 0) {
					//если правый потомок other не пуст, а в this пуст, то
					other_n2 = other_n1->right; //переходим в правый потомок other
					n2 = new Node<TypeKey, TypeData>(); //создаем новый узел
					n2->parent = n1; //заполняем
					n2->left = 0;
					n2->right = 0;
					n2->storage = other_n2->storage;
					n1->right = n2; //переходим в потомок this
				}
				else {
					//если и правый и левый пуст - переходим в родителя
					n2 = n1->parent; 
					other_n2 = other_n1->parent;
				}
			}

		}
	}
//--------------------------------------------------------------------------------//
	~BinTreeTable() { //деструктор
		if (root == 0) {
			delete root;// = nullptr; //если пусто - удаляем
		}
		//иначе надо удалять снизу вверх, чтобы точно удалить все
		else {
			Node<TypeKey,TypeData>* n1 = root; //где были
			Node<TypeKey, TypeData>* n2 = root; //куда идем
			while (n2 != NULL) { //пока есть куда идти
				n1 = n2; //начинаем спускаться вниз до упора
				if (n1->left != 0) { //есть левый потомок
					n2 = n1->left;
					n1->left = 0;
				}
				else if (n2->right != 0) { //есть правый потомок
					n2 = n1->right;
					n1->right = 0;
				}
				else { //если узел без потомков
					n2 = n1->parent; //возвращаемся в родителя
					delete n1; //а узел удаляем
				}
			}
		}
		root = 0;
		//delete root;
	}
//--------------------------------------------------------------------------------//
	BinTreeTable& operator=(const BinTreeTable& other) { //оператор присваивания
		if (&other != this) {
			if (root == 0) { //если дерево чему присваиваем пустое
				if (other.root == 0) {
					root = 0;
				}
				else { //начинаем создавать новое дерево
					root = new Node<TypeKey, TypeData>(); //создаем корень
					root->parent = 0; //заполняем
					root->left = 0;
					root->right = 0;
					root->storage = other.root->storage;
					Node<TypeKey, TypeData>* n1 = root; //были
					Node<TypeKey, TypeData>* n2 = root; //стали
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
			else { //если не пустое
				if (other.root == 0) { //а то что присваиваем пустое - удаляем все
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
				else { //если были оба не пустыми
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
		if (n1->storage.first == key)
			return n1->storage.second;
	}
//--------------------------------------------------------------------------------//
	binTreeIterator<TypeKey, TypeData> find(const TypeKey& key){
		Node<TypeKey, TypeData>* n1 = root;
		while (n1 != 0 && n1->storage.first != key) {
			if (n1->storage.first < key)
				n1 = n1->right;
			else
				n1 = n1->left;
		}
		return binTreeIterator<TypeKey, TypeData>(*n1, *this);
	}
//--------------------------------------------------------------------------------//
	int size() {
		int count = 0;
		for (auto i = begin(); i != end(); ++i) {
			count++;
		}
		return count;
	}
//--------------------------------------------------------------------------------//
	binTreeIterator<TypeKey, TypeData> insert(const TypeKey& key, const TypeData& d) {
		if (root == 0) {
			root = new Node<TypeKey, TypeData>();
			root->parent = 0;
			root->left = 0;
			root->right = 0;
			root->storage = make_pair(key, d);
			return binTreeIterator<TypeKey, TypeData>(*root,*this);
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
			return binTreeIterator<TypeKey, TypeData>(*n1, *this);
		}
	}
//--------------------------------------------------------------------------------//
	bool remove(const TypeKey& key) {
		Node<TypeKey, TypeData>* DeleteNode = root;
		while (DeleteNode != 0 && DeleteNode->storage.first != key)
			DeleteNode->storage.first < key ? DeleteNode = DeleteNode->right : DeleteNode = DeleteNode->left;
		if (DeleteNode == 0) return false;
		else if (DeleteNode->storage.first == key) {
			Node<TypeKey, TypeData>* tmp = 0;
			if (HasRightChild(DeleteNode)) {
				tmp = DeleteNode->right;
				while (HasLeftChild(tmp))
					tmp = tmp->left; //нашли min
				//переприсваиваем
				if (DeleteNode->right == tmp) { //правым сыном DeleteNode м.б. сама tmp
					if (HasLeftChild(DeleteNode)) {
						DeleteNode->left->parent = tmp;
					}
				}
				else {
					tmp->parent->left = tmp->right;
					if (HasRightChild(tmp)) tmp->right->parent = tmp->parent;//
					if (HasLeftChild(DeleteNode)) {
						DeleteNode->left->parent = tmp;
					}
					tmp->right = DeleteNode->right;
					if (HasRightChild(DeleteNode)) {
						DeleteNode->right->parent = tmp;
					}
				}
				if (DeleteNode == root) root = tmp;
				if (HasParent(DeleteNode)) {
					if (DeleteNode->parent->left == DeleteNode) DeleteNode->parent->left = tmp;
					else if (DeleteNode->parent->right == DeleteNode) DeleteNode->parent->right = tmp;
				}
				tmp->parent = DeleteNode->parent;
				tmp->left = DeleteNode->left;
				DeleteNode = 0;
			}
			else if (HasLeftChild(DeleteNode)) {//т.е есть слева, нет справа
				tmp = DeleteNode->left;
				tmp->parent = DeleteNode->parent;
				if (HasParent(DeleteNode)) {
					if (DeleteNode->parent->left == DeleteNode) DeleteNode->parent->left = tmp;
					else if (DeleteNode->parent->right == DeleteNode) DeleteNode->parent->right = tmp;
				}
				if (DeleteNode == root) root = tmp;
				DeleteNode = 0;
			}
			else {
				if (HasParent(DeleteNode) && DeleteNode->parent->right == DeleteNode)
					DeleteNode->parent->right = 0;
				else if (HasParent(DeleteNode) && DeleteNode->parent->left == DeleteNode)
					DeleteNode->parent->left = 0;
				if (DeleteNode == root) root = 0;
				DeleteNode = 0;
			}
			return true;
		}
	}
//--------------------------------------------------------------------------------//
	//итератор на начало
	binTreeIterator<TypeKey, TypeData> begin() {
		if (root == 0) return binTreeIterator<TypeKey, TypeData>(*root, *this);
		else {
			Node<TypeKey, TypeData>* n1 = root;
			while (n1->left != 0) {
				n1 = n1->left;
			}
			return binTreeIterator<TypeKey, TypeData>(*(n1), *this);
		}
	}
//--------------------------------------------------------------------------------//
	//итератор на конец
	binTreeIterator<TypeKey, TypeData> end() {
		if (root == 0) return binTreeIterator<TypeKey, TypeData>(*root, *this);
		Node<TypeKey, TypeData>* n1 = root;
		while (n1->right != 0) {
			n1 = n1->right;
		}
		return ++binTreeIterator<TypeKey, TypeData>(*n1, *this);
	}
//--------------------------------------------------------------------------------//
	int getHeight() { //высота для всего дерева
		if (root == 0) return -1;
		int h = 0; 
		int max_h = 0;
		Node<TypeKey, TypeData>* n = root;
		while (HasLeftChild(n)) {
			n = n->left;
			h++;
		}
		if (h > max_h) max_h = h; 
		while (true) {
			Node<TypeKey, TypeData>* it_node = n;
			if (HasRightChild(it_node)) { 
				it_node = it_node->right;
				h++;
				while (HasLeftChild(it_node)) {
					it_node = it_node->left;
					h++;
				}
			}
			else {
				Node<TypeKey, TypeData>* save_node = it_node;
				while (HasParent(it_node) && it_node->parent->right == it_node) {
					h--;
					it_node = it_node->parent; //если мы сейчас в правом сыне, то идем наверх, пока не станем левым сыном или пока не дойдем до корня
				}
				if (!HasParent(it_node)) {//если мы в корне, то возвращаем +1 к последнему
					it_node = save_node;
					break;
				}
				else if (it_node->parent->left == it_node) { //если мы в левом сыне, то просто переходим к родителю
					h--;
					it_node = it_node->parent;
				}
			}
			n = it_node;
			if (h > max_h) max_h = h;
		}
		return max_h;
	}
};


template <typename TypeKey, typename T>
class binTreeIterator {
protected:
	pair <TypeKey, T>* iterator;
	Node<TypeKey, T>* it_node;
	BinTreeTable<TypeKey, T>* it_tree;
public:
	binTreeIterator(pair<TypeKey, T>& data, Node<TypeKey, T>& new_node, BinTreeTable<TypeKey, T>& tree) {
		iterator = &data;
		it_node = &new_node;
		it_tree = &tree;
	}
	binTreeIterator(Node<TypeKey, T>& other, BinTreeTable<TypeKey, T>& other_tree) {
		iterator = &(other.storage);
		it_node = &other;
		it_tree = &other_tree;
	}
	T& operator*() const {
		return iterator->second;
	}
	T* operator->() const {
		return iterator.second;
	}

	binTreeIterator& operator++() {
		if (it_node->right != 0) { //если есть справа, то идем вправо...
			it_node = it_node->right;
			while(it_node->left!=0) //если есть слева, то идем влево до конца
				it_node = it_node->left;
			iterator = &(it_node->storage);
		}
		else {
			Node<TypeKey, T>* save_node(it_node);
			while (it_node->parent != 0 && it_node->parent->right == it_node)
				it_node = it_node->parent; //если мы сейчас в правом сыне, то идем наверх, пока не станем левым сыном или пока не дойдем до корня
			if (it_node->parent == 0) {//если мы в корне, то возвращаем +1 к последнему
				it_node = save_node;
				iterator = &(it_node->storage) + 1;
			}
			else if (it_node->parent->left == it_node) { //если мы в левом сыне, то просто переходим к родителю
				it_node = it_node->parent;
				iterator = &(it_node->storage);
			}
		}
		return *this;
	}
	binTreeIterator& operator--() {
		if (this->it_node == nullptr) {
			if (it_tree->root == 0) return binTreeIterator<TypeKey, T>(*it_tree->root, *it_tree);
			Node<TypeKey, T>* n1 = it_tree->root;
			while (n1->right != 0) {
				n1 = n1->right;
			}
			iterator = &(n1->storage);
		}
		else if (it_node->left !=0 ) {//если есть слева, то идем влево...
			it_node = it_node->left;
			while (it_node->right != 0)//если есть справа, то идем вправо до конца
				it_node = it_node->right;
			iterator = &(it_node->storage);
		}
		else {
			Node<TypeKey, T>* save_node(it_node);
			while (it_node->parent != 0 && it_node->parent->left == it_node)
				it_node = it_node->parent;//если мы сейчас в левом сыне, то идем наверх, пока не станем правым сыном или пока не дойдем до корня
			if (it_node->parent == 0) {//если мы в корне, то просто останемся, тк я не знаю что делать с бегином, по идее эта ситуация не может быть и это "зацита" от ошибок
				it_node = save_node;
				iterator = &(it_node->storage);
			}
			else if (it_node->parent->right == it_node) {//если мы в правом сыне, то просто переходим к родителю
				it_node = it_node->parent;
				iterator = &(it_node->storage);
			}
		}
		return *this;
	}
	binTreeIterator operator+() {
		binTreeIterator<TypeKey, T> tmp = *this;
		for (int i = 0; i < offset; i++) {
			++tmp;
		}
		return tmp;
	}
	bool operator==(const binTreeIterator& other) {
		return iterator == other.iterator;
	}
	bool operator!=(const binTreeIterator& other) {
		return iterator != other.iterator;
	}
};