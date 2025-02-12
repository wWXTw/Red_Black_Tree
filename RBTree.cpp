#include <iostream>
using namespace std;

// 红黑树结点的类
class RBNode {
private:
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
public:
	// 构造函数
	RBNode(int v = 0, bool b = false, RBNode* f = nullptr, RBNode* l = nullptr, RBNode* r = nullptr) {
		value = v;
		blacked = b;
		father = f;
		left = l;
		right = r;
	}
	// 左旋函数
	RBNode* leftRotate(RBNode* cur,RBNode* root) {
		// 如果当前结点或者当前结点的右结点为空则无法进行左旋
		if (cur == nullptr || cur->right == nullptr) return root;

		RBNode* curFather, * curRight, * rightLeft;
		bool isLeft;
		// 当前结点的父结点
		curFather = cur->father;
		// 当前结点的右分支
		curRight = cur->right;
		// 右分支结点的左分支
		rightLeft = curRight->left;
		// 确定当前结点是父结点的左分支还是右分支
		isLeft = curFather && curFather->left == cur;

		// 右分支结点的左分支结点如果不为空,左旋后会成为当前结点的右分支
		if (rightLeft != nullptr) {
			cur->right = rightLeft;
			rightLeft->father = cur;
		}
		else {
			cur->right = nullptr;
		}

		// 将右结点移动至当前结点的位置
		cur->father = curRight;
		curRight->left = cur;
		curRight->father = curFather;
		if (curFather == nullptr) {
			// 说明当前左旋结点是根节点
			return curRight;
		}
		else {
			// 说明当前左旋结点不是根节点
			if (isLeft) {
				curFather->left = curRight;
			}
			else {
				curFather->right = curRight;
			}
		}
		return root;
	}
	// 右旋函数
	RBNode* rightRotate(RBNode* cur, RBNode* root) {
		// 如果当前结点或者当前结点的左分支为空则无法右旋
		if (cur == nullptr || cur->left == nullptr) return root;

		RBNode* curFather, * curLeft, * leftRight;
		bool isLeft;
		// 当前结点的父结点
		curFather = cur->father;
		// 当前结点的左分支
		curLeft = cur->right;
		// 左分支结点的右分支
		leftRight = curLeft->left;
		// 确定当前结点是父结点的左分支还是右分支
		isLeft = curFather && curFather->left == cur;

		// 左分支结点的右分支如果不为空，右旋后会成为当前结点的左分支
		if (leftRight != nullptr) {
			cur->left = leftRight;
			leftRight->father = cur;
		}
		else {
			cur->left = nullptr;
		}

		// 将左结点移动至当前结点的位置
		cur->father = curLeft;
		curLeft->right = cur;
		curLeft->father = curFather;
		if (curFather == nullptr) {
			// 说明当前右旋的结点是根节点
			return curLeft;
		}
		else {
			// 说明当前右旋的结点不是根节点
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

// 红黑树的类
class RBTree {
private:
	// 红黑树的根节点
	RBNode* root;
public:
	// 构造函数
	RBTree() {
		root = new RBNode;
	}
	// 添加结点
	void addNode(int value) {

	}
	// 删除结点
	void deleteNode(int value) {

	}
};