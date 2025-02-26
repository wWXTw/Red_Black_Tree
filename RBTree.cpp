#include "RBTree.h"

// ��������Ĺ��캯��
RBNode::RBNode(int v, bool b, RBNode* f, RBNode* l, RBNode* r)
	: value(v), blacked(b), father(f), left(l), right(r) {}

// �����������������
RBNode* RBNode::leftRotate(RBNode* root) {
	// �����ǰ�����ߵ�ǰ�����ҽ��Ϊ�����޷���������
	if (this == nullptr || this->right == nullptr) return root;

	RBNode* curFather, * curRight, * rightLeft;
	bool isLeft;
	// ��ǰ���ĸ����
	curFather = this->father;
	// ��ǰ�����ҷ�֧
	curRight = this->right;
	// �ҷ�֧�������֧
	rightLeft = curRight->left;
	// ȷ����ǰ����Ǹ��������֧�����ҷ�֧
	isLeft = curFather && curFather->left == this;

	// �ҷ�֧�������֧��������Ϊ��,��������Ϊ��ǰ�����ҷ�֧
	if (rightLeft != nullptr) {
		this->right = rightLeft;
		rightLeft->father = this;
	}
	else {
		this->right = nullptr;
	}

	// ���ҽ���ƶ�����ǰ����λ��
	this->father = curRight;
	curRight->left = this;
	curRight->father = curFather;
	if (curFather == nullptr) {
		// ˵����ǰ��������Ǹ��ڵ�
		return curRight;
	}
	else {
		// ˵����ǰ������㲻�Ǹ��ڵ�
		if (isLeft) {
			curFather->left = curRight;
		}
		else {
			curFather->right = curRight;
		}
	}
	return root;
}

// �����������������
RBNode* RBNode::rightRotate(RBNode* root) {
	// �����ǰ�����ߵ�ǰ�������֧Ϊ�����޷�����
	if (this == nullptr || this->left == nullptr) return root;

	RBNode* curFather, * curLeft, * leftRight;
	bool isLeft;
	// ��ǰ���ĸ����
	curFather = this->father;
	// ��ǰ�������֧
	curLeft = this->left;
	// ���֧�����ҷ�֧
	leftRight = curLeft->right;
	// ȷ����ǰ����Ǹ��������֧�����ҷ�֧
	isLeft = curFather && curFather->left == this;

	// ���֧�����ҷ�֧�����Ϊ�գ���������Ϊ��ǰ�������֧
	if (leftRight != nullptr) {
		this->left = leftRight;
		leftRight->father = this;
	}
	else {
		this->left = nullptr;
	}

	// �������ƶ�����ǰ����λ��
	this->father = curLeft;
	curLeft->right = this;
	curLeft->father = curFather;
	if (curFather == nullptr) {
		// ˵����ǰ�����Ľ���Ǹ��ڵ�
		return curLeft;
	}
	else {
		// ˵����ǰ�����Ľ�㲻�Ǹ��ڵ�
		if (isLeft) {
			curFather->left = curLeft;
		}
		else {
			curFather->right = curLeft;
		}
	}
	return root;
}

// �������Ĺ��캯��
RBTree::RBTree() {
	root = new RBNode;
}

// ����������ӽ��
int RBTree::addNode(int value) {
	if (!root->blacked) {
		// �����ǰ��������ɫΪ��ɫ��˵���ú����û�н��,ֱ�Ӳ���
		RBNode* cur = new RBNode(value);
		balanceInsert(cur, nullptr, 0);
	}
	else {
		// ������Ѱ�Һ��ʵĲ���λ��
		RBNode* p = root;
		RBNode* father = new RBNode;
		int pos = 0;
		while (p) {
			if (p->value == value) {
				// ���ֵ��ͻ,���ش�����
				return -1;
			}
			else if (p->value < value) {
				// ��¼��ǰ�Ľ����Ϊ��¼�ĸ����
				father = p;
				p = p->right;
				// pos��¼Ϊ1,����ǰ��pΪfather���ҽ��
				pos = 1;
			}
			else {
				// ��¼��ǰ�Ľ����Ϊ��¼�ĸ����
				father = p;
				p = p->left;
				// pos��¼Ϊ2,����ǰ��pΪfather������
				pos = 2;
			}
		}
		// ���е�����,p�϶�Ϊ��,father�м�¼�������λ�õĸ����
		RBNode* cur = new RBNode(value, false, father);
		balanceInsert(cur, father, pos);
	}
	// ���ز���ɹ���
	return 1;
}

