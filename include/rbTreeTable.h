#pragma once
#include "binTreeTable.h"

template <typename TypeKey, typename TypeData>
class RbTreeTable : public BinTreeTable<TypeKey, TypeData> {
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
	Node<TypeKey, TypeData>* smallRight(Node<TypeKey, TypeData>* a) {
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

		if (change_root) root = b;

		//recorrect(a);
		//recorrect(b);
		return b;
	}
	Node<TypeKey, TypeData>* smallLeft(Node<TypeKey, TypeData>* a) {//����� ��� ��, ��� � � ����� ��������
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

		if (change_root) root = b;

		//recorrect(a);
		//recorrect(b);
		return b;
	}
	Node<TypeKey, TypeData>* bigRight(Node<TypeKey, TypeData>* a) {
		smallLeft(a->left);
		a = smallRight(a);
		return a;
	}
	Node<TypeKey, TypeData>* bigLeft(Node<TypeKey, TypeData>* a) {
		smallRight(a->right);
		a = smallLeft(a);
		return a;
	}

	int difference(Node<TypeKey, TypeData>* node) {
		int rh = -1, lh = -1;
		HasRightChild(node) ? rh = node->right->height : rh = -1;
		node->left != 0 ? lh = node->left->height : lh = -1;
		return lh - rh;
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

			if (diff_c <= 0 && diff_b == -2 && c==b->right) {//� �� ���������
				b = smallLeft(b);//��� ��������� �� ������ � ��� ��� b ���������, �� ������ �� ������ ���, �������� �� ���� ������ ����� ������ ��������
							//c=b; b=b->parent ?
				// 	 b
				// /   \
				// P    c
				//	   / \
				//    Q   R
				//
				//		c
				//     / \
				//    b   R 
				//   / \
				//  P   Q
				// 
				if (type) return;
			}
			else if (diff_c >= 0 && diff_b == 2 && c == b->left) {
				b = smallRight(b);
				if (type) return;
			}
			else if (diff_b == 1 && diff_a == -2 && c == b->left && b == a->right) {
				b = bigLeft(a);
				if (type) return;
			}
			else if (diff_b == -1 && diff_a == 2 && c == b->right && b == a->left) {
				b = bigRight(a);
				if (type) return;
			}
			c = b;
		}
	}

	void rebalanceInsert(Node<TypeKey, TypeData>* n) {
		while (n->parent!=0 && n->parent->colour == true) {
			if (n->parent->parent->left == n->parent) {
				if (n->parent->parent->right!=0 && n->parent->parent->right->colour ==true) {
					n->parent->colour = false;
					n->parent->parent->right->colour = false;
					n->parent->parent->colour = true;
					n = n->parent->parent;
				}
				else {
					if (n->parent->right == n) n = smallLeft(n->parent)->left;
					n->parent->colour = false;
					n->parent->parent->colour = true;
					smallRight(n->parent->parent);
				}
			}
			else {
				if (n->parent->parent->left != 0 && n->parent->parent->left->colour == true) {
					n->parent->colour = false;
					n->parent->parent->left->colour = false;
					n->parent->parent->colour = true;
					n = n->parent->parent;
				}
				else {
					if (n->parent->left == n) n = smallRight(n->parent)->right;
					n->parent->colour = false;
					n->parent->parent->colour = true;
					smallLeft(n->parent->parent);
				}
			}
		}
		root->colour = false;
	}

	void rebalanceRemove(Node<TypeKey, TypeData>* n) {
		while (n->colour == false && n->parent != 0) {
			if (n->parent->left == n && n->parent->right != 0) {
				Node<TypeKey, TypeData>* brother = n->parent->right;
				Node<TypeKey, TypeData>* parent = n->parent;
				if (brother->colour == true) {
					brother->colour = false;
					parent->colour = true;
					n = smallLeft(parent)->left;
					brother = n->parent->right;
					parent = n->parent;
				}
				if (brother != 0) {
					if (HasLeftChild(brother) && brother->left->colour == false && HasRightChild(brother) && brother->right->colour == false) {
						brother->colour = true;
						parent->colour = false;
						n = parent;
					}
					else {
						if (HasLeftChild(brother) && brother->left->colour == true && HasRightChild(brother) && brother->right->colour == false) {
							brother->left->colour = false;
							brother->colour = true;
							smallRight(brother);
							brother = n->parent->right;
							parent = n->parent;
						}
						brother->colour = parent->colour;
						parent->colour = false;
						if (brother->right != 0) brother->right->colour = false;
						smallLeft(parent);
						n = root;
					}
				}
				else n = parent;
			}
			else if (n->parent->right == n && n->parent->left != 0) {
				Node<TypeKey, TypeData>* brother = n->parent->left;
				Node<TypeKey, TypeData>* parent = n->parent;
				if (brother->colour == true) {
					brother->colour = false;
					parent->colour = true;
					n = smallRight(parent)->right;
					brother = n->parent->left;
					parent = n->parent;
				}
				if (brother != 0) {
					if (HasLeftChild(brother) && brother->left->colour == false && HasRightChild(brother) && brother->right->colour == false) {
						brother->colour = true;
						parent->colour = false;
						n = parent;
					}
					else {
						if (HasLeftChild(brother) && brother->left->colour == false && HasRightChild(brother) && brother->right->colour == true) {
							brother->right->colour = false;
							brother->colour = true;
							smallLeft(brother);
							brother = n->parent->left;
							parent = n->parent;
						}
						brother->colour = parent->colour;
						parent->colour = false;
						if (brother->left != 0) brother->left->colour = false;
						smallRight(parent);
						n = root;
					}
				}
				else n = parent;
			}
			else n = n->parent;
		}
		n->colour = false;
		root->colour = false;
	}

	int my_max(int a, int b) {
		return a >= b ? a : b;
	}

