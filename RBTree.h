#pragma once
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
	RBNode(int v = 0, bool b = false, RBNode* f = nullptr, RBNode* l = nullptr, RBNode* r = nullptr);
	// ��������
	RBNode* leftRotate(RBNode* root);
	// ��������
	RBNode* rightRotate(RBNode* root);
};

// ���������
class RBTree {
private:
	// ������ĸ��ڵ�
	RBNode* root;
public:
	// ���캯��
	RBTree();
	// ��ӽ��
	int addNode(int value);
	// ɾ�����
	int deleteNode(int value);
	// ƽ�ⷽ��������
	void balanceInsert(RBNode* cur, RBNode* father, int pos);
	// ƽ�ⷽ��ɾ�����
	void balanceDelete(RBNode* cur, RBNode* father, int pos);
	// չʾ�����
	void show();
	// �������������ʾ�ĺ���
	void dfs_node(RBNode* cur, int depth);
};