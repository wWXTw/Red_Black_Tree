#include <iostream>
using namespace std;

// �����������
class RBNode {
public:
	// ���ֵ(��int����Ϊ��)
	int value;
	// ȷ�Ͻ���Ƿ�Ϊ��ɫ�Ĳ���ֵ
	bool blacked;
	// ����������
	RBNode* left;
	// ����������
	RBNode* right;
	// ���ĸ����
	RBNode* father;
	// ���캯��
	RBNode(int v = 0, bool b = false, RBNode* f = nullptr, RBNode* l = nullptr, RBNode* r = nullptr) {
		value = v;
		blacked = b;
		father = f;
		left = l;
		right = r;
	}
	// ��������
	RBNode* leftRotate(RBNode* root) {
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
	// ��������
	RBNode* rightRotate(RBNode* root) {
		// �����ǰ�����ߵ�ǰ�������֧Ϊ�����޷�����
		if (this == nullptr || this->left == nullptr) return root;

		RBNode* curFather, * curLeft, * leftRight;
		bool isLeft;
		// ��ǰ���ĸ����
		curFather = this->father;
		// ��ǰ�������֧
		curLeft = this->right;
		// ���֧�����ҷ�֧
		leftRight = curLeft->left;
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
};

// ���������
class RBTree {
private:
	// ������ĸ��ڵ�
	RBNode* root;
public:
	// ���캯��
	RBTree() {
		root = new RBNode;
	}
	// ��ӽ��
	int addNode(int value) {
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
	// ɾ�����
	void deleteNode(int value) {

	}
	// ƽ�ⷽ��������
	void balanceInsert(RBNode* cur, RBNode* father, int pos) {
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
				balanceInsert(grand, grand->father,g_pos);
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
	// չʾ�����
	void show() {
		if (!root->blacked) {
			// �����Ϊ��
			cout << "Empty!" << endl;
			return;
		}
		dfs_node(root, 0);
	}
	// �������������ʾ�ĺ���
	void dfs_node(RBNode* cur,int depth) {
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
};

int main() {
	int value = 0;
	RBTree rbt;
	while (cin >> value) {
		rbt.addNode(value);
		rbt.show();
	}
}