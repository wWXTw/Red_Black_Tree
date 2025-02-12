#include <iostream>
using namespace std;

// �����������
class RBNode {
private:
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
public:
	// ���캯��
	RBNode(int v = 0, bool b = false, RBNode* f = nullptr, RBNode* l = nullptr, RBNode* r = nullptr) {
		value = v;
		blacked = b;
		father = f;
		left = l;
		right = r;
	}
	// ��������
	RBNode* leftRotate(RBNode* cur,RBNode* root) {
		// �����ǰ�����ߵ�ǰ�����ҽ��Ϊ�����޷���������
		if (cur == nullptr || cur->right == nullptr) return root;

		RBNode* curFather, * curRight, * rightLeft;
		bool isLeft;
		// ��ǰ���ĸ����
		curFather = cur->father;
		// ��ǰ�����ҷ�֧
		curRight = cur->right;
		// �ҷ�֧�������֧
		rightLeft = curRight->left;
		// ȷ����ǰ����Ǹ��������֧�����ҷ�֧
		isLeft = curFather && curFather->left == cur;

		// �ҷ�֧�������֧��������Ϊ��,��������Ϊ��ǰ�����ҷ�֧
		if (rightLeft != nullptr) {
			cur->right = rightLeft;
			rightLeft->father = cur;
		}
		else {
			cur->right = nullptr;
		}

		// ���ҽ���ƶ�����ǰ����λ��
		cur->father = curRight;
		curRight->left = cur;
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
	RBNode* rightRotate(RBNode* cur, RBNode* root) {
		// �����ǰ�����ߵ�ǰ�������֧Ϊ�����޷�����
		if (cur == nullptr || cur->left == nullptr) return root;

		RBNode* curFather, * curLeft, * leftRight;
		bool isLeft;
		// ��ǰ���ĸ����
		curFather = cur->father;
		// ��ǰ�������֧
		curLeft = cur->right;
		// ���֧�����ҷ�֧
		leftRight = curLeft->left;
		// ȷ����ǰ����Ǹ��������֧�����ҷ�֧
		isLeft = curFather && curFather->left == cur;

		// ���֧�����ҷ�֧�����Ϊ�գ���������Ϊ��ǰ�������֧
		if (leftRight != nullptr) {
			cur->left = leftRight;
			leftRight->father = cur;
		}
		else {
			cur->left = nullptr;
		}

		// �������ƶ�����ǰ����λ��
		cur->father = curLeft;
		curLeft->right = cur;
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
	void addNode(int value) {

	}
	// ɾ�����
	void deleteNode(int value) {

	}
};