// ��������ɾ�����
int RBTree::deleteNode(int value) {
	RBNode* father = nullptr;
	int pos = 0;
	if (!root->blacked) {
		// �����Ϊ��ֱ�ӷ���-1
		return -1;
	}
	else {
		RBNode* p = root;
		while (p) {
			if (p->value == value) {
				// �ҵ���ǰĿ�����,������ֵ��ǰ�������ߺ�̽�㽻��(����еĻ�)
				if (p->left) {
					RBNode* pa = p->left;
					RBNode* pt = pa->right;
					pos = 2;
					// Ѱ��ǰ�����
					while (pt) {
						pa = pt;
						pt = pt->right;
						pos = 1;
					}
					// ��Ŀ������ǰ������ֵ������ɾ��ǰ�����
					p->value = pa->value;
					pa->value = value;
					balanceDelete(pa, pa->father, pos);
				}
				else if (p->right) {
					RBNode* pa = p->right;
					RBNode* pt = pa->left;
					pos = 1;
					// Ѱ�Һ�̽��
					while (pt) {
						pa = pt;
						pt = pt->left;
						pos = 2;
					}
					// ��Ŀ�������̽���ֵ������ɾ����̽��
					p->value = pa->value;
					pa->value = value;
					balanceDelete(pa, pa->father, pos);
				}
				else {
					// Ŀ����ΪҶ�ӽ��,ֱ��ɾ��
					balanceDelete(p, p->father, pos);
				}
				return 1;
			}
			else if (p->value < value) {
				// ��ǰ���ֵС��Ŀ��,ǰ��������
				father = p;
				p = p->right;
				pos = 1;
			}
			else {
				// ��ǰ���ֵС��Ŀ��,ǰ��������
				father = p;
				p = p->left;
				pos = 2;
			}
		}
		// û��������,����-1
		return -1;
	}
}

// ��������ƽ�ⷽ��������
void RBTree::balanceInsert(RBNode* cur, RBNode* father, int pos) {
	if (cur->father == nullptr) {
		// �����Ϊ��˵���������в�����һ�������,ֱ�ӽ��������ɫ��Ϊ��ɫ����
		cur->blacked = true;
		// ���½ṹ�ĸ��ڵ�
		root = cur;
	}
	else if (father->blacked) {
		// �����Ϊ�ڽ����ֱ�Ӳ����ɫ��㼴��
		// ����posֵȷ���ӽ�㷽��λ��
		if (pos == 1) {
			father->right = cur;
		}
		else if (pos == 2) {
			father->left = cur;
		}
	}
	else {
		// �����Ϊ����
		RBNode* grand = father->father;
		// ����posֵȷ���ӽ�㷽��λ��
		if (pos == 1) {
			father->right = cur;
		}
		else if (pos == 2) {
			father->left = cur;
		}
		if (grand->left && grand->right) {
			// �游�����������˶��к�������
			// �����������,��������������㶼��Ϊ��ɫ,���游����Ϊ��ɫ���,�൱�游����ϸ���һ��
			grand->left->blacked = true;
			grand->right->blacked = true;
			grand->blacked = false;
			// ȷ���游�������丸�����˵�����㻹���ҽ��
			int g_pos;
			if (!grand->father) {
				// �游���û�и����
				g_pos = 0;
			}
			else if (grand->father->value > grand->value) {
				// �鸸���Ϊ����
				g_pos = 2;
			}
			else {
				// �鸸���Ϊ�ҽ��
				g_pos = 1;
			}
			// �游��������һ����˵�൱�ڲ���һ���µĺ���,��ȡ�ݹ����
			balanceInsert(grand, grand->father, g_pos);
		}
		else {
			// �游���ֻ��һ���к�������
			int f_pos;
			// �жϸ����������游����λ��
			if (grand->value > father->value) {
				// �����Ϊ�游��������
				f_pos = 2;
			}
			else {
				// �����Ϊ�游�����ҽ��
				f_pos = 1;
			}
			// ����pos��f_pos��ȡ������������
			if (pos == 2 && f_pos == 2) {
				// L-L�ṹ
				// ��-�游��㽻����ɫ����游�������
				father->blacked = true;
				grand->blacked = false;
				root = grand->rightRotate(root);
			}
			else if (pos == 1 && f_pos == 1) {
				// R-R�ṹ
				// ��-�游��㽻����ɫ����游�������
				father->blacked = true;
				grand->blacked = false;
				root = grand->leftRotate(root);
			}
			else if (pos == 2 && f_pos == 1) {
				// R-L�ṹ
				// �ȶԸ�����������
				root = father->rightRotate(root);
				// ��ǰ������游��㽻����ɫ����游�������
				cur->blacked = true;
				grand->blacked = false;
				root = grand->leftRotate(root);
			}
			else if (pos == 1 && f_pos == 2) {
				// L-R�ṹ
				// �ȶԸ�����������
				root = father->leftRotate(root);
				// ��ǰ������游��㽻����ɫ����游�������
				cur->blacked = true;
				grand->blacked = false;
				root = grand->rightRotate(root);
			}
		}
	}
}
	
