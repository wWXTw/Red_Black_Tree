#pragma once
#include <iostream>
using namespace std;

// 红黑树结点的类
class RBNode {
public:
	// 结点值(以int类型为例)
	int value;
	// 确认结点是否为黑色的布尔值
	bool blacked;
	// 结点的左子树
	RBNode* left;
	// 结点的右子树
	RBNode* right;
	// 结点的父结点
	RBNode* father;
	// 构造函数
	RBNode(int v = 0, bool b = false, RBNode* f = nullptr, RBNode* l = nullptr, RBNode* r = nullptr);
	// 左旋函数
	RBNode* leftRotate(RBNode* root);
	// 右旋函数
	RBNode* rightRotate(RBNode* root);
};

// 红黑树的类
class RBTree {
private:
	// 红黑树的根节点
	RBNode* root;
public:
	// 构造函数
	RBTree();
	// 添加结点
	int addNode(int value);
	// 删除结点
	int deleteNode(int value);
	// 平衡方法插入结点
	void balanceInsert(RBNode* cur, RBNode* father, int pos);
	// 平衡方法删除结点
	void balanceDelete(RBNode* cur, RBNode* father, int pos);
	// 展示红黑树
	void show();
	// 遍历结点用于显示的函数
	void dfs_node(RBNode* cur, int depth);
};