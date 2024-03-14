#pragma once

#include <string>
#include "table.h"

template <typename TypeKey, typename TypeData>
class Node {
public:
	pair<TypeData,TypeKey> store;
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
		if (root == 0) 
			other.root = 0;
		else {
			//не знаю как реализовать
			//по идее мы должны бродить по дереву и занулять
			//тут уже не выйдет, как с деструктором, здесь не получится какой то ориентир придумать
			//1) идея: завести переменную, которая будет хранить последнее перемещение
			//например: начальный проход это влево, если влево нельзя - значит вправо, если предыдущий был вправо, то наверх и тд
			//и там можно поля проверять для сверки какой шаг был последний, предыдущий, как мы туда попали
			//но решение попахивает сложной реализвацией и путаницей
			//2) можно просто сделать новое поле, которые будет говорить - были или нет
			//но как будто реализация не сильно облегчится, все равно ползать через цикл
			//3)как то реализовать рекурсивную функцию, но пока что не придумал как, реализвация будет самой крутой и по идее не сложной, но я пока что не додумался(
			
		}
	}
	//--------------------------------------------------------------------------------//
	~BinTreeTable() { //деструктор
		//не знаю как реализовать
		//по идее мы должны бродить по дереву и занулять
		//можно сделать цикл и идти сначала в лево, если в лево есть и направо, если направо есть, при выходе удаляться и занулять у предка откуда пришел
	}
	//--------------------------------------------------------------------------------//
	//BinTreeTable& operator=(const Table& other) { //оператор присваивания
	//по идее тут как с копированием, надо пописать, мне нужен перерыв, потом доделаю) или вместе сделаем, или ты сама сделаешь, короче, как выйдет
	//}
	////--------------------------------------------------------------------------------//
	TypeData& operator[] (const TypeKey& key) { //оператор []
		Node<TypeKey, TypeData>* n1 = root;
		while (n1 != 0 && n1->store.first != key) {
			if (n1->store.first < key)
				n1 = n1->right;
			else
				n1 = n1->left;
		}
		if (n1 == 0) throw "not_found";
		if (n1->store.first != key)
			return n1->store.second;
	}
	//--------------------------------------------------------------------------------//
		//возвращаемое значение - ссылка на итератор на найденный элемент
	Iterator<TypeKey, TypeData> find(const TypeKey& key){
		Node<TypeKey, TypeData>* n1 = root;
		while (n1 != 0 && n1->store.first != key) {
			if (n1->store.first < key)
				n1 = n1->right;
			else
				n1 = n1->left;
		}
		return Iterator<TypeKey, TypeData>(n1->store);
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
			root->store = make_pair(key, d);
			return Iterator<TypeKey, TypeData>(root->store);
		}
		else {
			Node<TypeKey, TypeData>* n1 = root;
			Node<TypeKey, TypeData>* n2 = 0;
			while (n1 != 0 && n1->store.first != key) {
				n2 = n1;
				if (n1->store.first < key)
					n1 = n1->right;
				else
					n1 = n1->left;
			}
			if (n1 == 0) {
				n1 = new Node<TypeKey, TypeData>();
				n1->store = make_pair(key, d);
				n1->left = 0;
				n1->right = 0;
				n1->parent = n2;
				if (n2->store.first < n1->store.first)
					n2->right = n1;
				else
					n2->left = n1;
			}
			else if (n1->store.first == key) {
				n1->store.second = d;
			}
			return Iterator<TypeKey, TypeData>(n1->store);
		}
	}
	//--------------------------------------------------------------------------------//
		//возвращаем true/false
	bool remove(const TypeKey& key) {
		Node<TypeKey, TypeData>* n1 = root;
		while (n1 != 0 && n1->store.first != key) {
			if (n1->store.first < key)
				n1 = n1->right;
			else
				n1 = n1->left;
		}
		if (n1 == 0)
			return false;
		if (n1->store.first == key) {
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
			if (n1->parent == 0)
				root = nr;
			else {
				nr->parent = n1->parent;
				if (n1->parent->left->store.first == key)
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