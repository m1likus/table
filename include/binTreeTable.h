#pragma once

#include "table.h"

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
class binTreeTable : public baseTable<TypeKey,TypeData> {
protected:
	Node<TypeKey,TypeData>* begin = NULL;
public:
	//--------------------------------------------------------------------------------//
	binTreeTable() { //����������� �� ���������
		begin = 0;
	}
	//--------------------------------------------------------------------------------//
	binTreeTable(const binTreeTable & other) { //����������� �����������
		this = other;
	}
	//--------------------------------------------------------------------------------//
	~binTreeTable() { //����������
		
	}
	//--------------------------------------------------------------------------------//
	binTreeTable& operator=(const Table& other) { //�������� ������������
		
	}
	//--------------------------------------------------------------------------------//
	TypeData& operator[] (const TypeKey& key) { //�������� []
		
	}
	//--------------------------------------------------------------------------------//
		//������������ �������� - ������ �� �������� �� ��������� �������
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
		//���������� true/false
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
			return true;//���������
		}
	}
	int size() {
		return 0;
	}
	//--------------------------------------------------------------------------------//
		//�������� �� ������
	Iterator<TypeKey, TypeData> begin() {
		return Iterator<TypeKey, TypeData>(make_pair(0,0));
	}
	//--------------------------------------------------------------------------------//
		//�������� �� �����
	Iterator<TypeKey, TypeData> end() {
		Iterator<TypeKey, TypeData> a = begin();
		return a + storage.size();
	}
	//--------------------------------------------------------------------------------//
};