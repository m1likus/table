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
	BinTreeTable() { //����������� �� ���������
		root = 0;
	}
	//--------------------------------------------------------------------------------//
	BinTreeTable(const BinTreeTable& other) { //����������� �����������
		if (root == 0) 
			other.root = 0;
		else {
			//�� ���� ��� �����������
			//�� ���� �� ������ ������� �� ������ � ��������
			//��� ��� �� ������, ��� � ������������, ����� �� ��������� ����� �� �������� ���������
			//1) ����: ������� ����������, ������� ����� ������� ��������� �����������
			//��������: ��������� ������ ��� �����, ���� ����� ������ - ������ ������, ���� ���������� ��� ������, �� ������ � ��
			//� ��� ����� ���� ��������� ��� ������ ����� ��� ��� ���������, ����������, ��� �� ���� ������
			//�� ������� ���������� ������� ������������ � ���������
			//2) ����� ������ ������� ����� ����, ������� ����� �������� - ���� ��� ���
			//�� ��� ����� ���������� �� ������ ����������, ��� ����� ������� ����� ����
			//3)��� �� ����������� ����������� �������, �� ���� ��� �� �������� ���, ����������� ����� ����� ������ � �� ���� �� �������, �� � ���� ��� �� ���������(
			
		}
	}
	//--------------------------------------------------------------------------------//
	~BinTreeTable() { //����������
		//�� ���� ��� �����������
		//�� ���� �� ������ ������� �� ������ � ��������
		//����� ������� ���� � ���� ������� � ����, ���� � ���� ���� � �������, ���� ������� ����, ��� ������ ��������� � �������� � ������ ������ ������
	}
	//--------------------------------------------------------------------------------//
	//BinTreeTable& operator=(const Table& other) { //�������� ������������
	//�� ���� ��� ��� � ������������, ���� ��������, ��� ����� �������, ����� �������) ��� ������ �������, ��� �� ���� ��������, ������, ��� ������
	//}
	////--------------------------------------------------------------------------------//
	TypeData& operator[] (const TypeKey& key) { //�������� []
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
		//������������ �������� - ������ �� �������� �� ��������� �������
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
		//���������� true/false
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
		//�������� �� ������
	//Iterator<TypeKey, TypeData> begin() {
	//	return Iterator<TypeKey, TypeData>(storage[0]);
		//��������� ������ �� ������, ��� ��� �������� ���� ��� �����������, 
		//������ ����� �������� ������� ����� ��� � ����, ������ ���� ����������� ��������, 
		//� ����� ���� ��� ����� �� ����, �� ������� �������, � ������� �� ���� ��������
	//}
	//--------------------------------------------------------------------------------//
		//�������� �� �����
	//Iterator<TypeKey, TypeData> end() {
	//	Iterator<TypeKey, TypeData> a = begin();
	//	return a + storage.size();
	//}
	//--------------------------------------------------------------------------------//
};