#pragma once
#include "binTreeTable.h"

template <typename TypeKey, typename TypeData>
class AvlTreeTable : public BinTreeTable<TypeKey, TypeData> {
private:
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
		bool change_root = false;//���� ���� ������ ������
		Node<TypeKey, TypeData>* b = a->left;
		if (HasParent(a)) 
			if (a->parent->right == a) a->parent->right = b;//������ � ���� a ������ �� ���� �� b
			else a->parent->left = b;
		else change_root = true; //���� ���� ���, �� �� � �����
		b->parent = a->parent;//������ ���� b

		if (HasRightChild(b)) b->right->parent = a;//���� ������ ��� ���, �� ������ ��� ���� � b �� a
		a->left = b->right;//������ ����

		b->right = a;//������ ����
		a->parent = b;//������ ����

		a = b;//�������� �� �������, � �� � ���������
		b = a->right;

		if (change_root) root = a;

		recorrect(b);
		recorrect(a);
		
	}
	void smallLeft(Node<TypeKey, TypeData>* a) {//����� ��� ��, ��� � � ����� ��������
		bool change_root = false;
		Node<TypeKey, TypeData>* b = a->right;
		if (HasParent(a)) {
			if(a->parent->right==a) a->parent->right = b;
			else a->parent->left = b;
		}
		else change_root = true;
		b->parent = a->parent;

		if (HasLeftChild(b)) b->left->parent = a;
		a->right = b->left;

		b->left = a;
		a->parent = b;

		a = b;
		b = a->left;

		if (change_root) root = a;

		recorrect(b);
		recorrect(a);
	}
	void bigRight(Node<TypeKey, TypeData>* a) {
		smallLeft(a->left);
		smallRight(a);
	}
	void bigLeft(Node<TypeKey, TypeData>* a) {
		smallRight(a->right);
		smallLeft(a);
	}
	void rebalance(Node<TypeKey, TypeData>* n, bool type) {
 		Node<TypeKey, TypeData>* c = n;
		Node<TypeKey, TypeData>* b = 0;
		Node<TypeKey, TypeData>* a = 0;
		int diff_c = 0;
		int diff_b = 0;
		int diff_a = 0;

		recorrect(c);//��������� ������ ��������������� ����.
		while (HasParent(c)) { //����, ���� �� ������ �� �����
			b = c->parent;
			recorrect(b);//��������� ������ ����
			if (HasParent(b)) { // ���� � ���� ���� ����, ����� ���
				a = b->parent;
				recorrect(a);
			}
			else a = 0;

			//������ ��������
			
			diff_c = difference(c);
			diff_b = difference(b);
			diff_a = 0;
			if (a != 0) diff_a = difference(a);

			if (diff_c <= 0 && diff_b == -2) {
				smallLeft(b);
				if (type) return;
			}
			else if (diff_c <= 0 && diff_b == 2) {
				smallRight(b);
				if (type) return;
			}
			else if (diff_c <= 1 && diff_b == 1 && diff_a == -2) {
				bigLeft(a);
				if (type) return;
			}
			else if (diff_c <= 1 && diff_b == -1 && diff_a == 2) {
				bigRight(a);
				if (type) return;
			}
			c = b;
		}
	}



	void smallRight1(Node<TypeKey, TypeData>* a) {
		Node<TypeKey, TypeData>* b = a->left;
		a->left = b->right;
		b->right = a;
		recorrect(a);
		recorrect(b);
	}
	void smallLeft1(Node<TypeKey, TypeData>* a) {
		Node<TypeKey, TypeData>* b = a->right;
		a->right = b->left;
		b->left = a;
		recorrect(a);
		recorrect(b);
	}
	void bigRight1(Node<TypeKey, TypeData>* a) {
		smallLeft1(a->left);
		smallRight1(a);
	}
	void bigLeft1(Node<TypeKey, TypeData>* a) {
		smallRight1(a->right);
		smallLeft1(a);
	}
	void rebalance1(Node<TypeKey, TypeData>* n) {
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
			//��� ������ �������� ����� 2 ����. : c � b.
			diff_c = difference(c);
			diff_b = difference(b);
			if (diff_c <= 0 && diff_b == -2) {
				smallLeft1(b);
			}
			else if (diff_c <= 0 && diff_b == 2) {
				smallRight1(b);
			}
			c = b;
		}
		//���� �� ��������� ����� ��������, �� ���� �������� �������� ����������
		c = n; diff_c = 0; diff_b = 0; diff_a = 0;
		if (HasParent(c)) b = c->parent;
		while (HasParent(c) && HasParent(b)) {
			b = c->parent;
			a = b->parent;
			recorrect(b);
			recorrect(a);
			diff_c = difference(c);
			diff_b = difference(b);
			diff_a = difference(a);
			if (diff_c <= 1 && diff_b == 1 && diff_a == -2) {
				bigLeft1(a);
			}
			else if (diff_c <= 1 && diff_b == -1 && diff_a == 2) {
				bigRight1(a);
			}
			c = b;
			b = a;
		}
	}

	int my_max(int a, int b) {
		return a >= b ? a : b;
	}

