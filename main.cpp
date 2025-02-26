#include "RBTree.h"

// 用户使用的交互函数
int main() {
	int value = 0;
	int op = 0;
	int res = 0;
	RBTree rbt;
	RBTree new_rbt;
	while (true) {
		cout << "1.红黑树中插入结点" << endl;
		cout << "2.红黑树中删除结点" << endl;
		cout << "3.清空红黑树" << endl;
		cout << "4.退出" << endl;
		cin >> op;
		switch (op)
		{
		case 1:
			cout << "请输出要插入的值" << endl;
			cin >> value;
			res = rbt.addNode(value);
			if (res == 1) rbt.show();
			else if (res == -1) cout << "插入失败!" << endl;
			break;
		case 2:
			cout << "请输出要删除的值" << endl;
			cin >> value;
			res = rbt.deleteNode(value);
			if (res == 1) rbt.show();
			else if (res == -1) cout << "删除失败!" << endl;
			break;
		case 3:
			rbt = new_rbt;
			break;
		case 4:
			return 1;
		default:
			break;
		}
	}
}