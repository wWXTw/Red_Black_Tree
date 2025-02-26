#include "RBTree.h"

// 红黑树结点的构造函数
RBNode::RBNode(int v, bool b, RBNode* f, RBNode* l, RBNode* r)
	: value(v), blacked(b), father(f), left(l), right(r) {}

// 红黑树结点的左旋函数
RBNode* RBNode::leftRotate(RBNode* root) {
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

// 红黑树结点的右旋函数
RBNode* RBNode::rightRotate(RBNode* root) {
	// 如果当前结点或者当前结点的左分支为空则无法右旋
	if (this == nullptr || this->left == nullptr) return root;

	RBNode* curFather, * curLeft, * leftRight;
	bool isLeft;
	// 当前结点的父结点
	curFather = this->father;
	// 当前结点的左分支
	curLeft = this->left;
	// 左分支结点的右分支
	leftRight = curLeft->right;
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

// 红黑树类的构造函数
RBTree::RBTree() {
	root = new RBNode;
}

// 红黑树类的添加结点
int RBTree::addNode(int value) {
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

// 红黑树类的删除结点
int RBTree::deleteNode(int value) {
	RBNode* father = nullptr;
	int pos = 0;
	if (!root->blacked) {
		// 红黑树为空直接返回-1
		return -1;
	}
	else {
		RBNode* p = root;
		while (p) {
			if (p->value == value) {
				// 找到当前目标结点后,将其数值与前驱结点或者后继结点交换(如果有的话)
				if (p->left) {
					RBNode* pa = p->left;
					RBNode* pt = pa->right;
					pos = 2;
					// 寻找前驱结点
					while (pt) {
						pa = pt;
						pt = pt->right;
						pos = 1;
					}
					// 将目标结点与前驱结点的值交换并删除前驱结点
					p->value = pa->value;
					pa->value = value;
					balanceDelete(pa, pa->father, pos);
				}
				else if (p->right) {
					RBNode* pa = p->right;
					RBNode* pt = pa->left;
					pos = 1;
					// 寻找后继结点
					while (pt) {
						pa = pt;
						pt = pt->left;
						pos = 2;
					}
					// 当目标结点与后继结点的值交换并删除后继结点
					p->value = pa->value;
					pa->value = value;
					balanceDelete(pa, pa->father, pos);
				}
				else {
					// 目标结点为叶子结点,直接删除
					balanceDelete(p, p->father, pos);
				}
				return 1;
			}
			else if (p->value < value) {
				// 当前结点值小于目标,前往右子树
				father = p;
				p = p->right;
				pos = 1;
			}
			else {
				// 当前结点值小于目标,前往左子树
				father = p;
				p = p->left;
				pos = 2;
			}
		}
		// 没有这个结点,返回-1
		return -1;
	}
}

// 红黑树类的平衡方法插入结点
void RBTree::balanceInsert(RBNode* cur, RBNode* father, int pos) {
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
			balanceInsert(grand, grand->father, g_pos);
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
	
// 红黑树类的平衡方法删除结点
void RBTree::balanceDelete(RBNode * cur, RBNode * father, int pos) {
	if (father == nullptr) {
		// 为根结点,将颜色改为红色即可
		cur->blacked = false;
	}
	else if (!cur->blacked) {
		// 为红色叶子结点,直接删除即可
		if (pos == 1) {
			father->right = nullptr;
		}
		else {
			father->left = nullptr;
		}
		delete cur;
	}
	else if (cur->blacked) {
		// 为黑色叶子结点,需要查看兄弟结点的情况
		// 同时删除当前结点(考虑塌陷情况,将父结点与子结点连接起来)
		RBNode* brother = new RBNode;
		if (pos == 1) {
			brother = father->left;
			if (cur->right) {
				// 坍陷情况下当前塌陷结点与父结点的方向一定与坍陷结点与分支结点的方向一致
				// 坍陷结点是父结点的右子结点,那么它只可能在右子结点上有分支
				// 将父结点与右子结点连接起来,根据情况处理坍陷空当
				father->right = cur->right;
				cur->right->father = father;
			}
			else {
				// 普通叶子结点直接删除不用考虑连接情况
				father->right = nullptr;
			}
			delete cur;
		}
		else if (pos == 2) {
			brother = father->right;
			if (cur->left) {
				// 坍陷结点是父结点的左子结点,那么它只可能在左子结点上有分支
				// 将父结点与左子结点连接起来,根据情况处理坍陷空当
				father->left = cur->left;
				cur->left->father = father;
			}
			else {
				// 普通叶子结点直接删除不用考虑连接情况
				father->left = nullptr;
			}
			delete cur;
		}
		// 考察兄弟结点的红色结点分支情况
		bool left_red = brother->left && !brother->left->blacked;
		bool right_red = brother->right && !brother->right->blacked;
		if (left_red && pos == 1) {
			bool father_bool = father->blacked;
			// L-L分支,将父亲结点右旋,令兄弟结点的左右子结点为黑色,兄弟结点的颜色与父结点原颜色一致
			root = father->rightRotate(root);
			brother->left->blacked = true;
			brother->right->blacked = true;
			brother->blacked = father_bool;
		}
		else if (right_red && pos == 2) {
			bool father_bool = father->blacked;
			// R-R分支,将父亲结点左旋,令兄弟结点的左右子结点为黑色,兄弟结点的颜色与父结点原颜色一致
			root = father->leftRotate(root);
			brother->left->blacked = true;
			brother->right->blacked = true;
			brother->blacked = father_bool;
		}
		else if (left_red && pos == 2) {
			bool father_bool = father->blacked;
			// R-L分支,对兄弟结点进行右旋形成R-R结构
			RBNode* cousin = brother->left;
			root = brother->rightRotate(root);
			// R-R结构同上对父亲结点进行左旋并改色
			root = father->leftRotate(root);
			cousin->left->blacked = true;
			cousin->right->blacked = true;
			cousin->blacked = father_bool;
		}
		else if (right_red && pos == 1) {
			bool father_bool = father->blacked;
			// L-R分支,对兄弟结点进行左旋形成L-L结构
			RBNode* cousin = brother->right;
			root = brother->leftRotate(root);
			// L-L结构同上对父亲结点进行右旋并改色
			root = father->rightRotate(root);
			cousin->left->blacked = true;
			cousin->right->blacked = true;
			cousin->blacked = father_bool;
		}
		else {
			// 兄弟结点没有红子结点可供分配
			if (!father->blacked) {
				// 父结点为红色结点,将父结点改为黑色,兄弟结点改为红色即可
				father->blacked = true;
				brother->blacked = false;
			}
			else {
				// 父结点为黑色结点,无法保存层数平衡,只能进行向下塌陷
				// 将兄弟结点染成红色
				brother->blacked = false;
				if (!father->father) {
					// 父结点为根结点,说明已经完成一层的塌陷
					return;
				}
				else {
					// 否则建立一个空当结点,将塌陷继续传递
					RBNode* blank = new RBNode(0, true, father->father);
					// 将空当结点插入树中
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
					// 通过递归进行删除操作
					balanceDelete(blank, blank->father, pos_f);
				}
			}
		}
	}
}
	
// 红黑树类结点的展示
void RBTree::show() {
	if (!root->blacked) {
		// 红黑树为空
		cout << "Empty!" << endl;
		return;
	}
	dfs_node(root, 0);
}

// 红黑树类遍历当前结点的函数
void RBTree::dfs_node(RBNode* cur, int depth) {
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