#pragma once

#include "binTreeTable.h"

template <typename TypeKey, typename TypeData>
class AvlTreeTable : public BinTreeTable<TypeKey, TypeData> {
private:
	void calculateHeight(Node<TypeKey, TypeData>* n) {
		Node<TypeKey, TypeData>* n1 = n;//?
		while (n1->parent != 0) {
			int hr = 0, hl = 0;
			if (n1->right != 0) hr = n1->right->height;
			if (n1->left != 0) hl = n1->left->height;
			n1->height = my_max(hr, hl);
			n1 = check(n1);
			n1 = n1->parent;
		}
		
		//if (this->root == 0) this->root->height = 0;
		//else {

			//вариант1: сначала пройтись по всем нижним узлам, расставить нули
			//дальше подниматься на один уровень вверх, брать максимум от высот потомков
			//проблема в проходке по этажам
			//вариант2: реверснуть рассчитывание высот, рассчитать с корня, потом 
			//развернуть рассчитанные высоты
			//проблема: как развернуть? есть ли какая-то формула?
			// ко 2варианту: создать tmp с помощью конструктора копирования,
			// расставить в нем высоты сверху вниз
			// свапнуть высоты корня и узлов, у которых нет потомков
			// корню присвоить максимум из высот тех узлов
			// свапнуть следующие два этажа?
			// либо пойти снизу вверх?
			//вариант3: двигаться от begin, возможно с помощью итератора?
			//проблема: движение итератора идет от большего к меньшему
		//}
	}

	Node<TypeKey, TypeData>* check(Node<TypeKey, TypeData>* n) {
		Node<TypeKey, TypeData>* n1 = n;
		int hr = 0, hl = 0;
		if (n1->right != 0) hr = n1->right->height;
		if (n1->left != 0) hl = n1->left->height;
		int delta = hl - hr;
		if (delta < -1) {
			return n1;
		}
		if (delta > -1) {
			return n1;
		}
		//мы передаем ноду, которую добавили или отца удаленной ноды или ноду, у которой точно поменяется высота
		//тут происходит пересчет высот от нашей ноды
		//при пересчете принимаем решение на повороты
	}

	int my_max(int a, int b) {
		if (a >= b)return a;
		else return b;
	}
public:
//--------------------------------------------------------------------------------//
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
				if (other_n1->left != 0 && n1->left == 0) {
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
				else if (other_n1->right != 0 && n1->right == 0) {
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
						if (other_n1->left != 0 && n1->left == 0) {
							other_n2 = other_n1->left;
							n2 = new Node<TypeKey, TypeData>();
							n2->parent = n1;
							n2->left = 0;
							n2->right = 0;
							n2->storage = other_n2->storage;
							n2->height = other_n2->height;
							n1->left = n2;
						}
						else if (other_n1->right != 0 && n1->right == 0) {
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
						if (other_n1->left != 0 && n1->left == 0) {
							other_n2 = other_n1->left;
							n2 = new Node<TypeKey, TypeData>();
							n2->parent = n1;
							n2->left = 0;
							n2->right = 0;
							n2->storage = other_n2->storage;
							n2->height = other_n2->height;
							n1->left = n2;
						}
						else if (other_n1->right != 0 && n1->right == 0) {
							other_n2 = other_n1->right;
							n2 = new Node<TypeKey, TypeData>();
							n2->parent = n1;
							n2->left = 0;
							n2->right = 0;
							n2->storage = other_n2->storage;
							n2->height = other_n2->height;
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
	binTreeIterator<TypeKey, TypeData> insert(const TypeKey& key, const TypeData& d) {//здесь вроде все стандартно, не вижу смысла комментить)
		if (root == 0) {
			root = new Node<TypeKey, TypeData>();
			root->parent = 0;
			root->left = 0;
			root->right = 0;
			root->storage = make_pair(key, d);
			root->height = 0;
			return binTreeIterator<TypeKey, TypeData>(*root);
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
				calculateHeight(n1);
			}
			else if (n1->storage.first == key) {
				n1->storage.second = d;
			}
			return binTreeIterator<TypeKey, TypeData>(*n1);
			//return binTreeIterator<TypeKey, TypeData>(n1->storage);
		}
	}
//--------------------------------------------------------------------------------//
	bool remove(const TypeKey& key) {//наверное, его надо переписать, а то очень плохо выйдет, но это не точно, ещё подумаю
		Node<TypeKey, TypeData>* n1 = root;
		Node<TypeKey, TypeData>* startCheck = 0;//чтобы не искать где мы удалили, мы запоминаем где начинать проверку check
		while (n1 != 0 && n1->storage.first != key) {//ищем нужную ноду по ключу
			if (n1->storage.first < key)
				n1 = n1->right;
			else
				n1 = n1->left;
		}
		if (n1 == 0) //если такого ключа нет, то false
			return false;
		if (n1->storage.first == key) {//если все таки нашли ключ
			Node<TypeKey, TypeData>* nr;//новый "локальный корень" который будет вместе удаленной ноды
			if (n1->right != 0) {//если есть справа что то
				nr = n1->right; //запоминаем правую ноду от удаленной, он новый "локальный корень"
				Node<TypeKey, TypeData>* n2 = nr;//пойдем влево до конца, туда запишем левую ноду удаленной ноды
				while (n2->left != 0)
					n2 = n2->left;
				n2->left = n1->left;//здесь записываем
				n1->left->parent = n2;
				startCheck = n2;//как раз здесь мы запоминаем, где начать, чтобы не искать потом
			}
			else //если справа нет, то просто левую оставляем
				nr = n1->left;
			if (nr == 0) {
				root = nr;
			}
			else if (n1->parent == 0) {
				nr->parent = 0;
				root = nr;
				calculateHeight(root);//изменился корень, надо поменять только у него
			}
			else {
				nr->parent = n1->parent;
				if (n1->parent->left->storage.first == key) {
					n1->parent->left = nr;
				}
				else {
					n1->parent->right = nr;
				}
				if (startCheck == 0) calculateHeight(nr->parent);//если начальное значение, то значит глубоко мы не меняли, начинаем с отца удаленной ноды
				else calculateHeight(startCheck);//иначе начиаем с глубокого места изменения
			}
			return true;
		}
	}
//--------------------------------------------------------------------------------//
};