#include <iostream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int A, B;
	cin >> A >> B;

	int L = 0;
	int R = 0;

	//���������� ��Ʈ�� �Ž��� �ö󰣴�
	while (A > 1 && B > 1) {
		if (A > B) {
			A = A - B;
			L++;
		}
		else {
			B = B - A;
			R++;
		}
	}

	//A�� 1�� �� ��� R�� ���� (1,1)���� �� �ö󰣴�
	if (A == 1)
		R += (B - 1);

	//B�� 1�� �� ��� L�� ���� (1,1)���� �� �ö󰣴�
	else if (B == 1)
		L += (A - 1);

	cout << L <<" "<<R;
	return 0;
}