#pragma once
#include "binTreeTable.h"

template <typename TypeKey, typename TypeData>
class AvlTreeTable : public BinTreeTable<TypeKey, TypeData> {
private:
	int recorrect(Node<TypeKey, TypeData>* n) {
		int rh = 0, lh = 0;
		n->right != 0 ? rh = n->right->height : rh = 0 ;
		n->left != 0 ? lh = n->left->height : lh = 0;
		return lh + rh;
	}
	void smallRight(Node<TypeKey, TypeData>* a) {
		Node<TypeKey, TypeData>* b = a->left;
		a->left = b->right;
		b->right = a;
		recorrect(a);
		recorrect(b);

	}
	void smallLeft(Node<TypeKey, TypeData>* a) {
		Node<TypeKey, TypeData>* b = a->right;
		a->right = b->left;
		b->left = a;
		recorrect(a);
		recorrect(b);
	}
	void bigRight(Node<TypeKey, TypeData>* a) {
		smallLeft(a->left);
		smallRight(a);
	}
	void bigLeft(Node<TypeKey, TypeData>* a) {
		smallRight(a->right);
		smallLeft(a);
	}

	int difference(Node<TypeKey, TypeData>* n) {
		int rh = 0, lh = 0;
		n->right != 0 ? rh = n->right->height : rh = 0 ;
		n->left != 0 ? lh = n->left->height : lh = 0;
		return lh - rh;
	}
	void rebalance(Node<TypeKey, TypeData>* n) {
		//����� ����������� 3 ����., ����� ����� ���� ������� ��� �����, ��� � ������� �������
		Node<TypeKey, TypeData>* c = n; 
		Node<TypeKey, TypeData>* b = c->parent;
		//������ ���� � ������ ����������, ������������ 2 ����
		while(c!=0 && b!=0){
			int diff_c = difference(c);
			int diff_b = difference(b);

			if ((diff_c == -1 || diff_c == 0) && diff_b == -2) {
				smallLeft(b);
				return;
			}
			else if ((diff_c == 1 || diff_c == 0) && diff_b == 2) {
				smallRight(b);
				return;
			}
			//������ ������� �� 1 ���� �����
			c = b;
			b = b->parent;
		}  
		//�������� ��������
		c = n;
		b = c->parent;
		//������ 3��� ����. 
		// a==0 - �������������� ��� �� �����, �� �� � ����� � ����� �� �����������
		Node<TypeKey, TypeData>* a = b->parent;;
		if (a == 0) return;
		//�������� ��� ��� � ���������� ����.
		while(c!=0 && b!=0 && a!=0){
			int diff_c = difference(c);
			int diff_b = difference(b);
			int diff_a = difference(a);

			if (diff_c <= 1 && diff_b == 1 && diff_a == -2) {
				bigLeft(a);
				return;
			}
			else if (diff_c <= 1 && diff_b == -1 && diff_a == 2) {
				bigRight(a);
				return;
			}
			//������ ������� �� 1 ���� �����
			c = b;
			b = a;
			a = a ->parent;
		}
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
				if (other_n1->left != 0 && n1->left == 0) {
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
				else if (other_n1->right != 0 && n1->right == 0) {
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
			return binTreeIterator<TypeKey, TypeData>(*n1,*this);
		}
	}
//--------------------------------------------------------------------------------//
	bool remove(const TypeKey& key) {
		Node<TypeKey, TypeData>* n1 = root;
		Node<TypeKey, TypeData>* startCheck = 0;
		while (n1 != 0 && n1->storage.first != key)
			n1->storage.first < key ? n1 = n1->right : n1 = n1->left;
		if (n1 == 0) //������ ����� ���, �� false
			return false;
		if (n1->storage.first == key) {// ����� ����
			Node<TypeKey, TypeData>* nr;//����� "���������" ������, ������� ����� ������ ��������� ����
			if (n1->right != 0) {//���� ���� ������
				nr = n1->right; //���������� ������ ���� �� ���������, �� ����� "���������" ������
				Node<TypeKey, TypeData>* n2 = nr;//������ ����� �� �����, ���� ������� ����� ���� ��������� ����
				while (n2->left != 0)
					n2 = n2->left;
				n2->left = n1->left;//����� ����������
				n1->left->parent = n2;
				startCheck = n2;//��� ��� ����� �� ����������, ��� ������, ����� �� ������ �����
			}
			else //���� ������ ���, �� ������ ����� ���������
				nr = n1->left;
			if (nr == 0) {
				root = nr;
			}
			else if (n1->parent == 0) {
				nr->parent = 0;
				root = nr;
				rebalance(root);
			}
			else {
				nr->parent = n1->parent;
				if (n1->parent->left->storage.first == key) {
					n1->parent->left = nr;
				}
				else {
					n1->parent->right = nr;
				}
				if (startCheck == 0) rebalance(nr->parent);
				else rebalance(startCheck);
			}
			return true;
		}
	}
//--------------------------------------------------------------------------------//
};


/*Node<TypeKey, TypeData>* n1 = n;
while (n1->parent != 0) {
	int hr = 0, hl = 0;
	if (n1->right != 0) hr = n1->right->height;
	if (n1->left != 0) hl = n1->left->height;
	n1->height = my_max(hr, hl);
	n1 = check(n1);
	n1 = n1->parent;
}*/


//������� �������, �� �������� ������ ����� �����
/*Node<TypeKey, TypeData>* n1 = n;
int h = 0;
int max_h = 0;
while (n1->left != 0) {
	n1 = n1->left;
	h++;
}
if (h > max_h) max_h = h;
while (true) {
	Node<TypeKey, TypeData>* it_node = n1;
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
			it_node = it_node->parent;
			h--;
		}
		if (it_node->parent == 0) {
			it_node = save_node;
			break;
		}
		else if (it_node->parent->left == it_node) {
			it_node = it_node->parent;
			h--;
		}
	}
	n1 = it_node;
	if (h > max_h) max_h = h;
}
return max_h;
*/

//void getHeightTree() {
//	auto i = this->begin();
//	for (i; i != a.end(); ++i) {
//		i->it_node->height = calculateHeight(i->it_node);
//	}
//}

//int calculateHeight(Node<TypeKey,TypeData>*n) {
//	if (n == 0) return -1;

//	int lh = calculateHeight(n->left);
//	int rh = calculateHeight(n->right);
//	return lh > rh ? lh = lh + 1 : rh = rh + 1;
//}

//int my_max(int a, int b) {
//	return a >= b ? a : b;
//}