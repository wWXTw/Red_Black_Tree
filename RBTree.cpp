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
	RBNode(int v = 0, bool b = false, RBNode* f = nullptr, RBNode* l = nullptr, RBNode* r = nullptr) {
		value = v;
		blacked = b;
		father = f;
		left = l;
		right = r;
	}
	// 左旋函数
	RBNode* leftRotate(RBNode* root) {
		// 如果当前结点或者当前结点的右结点为空则无法进行左旋
		if (this == nullptr || this->right == nullptr) return root;

		RBNode* curFather, * curRight, * rightLeft;
		bool isLeft;
		// 当前结点的父结点
		curFather = this->father;
		// 当前结点的右分支
		curRight = this->right;
		// 右分支结点的左分支
		rightLeft = curRight->left;
		// 确定当前结点是父结点的左分支还是右分支
		isLeft = curFather && curFather->left == this;

		// 右分支结点的左分支结点如果不为空,左旋后会成为当前结点的右分支
		if (rightLeft != nullptr) {
			this->right = rightLeft;
			rightLeft->father = this;
		}
		else {
			this->right = nullptr;
		}

		// 将右结点移动至当前结点的位置
		this->father = curRight;
		curRight->left = this;
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
	RBNode* rightRotate(RBNode* root) {
		// 如果当前结点或者当前结点的左分支为空则无法右旋
		if (this == nullptr || this->left == nullptr) return root;

		RBNode* curFather, * curLeft, * leftRight;
		bool isLeft;
		// 当前结点的父结点
		curFather = this->father;
		// 当前结点的左分支
		curLeft = this->right;
		// 左分支结点的右分支
		leftRight = curLeft->left;
		// 确定当前结点是父结点的左分支还是右分支
		isLeft = curFather && curFather->left == this;

		// 左分支结点的右分支如果不为空，右旋后会成为当前结点的左分支
		if (leftRight != nullptr) {
			this->left = leftRight;
			leftRight->father = this;
		}
		else {
			this->left = nullptr;
		}

		// 将左结点移动至当前结点的位置
		this->father = curLeft;
		curLeft->right = this;
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
	int addNode(int value) {
		if (!root->blacked) {
			// 如果当前根结点的颜色为红色则说明该红黑树没有结点,直接插入
			RBNode* cur = new RBNode(value);
			balanceInsert(cur, nullptr, 0);
		}
		else {
			// 在树中寻找合适的插入位置
			RBNode* p = root;
			RBNode* father = new RBNode;
			int pos = 0;
			while (p) {
				if (p->value == value) {
					// 结点值冲突,返回错误码
					return -1;
				}
				else if (p->value < value) {
					// 记录当前的结点作为记录的父结点
					father = p;
					p = p->right;
					// pos记录为1,即当前的p为father的右结点
					pos = 1;
				}
				else {
					// 记录当前的结点作为记录的父结点
					father = p;
					p = p->left;
					// pos记录为2,即当前的p为father的左结点
					pos = 2;
				}
			}
			// 运行到这里,p肯定为空,father中记录着这个空位置的父结点
			RBNode* cur = new RBNode(value, false, father);
			balanceInsert(cur, father, pos);
		}
		// 返回插入成功码
		return 1;
	}
	// 删除结点
	void deleteNode(int value) {

	}
	// 平衡方法插入结点
	void balanceInsert(RBNode* cur, RBNode* father, int pos) {
		if (cur->father == nullptr) {
			// 父结点为空说明向红黑树中插入了一个根结点,直接将根结点颜色变为黑色即可
			cur->blacked = true;
			// 更新结构的根节点
			root = cur;
		}
		else if (father->blacked) {
			// 父结点为黑结点则直接插入红色结点即可
			// 根据pos值确认子结点方向位置
			if (pos == 1) {
				father->right = cur;
			}
			else if (pos == 2) {
				father->left = cur;
			}
		}
		else {
			// 父结点为红结点
			RBNode* grand = father->father;
			// 根据pos值确认子结点方向位置
			if (pos == 1) {
				father->right = cur;
			}
			else if (pos == 2) {
				father->left = cur;
			}
			if (grand->left && grand->right) {
				// 祖父结点的左右两端都有红结点的情况
				// 采用上溢操作,将父结点与叔叔结点都变为黑色,将祖父结点变为红色结点,相当祖父结点上浮了一层
				grand->left->blacked = true;
				grand->right->blacked = true;
				grand->blacked = false;
				// 确认祖父结点对于其父结点来说是左结点还是右结点
				int g_pos;
				if (!grand->father) {
					// 祖父结点没有父结点
					g_pos = 0;
				}
				else if (grand->father->value > grand->value) {
					// 组父结点为左结点
					g_pos = 2;
				}
				else {
					// 组父结点为右结点
					g_pos = 1;
				}
				// 祖父结点对上面一层来说相当于插入一个新的红结点,采取递归操作
				balanceInsert(grand, grand->father,g_pos);
			}
			else {
				// 祖父结点只有一段有红结点的情况
				int f_pos;
				// 判断父结点相对于祖父结点的位置
				if (grand->value > father->value) {
					// 父结点为祖父结点的左结点
					f_pos = 2;
				}
				else {
					// 父结点为祖父结点的右结点
					f_pos = 1;
				}
				// 根据pos与f_pos采取左旋右旋操作
				if (pos == 2 && f_pos == 2) {
					// L-L结构
					// 父-祖父结点交换颜色后对祖父结点右旋
					father->blacked = true;
					grand->blacked = false;
					root = grand->rightRotate(root);
				}
				else if (pos == 1 && f_pos == 1) {
					// R-R结构
					// 父-祖父结点交换颜色后对祖父结点左旋
					father->blacked = true;
					grand->blacked = false;
					root = grand->leftRotate(root);
				}
				else if (pos == 2 && f_pos == 1) {
					// R-L结构
					// 先对父结点进行右旋
					root = father->rightRotate(root);
					// 当前结点与祖父结点交换颜色后对祖父结点左旋
					cur->blacked = true;
					grand->blacked = false;
					root = grand->leftRotate(root);
				}
				else if (pos == 1 && f_pos == 2) {
					// L-R结构
					// 先对父结点进行左旋
					root = father->leftRotate(root);
					// 当前结点与祖父结点交换颜色后对祖父结点右旋
					cur->blacked = true;
					grand->blacked = false;
					root = grand->rightRotate(root);
				}
			}
		}
	}
	// 展示红黑树
	void show() {
		if (!root->blacked) {
			// 红黑树为空
			cout << "Empty!" << endl;
			return;
		}
		dfs_node(root, 0);
	}
	// 遍历结点用于显示的函数
	void dfs_node(RBNode* cur,int depth) {
		if (!cur) {
			return;
		}
		// 对右边结点优先遍历
		dfs_node(cur->right, depth + 1);
		// 当前结点信息打印
		for (int i = 0; i < depth; i++) {
			cout << "\t";
		}
		cout << cur->value;
		if (cur->blacked) cout << "(黑)" << endl;
		else cout << "(红)" << endl;
		// 最后遍历左结点
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