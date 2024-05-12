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
		if (!HasGrandparent(node)) return false;
		if (node->parent->parent->left == node->parent) {
			if (!HasRightChild(node->parent->parent)) return false;
		}
		else {
			if (!HasLeftChild(node->parent->parent)) return false;
		}
		return true;
	}

	Node <TypeKey, TypeData>* Uncle (Node <TypeKey, TypeData>* node) {
		if (node->parent->parent->left == node->parent) {
			if (HasRightChild(node->parent->parent))
				return node->parent->parent->right;
		}
		else {
			if (HasLeftChild(node->parent->parent))
				return node->parent->parent->left;
		}
	}

	Node <TypeKey, TypeData>* Grandparent(Node <TypeKey, TypeData>* node) {
		return node->parent->parent;
	}



	void Repaint(Node <TypeKey, TypeData>* node) {
		//надо поменять раскраски отца и деда
		//может нарушиться правило для деда,вызывать рекурсивно перебалансировку
		node->parent->colour = black;
		node->parent->parent->colour = red;
		Uncle(node)->colour = black;
		rebalance(node->parent->parent);
	}


	bool Check(Node <TypeKey, TypeData>* node) {
		if (node->colour == red) { //если сама вершина красная
			if (HasParent(node)) { 
				if (node->parent->colour == red) return true; //если отец - красный, то нужна ребалансировка
			}
			if (HasLeftChild(node)) {
				if (node->left->colour == red) return true; // если левый сын - красный, то ..
			}
			if (HasRightChild(node)) {
				if (node->right->colour == red) return true; // если правый сын - красный, то ..
			}
			return false;
		}
		return false;
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

		//recorrect(a);
		//recorrect(b);
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

		//recorrect(a);
		//recorrect(b);
	}
	void bigRight(Node<TypeKey, TypeData>* a) {
		smallRight(a);
		a->colour=red;
		a->parent->colour = black;
	}
	void bigLeft(Node<TypeKey, TypeData>* a) {
		smallLeft(a);
		a->colour = red;
		a->parent->colour = black;
	}

	void rebalance(Node <TypeKey, TypeData>* node) {
		if (node == root) {
			node->colour = black;
			return;
		}
		//проверка на нарушение 4 правила
		else if (!Check(node)) return;
		//нарушение есть - начинаем магию.


		//случай 1: дядя красный, решение - перекраска.
		if (HasUncle(node) && Uncle(node)->colour == red)
			Repaint(node);
		else { //е. дядя не красный - он всегда чёрный
			//случай 2: черный дядя, папа и дед в разных сторонах.
			if (HasGrandparent(node) && node->parent->right == node && Grandparent(node)->left == node->parent){
				smallLeft(node->parent);
				node = node->left;
			}
			else if (HasGrandparent(node) && node->parent->left == node && Grandparent(node)->right == node->parent){
				smallRight(node->parent);
				node = node->right;
			}
			//случай 3: черный дядя, папа и дед в одной стороне
			if (HasGrandparent(node)) {
				if (Grandparent(node)->left == node->parent) { //папа(P) и дед(G) слева, значит и узел(X) должен быть слева
					if (node->parent->left == node) bigRight(Grandparent(node));
					else return;
				}
				else if ((Grandparent(node)->right == node->parent)) { //папа(P) и дед(G) справа, значит и узел(X) должен быть справа
					if (node->parent->right == node) bigLeft(Grandparent(node));
					else return;
				}
			}
			else return;
		}
	}

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
				n1->parent = n2;
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
				Node<TypeKey, TypeData>* saveNode = 0;
				if (DeleteNode->right == tmp) { //правым сыном DeleteNode м.б. сама tmp
					if (HasLeftChild(DeleteNode)) {
						DeleteNode->left->parent = tmp;
					}
				}
				else {
					tmp->parent->left = tmp->right;
					if (HasRightChild(tmp)){
						tmp->right->parent = tmp->parent;
						saveNode = tmp->right;
					}
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
				if (saveNode != 0) rebalance(saveNode);
				else rebalance(tmp);
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
				tmp->colour = DeleteNode->colour;
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
			}
			return true;
		}
	}
	//--------------------------------------------------------------------------------//
	int getHeight() { //высота для всего дерева
		if (root == 0) return -1;
		int h = 0;
		int max_h = 0;
		Node<TypeKey, TypeData>* n = root;
		while (HasLeftChild(n)) {
			n = n->left;
			if (n->colour == black) h++;
		}
		if (h > max_h) max_h = h;
		while (true) {
			Node<TypeKey, TypeData>* it_node = n;
			if (HasRightChild(it_node)) {
				it_node = it_node->right;
				if (it_node->colour == black) h++;
				while (HasLeftChild(it_node)) {
					it_node = it_node->left;
					if (it_node->colour == black) h++;
				}
			}
			else {
				Node<TypeKey, TypeData>* save_node = it_node;
				while (HasParent(it_node) && it_node->parent->right == it_node) {
					if (it_node->colour == black) h--;
					it_node = it_node->parent; 
					
				}
				if (!HasParent(it_node)) {
					it_node = save_node;
					break;
				}
				else if (it_node->parent->left == it_node) {
					if (it_node->colour == black) h--;
					it_node = it_node->parent;
					
				}
			}
			n = it_node;
			if (h > max_h) max_h = h;
		}
		return max_h;
	}
};

