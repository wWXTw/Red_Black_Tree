#include "RBTree.h"

// �û�ʹ�õĽ�������
int main() {
	int value = 0;
	int op = 0;
	int res = 0;
	RBTree rbt;
	RBTree new_rbt;
	while (true) {
		cout << "1.������в�����" << endl;
		cout << "2.�������ɾ�����" << endl;
		cout << "3.��պ����" << endl;
		cout << "4.�˳�" << endl;
		cin >> op;
		switch (op)
		{
		case 1:
			cout << "�����Ҫ�����ֵ" << endl;
			cin >> value;
			res = rbt.addNode(value);
			if (res == 1) rbt.show();
			else if (res == -1) cout << "����ʧ��!" << endl;
			break;
		case 2:
			cout << "�����Ҫɾ����ֵ" << endl;
			cin >> value;
			res = rbt.deleteNode(value);
			if (res == 1) rbt.show();
			else if (res == -1) cout << "ɾ��ʧ��!" << endl;
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