#pragma once
#include "binTreeTable.h"

//Правила для Красно-черных деревьев:
// 1) Корень - черный
// 2) Все листы - null, всегда черные
// 3) Каждая верш. черная/красная, всегда 2 потомка (с учетом null-листов)
// 4) У красной вершины потомки - черные 
//				<=>
//	В дереве не может быть две красные вершины подряд
// 5) Является сбалансированным относительно черной вершины.
//	  height по черным вершинам всегда одинаков
// 6) При вставке любой вершины - она всегда красная.
//
//
// Соблюдение этих правил гарантирует нам черно-красное дерево.

template <typename TypeKey, typename TypeData>
class RbTreeTable : public BinTreeTable<TypeKey, TypeData> {
private:
	inline bool HasGrandparent(Node <TypeKey, TypeData>* node) {
		if (node->parent == 0) return false;
		else if (node->parent->parent == 0) return false;
		return true;
	}

	inline bool HasUncle(Node <TypeKey, TypeData>* node) {
		if (!HasParent(node)) return false;
		if (node->parent->right == node) {
			if (!HasLeftChild(node->parent))
				return false;
		}
		else 
			if (!HasRightChild(node->parent))
				return false;
		return true;
	}
	void rebalance(Node <TypeKey, TypeData>* Node) {}

public:
	RbTreeTable() { //конструктор по умолчанию
		root = 0;
	}
	//--------------------------------------------------------------------------------//
	RbTreeTable(const RbTreeTable& other) { //конструктор копирования
		if (other.root == 0) { //если пустое - то будет пустое
			root = 0;
		}
		else {
			root = new Node<TypeKey, TypeData>(); //создаем узел корня
			root->parent = 0; //пустой корень
			root->left = 0;
			root->right = 0;
			root->colour = black;
			root->storage = other.root->storage;  //скопировали хранилище
			root->height = other.root->height;
			Node<TypeKey, TypeData>* n1 = root; //где были
			Node<TypeKey, TypeData>* n2 = root; //куда идем
			Node<TypeKey, TypeData>* other_n1 = other.root; //где были в other
			Node<TypeKey, TypeData>* other_n2 = other.root; //куда идем в other
			while (n2 != 0) { //пока есть куда идти
				n1 = n2;
				other_n1 = other_n2;
				if (HasLeftChild(other_n1) && !HasLeftChild(n1)) {
					//если левый потомок в other не пуст, а в this пуст, то
					other_n2 = other_n1->left; //приходим в левый потомок other
					n2 = new Node<TypeKey, TypeData>(); //раз пуст, то создадим новый узел
					n2->parent = n1; //заполним его
					n2->left = 0;
					n2->right = 0;
					n2->storage = other_n2->storage;
					n2->height = other_n2->height;
					n2->colour = other_n2->colour;
					n1->left = n2; //переходим в потомок this
				}
				else if (HasRightChild(other_n1) && !HasRightChild(n1)) {
					//если правый потомок other не пуст, а в this пуст, то
					other_n2 = other_n1->right; //переходим в правый потомок other
					n2 = new Node<TypeKey, TypeData>(); //создаем новый узел
					n2->parent = n1; //заполняем
					n2->left = 0;
					n2->right = 0;
					n2->storage = other_n2->storage;
					n2->height = other_n2->height;
					n2->colour = other_n2->colour;
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
					root->colour = black;
					root->storage = other.root->storage;
					root->height = other.root->height;
					Node<TypeKey, TypeData>* n1 = root; //были
					Node<TypeKey, TypeData>* n2 = root; //стали
					Node<TypeKey, TypeData>* other_n1 = other.root;
					Node<TypeKey, TypeData>* other_n2 = other.root;
					while (n2 != 0) {
						n1 = n2;
						other_n1 = other_n2;
						if (HasLeftChild(other_n1) && !HasLeftChild(n1)) {
							other_n2 = other_n1->left;
							n2 = new Node<TypeKey, TypeData>();
							n2->parent = n1;
							n2->left = 0;
							n2->right = 0;
							n2->storage = other_n2->storage;
							n2->height = other_n2->height;
							n2->colour = other_n2->colour;
							n1->left = n2;
						}
						else if (HasRightChild(other_n1) && !HasRightChild(n1)) {
							other_n2 = other_n1->right;
							n2 = new Node<TypeKey, TypeData>();
							n2->parent = n1;
							n2->left = 0;
							n2->right = 0;
							n2->storage = other_n2->storage;
							n2->height = other_n2->height;
							n2->colour = other_n2->colour;
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
				if (other.root == 0) { //е. то что присваиваем пустое - удаляем все
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
						if (HasLeftChild(other_n1) && !HasLeftChild(n1)) {
							other_n2 = other_n1->left;
							n2 = new Node<TypeKey, TypeData>();
							n2->parent = n1;
							n2->left = 0;
							n2->right = 0;
							n2->storage = other_n2->storage;
							n2->height = other_n2->height;
							n2->colour = other_n2->colour;
							n1->left = n2;
						}
						else if (HasRightChild(other_n1) && !HasRightChild(n1)) {
							other_n2 = other_n1->right;
							n2 = new Node<TypeKey, TypeData>();
							n2->parent = n1;
							n2->left = 0;
							n2->right = 0;
							n2->storage = other_n2->storage;
							n2->height = other_n2->height;
							n2->colour = other_n2->colour;
							n1->right = n2;
						}
						else if (!HasLeftChild(other_n1) && HasLeftChild(n1)) {
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
						else if (!HasRightChild(other_n1) && HasRightChild(n1)) {
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
	binTreeIterator<TypeKey, TypeData> insert(const TypeKey& key, const TypeData& d) {
		if (root == 0) {
			root = new Node<TypeKey, TypeData>();
			root->parent = 0;
			root->left = 0;
			root->right = 0;
			root->storage = make_pair(key, d);
			root->height = 0;
			root->colour = black;
			return binTreeIterator<TypeKey, TypeData>(*root, *this);
		}
		else {
			Node<TypeKey, TypeData>* n1 = root;
			Node<TypeKey, TypeData>* n2 = 0;
			while (n1 != 0 && n1->storage.first != key) {
				n2 = n1;
				n1->storage.first < key ? n1 = n1->right : n1 = n1->left;
			}
			if (n1 == 0) {
				n1 = new Node<TypeKey, TypeData>();
				n1->storage = make_pair(key, d);
				n1->left = 0;
				n1->right = 0;
				n1->parent = 0;
				n1->height = 0;
				n1->colour = red; //всегда вставляем красную вершину
				if (n2->storage.first < n1->storage.first)
					n2->right = n1;
				else
					n2->left = n1;
				rebalance(n1);
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
				tmp->height = DeleteNode->height;
				tmp->colour = DeleteNode->colour;
				rebalance(tmp);
				DeleteNode = 0;
			}
			else if (HasLeftChild(DeleteNode)) {//т.е есть слева, нет справа
				if (DeleteNode == root) root = tmp;
				tmp = DeleteNode->left;
				tmp->parent = DeleteNode->parent;
				if (HasParent(DeleteNode)) {
					if (DeleteNode->parent->left == DeleteNode) DeleteNode->parent->left = tmp;
					else if (DeleteNode->parent->right == DeleteNode) DeleteNode->parent->right = tmp;
				}
				tmp->height = DeleteNode->height;
				tmp->height = DeleteNode->colour;
				rebalance(tmp);
				DeleteNode = 0;
			}
			else {
				if (DeleteNode == root) root = tmp;
				if (HasParent(DeleteNode)) {
					tmp = DeleteNode->parent;
					if (DeleteNode->parent->right == DeleteNode) DeleteNode->parent->right = 0;
					else if (DeleteNode->parent->left == DeleteNode) DeleteNode->parent->left = 0;
				}
				tmp->colour = DeleteNode->colour;
				DeleteNode = 0;
				if (tmp != 0)rebalance(tmp);
			}
			return true;
		}
	}
	//--------------------------------------------------------------------------------//
	int getHeight() { //высота для всего дерева
		return root->height;
	}
};