public:
	RbTreeTable() { //����������� �� ���������
		root = 0;
	}
//--------------------------------------------------------------------------------//
	RbTreeTable(const RbTreeTable& other) { //����������� �����������
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
			root->colour = false;
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
				n1->colour = true;
				if (n2->storage.first < n1->storage.first)
					n2->right = n1;
				else
					n2->left = n1;
				rebalanceInsert(n1);
			}
			else if (n1->storage.first == key) {
				n1->storage.second = d;
			}
			return binTreeIterator<TypeKey, TypeData>(*n1,*this);
		}
	}
//--------------------------------------------------------------------------------//
	bool remove(const TypeKey& key) {
		Node<TypeKey, TypeData>* n1 = root; //�������� � �����
		while (n1 != 0 && n1->storage.first != key)
			n1->storage.first < key ? n1 = n1->right : n1 = n1->left;
		if (n1 == 0) //������ ����� ���, �� false
			return false;

		if (n1->storage.first == key) {// ����� ����
			if (!HasRightChild(n1) && !HasLeftChild(n1)) {
				if (HasParent(n1)) {
					if (n1->parent->left == n1) n1->parent->left = 0;
					else n1->parent->right = 0;
				}
				else {
					root = 0;
				}
				delete n1;
				return true;
			}
			if (HasRightChild(n1)) {
				Node<TypeKey, TypeData>* new_root = n1->right; //�������� ������
				Node<TypeKey, TypeData>* startCheck = 0;
				while (HasLeftChild(new_root)) {
					new_root = new_root->left;
				}//������ �� � ��� �����
				if (new_root->parent != n1) {//���� � ������� ���� ��� ���� �����, �� ��� �������� ���, ����� � ��������, ��� ��� ��� ����� �������� ������ �� ��� ��������� �������
					if (HasRightChild(new_root)) {//� ������� ���� ����� ������ ������
						new_root->parent->left = new_root->right;
						new_root->right->parent = new_root->parent;
					}
					else new_root->parent->left = 0;
					//���� ������� �������� �����, ������� �������� ����� "������" ��������� ��� ������ ����
					startCheck = new_root->parent;
				}
				else {//���� ��� ������ ��� ��� ��������� �������, �� �� ������ ����� ������ �� ��� ����, ����� �� ������)
					if (HasRightChild(new_root))
						new_root->right->parent = n1;
					n1->right = new_root->right;
					startCheck = new_root;//���� �� �� ���������� ������, �� ������ � ������ �������� �����
				}
				if (!HasParent(n1)) //�������� �� ������
					root = new_root;
				else if (n1->parent->left == n1)//������ �������� � ��� ��������� �������
					n1->parent->left = new_root;
				else 
					n1->parent->right = new_root;

				new_root->parent = n1->parent;//������ �������� � ������ �������� �����
				new_root->right = n1->right;
				if (HasRightChild(new_root))
					new_root->right->parent = new_root;
				new_root->left = n1->left;
				if (HasLeftChild(new_root)) 
					new_root->left->parent = new_root;
				if (n1->colour == false)
					rebalanceRemove(new_root);
				delete n1;
				return true;
			}
			if (HasLeftChild(n1)) {//���� ��� ���� ������, �� ���� �����
				Node<TypeKey, TypeData>* new_root = n1->left;
				if (!HasParent(n1))//�������� �� ������
					root = new_root;
				else if (n1->parent->left == n1)//������ ������ � ����
					n1->parent->left = new_root;
				else
					n1->parent->right = new_root;
				new_root->parent = n1->parent;//������ ������ ������ ���������� �����
				if (n1->colour == false)
					rebalanceRemove(new_root);
				delete n1;
				return true;
			}
		}

	}
//--------------------------------------------------------------------------------//
	int getHeight() { //������ ��� ����� ������
		return root->height;
	}
};

