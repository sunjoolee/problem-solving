#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int height;
	cin >> height;

	int numofnodes = pow(2, height + 1) - 1;

	string path;
	cin >> path;

	//��ΰ� �־����� ���� ���
	if (cin.eof()) {
		//��Ʈ�� ��� ��ȣ ��� �� ����
		cout << numofnodes;
		return 0;
	}

	
	int i = 1;
	for (int j = 0; j < path.size(); ++j) {
		//LeftChild�� �̵�
		if (path[j] == 'L') 
			i = 2 * i;
		//RightChild�� �̵�
		else if (path[j] == 'R') 
			i = 2 * i + 1;
	}

	//����� ���� ������ ��� ��ȣ ���
	cout << numofnodes - i + 1;

	return 0;
}