public:
	AvlTreeTable() { //����������� �� ���������
		root = 0;
	}
//--------------------------------------------------------------------------------//
	AvlTreeTable(const AvlTreeTable& other) { //����������� �����������
		if (other.root == 0) { //���� ������ - �� ����� ������
			root = 0;
		}
		else {
			root = new Node<TypeKey, TypeData>(); //������� ���� �����
			root->parent = 0; //������ ������
			root->left = 0;
			root->right = 0;
			root->storage = other.root->storage;  //����������� ���������
			root->height = other.root->height;
			Node<TypeKey, TypeData>* n1 = root; //��� ����
			Node<TypeKey, TypeData>* n2 = root; //���� ����
			Node<TypeKey, TypeData>* other_n1 = other.root; //��� ���� � other
			Node<TypeKey, TypeData>* other_n2 = other.root; //���� ���� � other
			while (n2 != 0) { //���� ���� ���� ����
				n1 = n2;
				other_n1 = other_n2;
				if (HasLeftChild(other_n1) && !HasLeftChild(n1)) {
					//���� ����� ������� � other �� ����, � � this ����, ��
					other_n2 = other_n1->left; //�������� � ����� ������� other
					n2 = new Node<TypeKey, TypeData>(); //��� ����, �� �������� ����� ����
					n2->parent = n1; //�������� ���
					n2->left = 0;
					n2->right = 0;
					n2->storage = other_n2->storage;
					n2->height = other_n2->height;
					n1->left = n2; //��������� � ������� this
				}
				else if (HasRightChild(other_n1) && !HasRightChild(n1)) {
					//���� ������ ������� other �� ����, � � this ����, ��
					other_n2 = other_n1->right; //��������� � ������ ������� other
					n2 = new Node<TypeKey, TypeData>(); //������� ����� ����
					n2->parent = n1; //���������
					n2->left = 0;
					n2->right = 0;
					n2->storage = other_n2->storage;
					n2->height = other_n2->height;
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
					root->height = other.root->height;
					Node<TypeKey, TypeData>* n1 = root; //����
					Node<TypeKey, TypeData>* n2 = root; //�����
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
				rebalance(n1,1);
			}
			else if (n1->storage.first == key) {
				n1->storage.second = d;
			}
			return binTreeIterator<TypeKey, TypeData>(*n1,*this);
		}
	}
//--------------------------------------------------------------------------------//
	bool remove1(const TypeKey & key) {
		Node<TypeKey, TypeData>* DeleteNode = root;
		while (DeleteNode !=0 && DeleteNode->storage.first != key)
			DeleteNode->storage.first < key ? DeleteNode = DeleteNode->right : DeleteNode = DeleteNode->left;
		if (DeleteNode == 0) return false;
		else if (DeleteNode->storage.first == key) {
			Node<TypeKey, TypeData>* tmp = 0;
			if (HasRightChild(DeleteNode)) {
				tmp = DeleteNode->right;
				while (HasLeftChild(tmp))
					tmp = tmp->left; //����� min
				//���������������
				if (DeleteNode->right == tmp) { //������ ����� DeleteNode �.�. ���� tmp
					if (DeleteNode == root) root = tmp;
					tmp->parent = DeleteNode->parent;
					if (HasParent(DeleteNode)) {
						if (DeleteNode->parent->left == DeleteNode) DeleteNode->parent->left = tmp;
						else if (DeleteNode->parent->right == DeleteNode) DeleteNode->parent->right = tmp;
					}
					tmp->left = DeleteNode->left;
					if (HasLeftChild(DeleteNode)) {
						DeleteNode->left->parent = tmp;
					}
					tmp->height = DeleteNode->height;
					DeleteNode = 0;
					rebalance1(tmp);
				}
				else {
					if (DeleteNode == root) root = tmp;
					tmp->parent->left = tmp->right;
					tmp->parent = DeleteNode->parent;
					if (HasParent(DeleteNode)) {
						if (DeleteNode->parent->left == DeleteNode) DeleteNode->parent->left = tmp;
						else if (DeleteNode->parent->right == DeleteNode) DeleteNode->parent->right = tmp;
					}
					tmp->left = DeleteNode->left;
					if (HasLeftChild(DeleteNode)) {
						DeleteNode->left->parent = tmp;
					}
					tmp->right = DeleteNode->right;
					if (HasRightChild(DeleteNode)) {
						DeleteNode->right->parent = tmp;
					}
					tmp->height = DeleteNode->height;
					DeleteNode = 0;
					rebalance1(tmp);
				}
			}
			else if (HasLeftChild(DeleteNode)) {//�.� ���� �����, ��� ������
				if (DeleteNode == root) root = tmp;
				tmp = DeleteNode->left;
				tmp->parent = DeleteNode->parent;
				if (HasParent(DeleteNode)) {
					if (DeleteNode->parent->left == DeleteNode) DeleteNode->parent->left = tmp;
					else if (DeleteNode->parent->right == DeleteNode) DeleteNode->parent->right = tmp;
				}
				tmp->height = DeleteNode->height;
				rebalance1(tmp);
				DeleteNode = 0;
			}
			else {
				if (DeleteNode == root) root = tmp;
				if (HasParent(DeleteNode)) {
					tmp = DeleteNode->parent;
					if (DeleteNode->parent->right == DeleteNode) DeleteNode->parent->right = 0;
					else if (DeleteNode->parent->left == DeleteNode) DeleteNode->parent->left = 0;
				}
				DeleteNode = 0;
				if (tmp!=0)rebalance1(tmp);
			}
			return true;
		}
	}


	bool remove(const TypeKey& key) {
		Node<TypeKey, TypeData>* n1 = root; //�������� � �����
		Node<TypeKey, TypeData>* startCheck = 0;
		while (n1 != 0 && n1->storage.first != key)
			n1->storage.first < key ? n1 = n1->right : n1 = n1->left;
		if (n1 == 0) //������ ����� ���, �� false
			return false;
		if (n1->storage.first == key) {// ����� ����
			Node<TypeKey, TypeData>* nr = 0;//����� "���������" ������, ������� ����� ������ ��������� ����
			if (HasRightChild(n1)) {//���� ���� ������
				nr = n1->right; //���������� ������ ���� �� ���������, �� ����� "���������" ������
				Node<TypeKey, TypeData>* n2 = nr;//������ ����� �� �����, ���� ������� ����� ���� ��������� ����
				while (HasLeftChild(n2))
					n2 = n2->left;
				n2->left = n1->left;//����� ����������
				if (HasLeftChild(n1))
					n1->left->parent = n2;
				startCheck = n2;//��� ��� ����� �� ����������, ��� ������, ����� �� ������ �����
			}
			else if (HasLeftChild(n1))//���� ������ ��� � ����� ����, �� ������ ����� ���������
				nr = n1->left;

			
			if (nr == 0 && n1->parent == 0) {//������� �� ����, �� ���� ����, ������ ������
				root = 0;
			}
			else if (n1->parent == 0) {//�����-�� ������� ����, �� ��������� ������� ���� ������
				nr->parent = 0;
				root = nr;
				rebalance(root, 0);
			}
			else {//��� ����
				if(nr!=0) nr->parent = n1->parent;//���� ������� ������, �� ������ � ��� �� ���������� � ������ ��� ������
				if (n1->parent->left != 0 && n1->parent->left->storage.first == key)
					n1->parent->left = nr;
				else
					n1->parent->right = nr;
				if (startCheck == 0) {
					if (nr == 0) rebalance(n1->parent, 0);
					else rebalance(nr, 0);
				}
				else rebalance(startCheck,0);
			}
			delete n1;
			return true;
		}
	}
//--------------------------------------------------------------------------------//
	int getHeight() { //������ ��� ����� ������
		return root->height;
	}
};