// ��������ƽ�ⷽ��ɾ�����
void RBTree::balanceDelete(RBNode * cur, RBNode * father, int pos) {
	if (father == nullptr) {
		// Ϊ�����,����ɫ��Ϊ��ɫ����
		cur->blacked = false;
	}
	else if (!cur->blacked) {
		// Ϊ��ɫҶ�ӽ��,ֱ��ɾ������
		if (pos == 1) {
			father->right = nullptr;
		}
		else {
			father->left = nullptr;
		}
		delete cur;
	}
	else if (cur->blacked) {
		// Ϊ��ɫҶ�ӽ��,��Ҫ�鿴�ֵܽ������
		// ͬʱɾ����ǰ���(�����������,����������ӽ����������)
		RBNode* brother = new RBNode;
		if (pos == 1) {
			brother = father->left;
			if (cur->right) {
				// ̮������µ�ǰ���ݽ���븸���ķ���һ����̮�ݽ�����֧���ķ���һ��
				// ̮�ݽ���Ǹ��������ӽ��,��ô��ֻ���������ӽ�����з�֧
				// ������������ӽ����������,�����������̮�ݿյ�
				father->right = cur->right;
				cur->right->father = father;
			}
			else {
				// ��ͨҶ�ӽ��ֱ��ɾ�����ÿ����������
				father->right = nullptr;
			}
			delete cur;
		}
		else if (pos == 2) {
			brother = father->right;
			if (cur->left) {
				// ̮�ݽ���Ǹ��������ӽ��,��ô��ֻ���������ӽ�����з�֧
				// ������������ӽ����������,�����������̮�ݿյ�
				father->left = cur->left;
				cur->left->father = father;
			}
			else {
				// ��ͨҶ�ӽ��ֱ��ɾ�����ÿ����������
				father->left = nullptr;
			}
			delete cur;
		}
		// �����ֵܽ��ĺ�ɫ����֧���
		bool left_red = brother->left && !brother->left->blacked;
		bool right_red = brother->right && !brother->right->blacked;
		if (left_red && pos == 1) {
			bool father_bool = father->blacked;
			// L-L��֧,�����׽������,���ֵܽ��������ӽ��Ϊ��ɫ,�ֵܽ�����ɫ�븸���ԭ��ɫһ��
			root = father->rightRotate(root);
			brother->left->blacked = true;
			brother->right->blacked = true;
			brother->blacked = father_bool;
		}
		else if (right_red && pos == 2) {
			bool father_bool = father->blacked;
			// R-R��֧,�����׽������,���ֵܽ��������ӽ��Ϊ��ɫ,�ֵܽ�����ɫ�븸���ԭ��ɫһ��
			root = father->leftRotate(root);
			brother->left->blacked = true;
			brother->right->blacked = true;
			brother->blacked = father_bool;
		}
		else if (left_red && pos == 2) {
			bool father_bool = father->blacked;
			// R-L��֧,���ֵܽ����������γ�R-R�ṹ
			RBNode* cousin = brother->left;
			root = brother->rightRotate(root);
			// R-R�ṹͬ�϶Ը��׽�������������ɫ
			root = father->leftRotate(root);
			cousin->left->blacked = true;
			cousin->right->blacked = true;
			cousin->blacked = father_bool;
		}
		else if (right_red && pos == 1) {
			bool father_bool = father->blacked;
			// L-R��֧,���ֵܽ����������γ�L-L�ṹ
			RBNode* cousin = brother->right;
			root = brother->leftRotate(root);
			// L-L�ṹͬ�϶Ը��׽�������������ɫ
			root = father->rightRotate(root);
			cousin->left->blacked = true;
			cousin->right->blacked = true;
			cousin->blacked = father_bool;
		}
		else {
			// �ֵܽ��û�к��ӽ��ɹ�����
			if (!father->blacked) {
				// �����Ϊ��ɫ���,��������Ϊ��ɫ,�ֵܽ���Ϊ��ɫ����
				father->blacked = true;
				brother->blacked = false;
			}
			else {
				// �����Ϊ��ɫ���,�޷��������ƽ��,ֻ�ܽ�����������
				// ���ֵܽ��Ⱦ�ɺ�ɫ
				brother->blacked = false;
				if (!father->father) {
					// �����Ϊ�����,˵���Ѿ����һ�������
					return;
				}
				else {
					// ������һ���յ����,�����ݼ�������
					RBNode* blank = new RBNode(0, true, father->father);
					// ���յ�����������
					int pos_f = 0;
					if (father->father->value > father->value) {
						pos_f = 2;
						blank->left = father;
						father->father->left = blank;
						blank->father = father->father;
						father->father = blank;
					}
					else if (father->father->value < father->value) {
						pos_f = 1;
						blank->right = father;
						father->father->right = blank;
						blank->father = father->father;
						father->father = blank;
					}
					// ͨ���ݹ����ɾ������
					balanceDelete(blank, blank->father, pos_f);
				}
			}
		}
	}
}
	
// ����������չʾ
void RBTree::show() {
	if (!root->blacked) {
		// �����Ϊ��
		cout << "Empty!" << endl;
		return;
	}
	dfs_node(root, 0);
}

// ������������ǰ���ĺ���
void RBTree::dfs_node(RBNode* cur, int depth) {
	if (!cur) {
		return;
	}
	// ���ұ߽�����ȱ���
	dfs_node(cur->right, depth + 1);
	// ��ǰ�����Ϣ��ӡ
	for (int i = 0; i < depth; i++) {
		cout << "\t";
	}
	cout << cur->value;
	if (cur->blacked) cout << "(��)" << endl;
	else cout << "(��)" << endl;
	// ����������
	dfs_node(cur->left, depth + 1);
}