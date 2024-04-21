#pragma once
#include <string>
#include "table.h"

template <typename TypeKey, typename T>
class binTreeIterator;

template <typename TypeKey, typename TypeData>
class Node {
public:
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
	Node<TypeKey, TypeData>* root;
	friend binTreeIterator<TypeKey, TypeData>;
public:
//--------------------------------------------------------------------------------//
	BinTreeTable() { //����������� �� ���������
		root = 0;
	}
//--------------------------------------------------------------------------------//
	BinTreeTable(const BinTreeTable& other) { //����������� �����������
		if (other.root == 0) { //���� ������ - �� ����� ������
			root = 0;
		}
		else {
			root = new Node<TypeKey, TypeData>(); //������� ���� �����
			root->parent = 0; //������ ������
			root->left = 0;
			root->right = 0;
			root->storage = other.root->storage;  //����������� ���������
			Node<TypeKey, TypeData>* n1 = root; //��� ����
			Node<TypeKey, TypeData>* n2 = root; //���� ����
			Node<TypeKey, TypeData>* other_n1 = other.root; //��� ���� � other
			Node<TypeKey, TypeData>* other_n2 = other.root; //���� ���� � other
			while (n2 != 0) { //���� ���� ���� ����
				n1 = n2;
				other_n1 = other_n2;
				if (other_n1->left != 0 && n1->left == 0) { 
					//���� ����� ������� � other �� ����, � � this ����, ��
					other_n2 = other_n1->left; //�������� � ����� ������� other
					n2 = new Node<TypeKey, TypeData>(); //��� ����, �� �������� ����� ����
					n2->parent = n1; //�������� ���
					n2->left = 0;
					n2->right = 0;
					n2->storage = other_n2->storage;
					n1->left = n2; //��������� � ������� this
				}
				else if (other_n1->right != 0 && n1->right == 0) {
					//���� ������ ������� other �� ����, � � this ����, ��
					other_n2 = other_n1->right; //��������� � ������ ������� other
					n2 = new Node<TypeKey, TypeData>(); //������� ����� ����
					n2->parent = n1; //���������
					n2->left = 0;
					n2->right = 0;
					n2->storage = other_n2->storage;
					n1->right = n2; //��������� � ������� this
				}
				else {
					//���� � ������ � ����� ���� - ��������� � ��������
					n2 = n1->parent; 
					other_n2 = other_n1->parent;
				}
			}

		}
	}
//--------------------------------------------------------------------------------//
	~BinTreeTable() { //����������
		if (root == 0) {
			delete root;// = nullptr; //���� ����� - �������
		}
		//����� ���� ������� ����� �����, ����� ����� ������� ���
		else {
			Node<TypeKey,TypeData>* n1 = root; //��� ����
			Node<TypeKey, TypeData>* n2 = root; //���� ����
			while (n2 != NULL) { //���� ���� ���� ����
				n1 = n2; //�������� ���������� ���� �� �����
				if (n1->left != 0) { //���� ����� �������
					n2 = n1->left;
					n1->left = 0;
				}
				else if (n2->right != 0) { //���� ������ �������
					n2 = n1->right;
					n1->right = 0;
				}
				else { //���� ���� ��� ��������
					n2 = n1->parent; //������������ � ��������
					delete n1; //� ���� �������
				}
			}
		}
		root = 0;
		//delete root;
	}
//--------------------------------------------------------------------------------//
	BinTreeTable& operator=(const BinTreeTable& other) { //�������� ������������
		if (&other != this) {
			if (root == 0) { //���� ������ ���� ����������� ������
				if (other.root == 0) {
					root = 0;
				}
				else { //�������� ��������� ����� ������
					root = new Node<TypeKey, TypeData>(); //������� ������
					root->parent = 0; //���������
					root->left = 0;
					root->right = 0;
					root->storage = other.root->storage;
					Node<TypeKey, TypeData>* n1 = root; //����
					Node<TypeKey, TypeData>* n2 = root; //�����
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
			else { //���� �� ������
				if (other.root == 0) { //� �� ��� ����������� ������ - ������� ���
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
				else { //���� ���� ��� �� �������
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
	TypeData& operator[] (const TypeKey& key) { //�������� []
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
		Node<TypeKey, TypeData>* n1 = root; //�������� � �����
		while (n1 != 0 && n1->storage.first != key) { //���� ���� ���� !=0 � �� ����� �����
			if (n1->storage.first < key) //���� ������� ���� ������ ����� � ���� n1
				n1 = n1->right; //���� �������
			else
				n1 = n1->left; //����� ������
		}
		if (n1 == 0) //���� �����, �� �� ����� �������
			return false;
		if (n1->storage.first == key) { //���� �����
			Node<TypeKey, TypeData>* nr = 0; //������ ��� ����� ������� �������
			if (n1->right != 0) { //���� � n1 ������ ������� !=0
				nr = n1->right; //��������� � ����� ������� �������
				Node<TypeKey, TypeData>* n2 = nr; //� ������� ��� ����
				while (n2->left != 0)
					n2 = n2->left; //��������� � ����
				n2->left = n1->left;
				if(n1->left!=0)
					n1->left->parent = n2;
			}
			else if(n1->left != 0)
				nr = n1->left;
			
			if (nr == 0 && n1->parent != 0) {
				if (n1->parent->left != 0 && n1->parent->left->storage.first == key)
					n1->parent->left = nr;
				else
					n1->parent->right = nr;
				return true;
			}
			else if (nr == 0 && n1->parent == 0) {
				root = 0;
			}
			else if (n1->parent == 0) {
				nr->parent = 0;
				root = nr;
			}
			else {
				nr->parent = n1->parent;
				if (n1->parent->left!=0 && n1->parent->left->storage.first == key)
					n1->parent->left = nr;
				else
					n1->parent->right = nr;
			}
			return true;
		}
	}
//--------------------------------------------------------------------------------//
	//�������� �� ������
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
	//�������� �� �����
	binTreeIterator<TypeKey, TypeData> end() {
		if (root == 0) return binTreeIterator<TypeKey, TypeData>(*root, *this);
		Node<TypeKey, TypeData>* n1 = root;
		while (n1->right != 0) {
			n1 = n1->right;
		}
		return ++binTreeIterator<TypeKey, TypeData>(*n1, *this);
	}
//--------------------------------------------------------------------------------//
	int getHeight() { //������ ��� ����� ������
		int h = 0; 
		int max_h = 0;
		Node<TypeKey, TypeData>* n = root;
		while (n->left != 0) {
			n = n->left;
			h++;
		}
		if (h > max_h) max_h = h; 
		while (true) {
			Node<TypeKey, TypeData>* it_node = n;
			if (it_node->right != 0) { 
				it_node = it_node->right;
				h++;
				while (it_node->left != 0) {
					it_node = it_node->left;
					h++;
				}
			}
			else {
				Node<TypeKey, TypeData>* save_node(it_node);
				while (it_node->parent != 0 && it_node->parent->right == it_node) {
					it_node = it_node->parent; //���� �� ������ � ������ ����, �� ���� ������, ���� �� ������ ����� ����� ��� ���� �� ������ �� �����
					h--;
				}
				if (it_node->parent == 0) {//���� �� � �����, �� ���������� +1 � ����������
					it_node = save_node;
					break;
				}
				else if (it_node->parent->left == it_node) { //���� �� � ����� ����, �� ������ ��������� � ��������
					it_node = it_node->parent;
					h--;
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
		if (it_node->right != 0) { //���� ���� ������, �� ���� ������...
			it_node = it_node->right;
			while(it_node->left!=0) //���� ���� �����, �� ���� ����� �� �����
				it_node = it_node->left;
			iterator = &(it_node->storage);
		}
		else {
			Node<TypeKey, T>* save_node(it_node);
			while (it_node->parent != 0 && it_node->parent->right == it_node)
				it_node = it_node->parent; //���� �� ������ � ������ ����, �� ���� ������, ���� �� ������ ����� ����� ��� ���� �� ������ �� �����
			if (it_node->parent == 0) {//���� �� � �����, �� ���������� +1 � ����������
				it_node = save_node;
				iterator = &(it_node->storage) + 1;
			}
			else if (it_node->parent->left == it_node) { //���� �� � ����� ����, �� ������ ��������� � ��������
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
		else if (it_node->left != 0) {//���� ���� �����, �� ���� �����...
			it_node = it_node->left;
			while (it_node->right != 0)//���� ���� ������, �� ���� ������ �� �����
				it_node = it_node->right;
			iterator = &(it_node->storage);
		}
		else {
			Node<TypeKey, T>* save_node(it_node);
			while (it_node->parent != 0 && it_node->parent->left == it_node)
				it_node = it_node->parent;//���� �� ������ � ����� ����, �� ���� ������, ���� �� ������ ������ ����� ��� ���� �� ������ �� �����
			if (it_node->parent == 0) {//���� �� � �����, �� ������ ���������, �� � �� ���� ��� ������ � �������, �� ���� ��� �������� �� ����� ���� � ��� "������" �� ������
				it_node = save_node;
				iterator = &(it_node->storage);
			}
			else if (it_node->parent->right == it_node) {//���� �� � ������ ����, �� ������ ��������� � ��������
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