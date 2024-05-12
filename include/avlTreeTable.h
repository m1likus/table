#pragma once
#include "binTreeTable.h"

template <typename TypeKey, typename TypeData>
class AvlTreeTable : public BinTreeTable<TypeKey, TypeData> {
private:
	void recorrect(Node<TypeKey, TypeData>* node) {
		int rh = -1, lh = -1;
		HasRightChild(node) ? rh = node->right->height : rh = -1;
		HasLeftChild(node)  ? lh = node->left->height : lh = -1;
		node->height = my_max(lh, rh) + 1;
	}
	int difference(Node<TypeKey, TypeData>* node) {
		int rh = -1, lh = -1;
		HasRightChild(node) ? rh = node->right->height : rh = -1;
		node->left != 0 ? lh = node->left->height : lh = -1;
		return lh - rh;
	}

	
	void smallRight(Node<TypeKey, TypeData>* a) {
		Node<TypeKey, TypeData>* b = a->left;
		if (HasParent(a))
			if (a->parent->right == a) a->parent->right = b;
			else a->parent->left = b;
		else root = b;
		b->parent = a->parent;
		if (HasRightChild(b)) b->right->parent = a;
		a->left = b->right;
		b->right = a;
		a->parent = b;

		recorrect(a);
		recorrect(b);
	}
	void smallLeft(Node<TypeKey, TypeData>* a) {
		Node <TypeKey, TypeData>* b = a->right;
		if (HasParent(a))
			if (a->parent->right == a) a->parent->right = b;
			else a->parent->left = b;
		else root = b;
		b->parent = a->parent;
		if (HasLeftChild(b)) b->left->parent = a;
		a->right = b->left;
		b->left = a;
		a->parent = b;

		recorrect(a);
		recorrect(b);
	}
	void bigRight(Node<TypeKey, TypeData>* a) {
		if (HasRightChild(a->left))
			smallLeft(a->left);
		else return;
		smallRight(a);
	}
	void bigLeft(Node<TypeKey, TypeData>* a) {
		if (HasLeftChild(a->right))
			smallRight(a->right);
		else return;
		smallLeft(a);
	}
	void rebalance(Node<TypeKey, TypeData>* n) {
		Node<TypeKey, TypeData>* c = n;
		Node<TypeKey, TypeData>* b = 0;
		Node<TypeKey, TypeData>* a = 0;
		int diff_c = 0;
		int diff_b = 0;
		int diff_a = 0;

		recorrect(c);
		while (HasParent(c)) {
			b = c->parent;
			recorrect(b);
			//для малого поворота нужно 2 верш. : c и b.
			diff_c = difference(c);
			diff_b = difference(b);
			if (diff_c <= 0 && diff_b == -2) {
				smallLeft(b);
			}
			else if (diff_c >= 0 && diff_b == 2) {
				smallRight(b);
			}
			c = b;
		}
		//если не сработали малые повороты, то надо пройтись большими поворотами
		c = n; diff_c = 0; diff_b = 0; diff_a = 0; b = 0; a = 0;
		if (HasParent(c)) b = c->parent;
		while (HasParent(c) && HasParent(b)) {
			b = c->parent;
			if (!HasParent(b)) break;
			a = b->parent;
			recorrect(b);
			recorrect(a);
			diff_c = difference(c);
			diff_b = difference(b);
			diff_a = difference(a);
			if (/*diff_c <= 1 &&*/ diff_b == 1 && diff_a == -2) {
				bigLeft(a);
			}
			else if (/*diff_c <= 1 && */ diff_b == -1 && diff_a == 2) {
				bigRight(a);
			}
			c = b;
			b = a;
		}
		c = n;
		b = 0;
	}

	int my_max(int a, int b) {
		return a >= b ? a : b;
	}

public:
	AvlTreeTable() { //конструктор по умолчанию
		root = 0;
	}
//--------------------------------------------------------------------------------//
	AvlTreeTable(const AvlTreeTable& other) { //конструктор копирования
		if (other.root == 0) { //если пустое - то будет пустое
			root = 0;
		}
		else {
			root = new Node<TypeKey, TypeData>(); //создаем узел корня
			root->parent = 0; //пустой корень
			root->left = 0;
			root->right = 0;
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
						if (HasLeftChild(other_n1) && !HasLeftChild(n1)) {
							other_n2 = other_n1->left;
							n2 = new Node<TypeKey, TypeData>();
							n2->parent = n1;
							n2->left = 0;
							n2->right = 0;
							n2->storage = other_n2->storage;
							n2->height = other_n2->height;
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
				n1->parent = n2;
				n1->height = 0;
				if (n2->storage.first < n1->storage.first)
					n2->right = n1;
				else
					n2->left = n1;
				rebalance(n1);
			}
			else if (n1->storage.first == key) {
				n1->storage.second = d;
			}
			return binTreeIterator<TypeKey, TypeData>(*n1,*this);
		}
	}
//--------------------------------------------------------------------------------//
	bool remove(const TypeKey & key) {
		Node<TypeKey, TypeData>* DeleteNode = root;
		while (DeleteNode !=0 && DeleteNode->storage.first != key)
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
					if (HasRightChild(tmp)) tmp->right->parent = tmp->parent;
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
				rebalance(tmp);
				DeleteNode = 0;
			}
			else if (HasLeftChild(DeleteNode)) {//т.е есть слева, нет справа
				
				tmp = DeleteNode->left;
				tmp->parent = DeleteNode->parent;
				if (HasParent(DeleteNode)) {
					if (DeleteNode->parent->left == DeleteNode) DeleteNode->parent->left = tmp;
					else if (DeleteNode->parent->right == DeleteNode) DeleteNode->parent->right = tmp;
				}
				tmp->height = DeleteNode->height;
				if (DeleteNode == root) root = tmp;
				rebalance(tmp);
				DeleteNode = 0;
			}
			else {
				if (HasParent(DeleteNode) && DeleteNode->parent->right == DeleteNode)
					DeleteNode->parent->right = 0;
				else if (HasParent(DeleteNode) && DeleteNode->parent->left == DeleteNode)
					DeleteNode->parent->left = 0;
				if (DeleteNode == root) root = 0;
				DeleteNode = 0;
				if (tmp != 0) rebalance(tmp);
			}
			return true;
		}
	}



//--------------------------------------------------------------------------------//
	int getHeight() { //высота для всего дерева
		if (root == 0) return -1;
		return root->height;
	}
};
