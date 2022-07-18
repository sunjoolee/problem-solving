#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <iostream>
using namespace std;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n; //���������� ��
	int m; //���� ��
	vector<int> R; //�������� �� ���� ���
	vector<int> W; //���� ����


	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		int r;
		cin >> r;
		R.push_back(r);
	}
	for (int i = 0; i < m; ++i) {
		int w;
		cin >> w;
		W.push_back(w);
	}


	//������ �� ť
	queue<int> q;

	//parkinglot[n]: n�� �������� ��������� 0, �������� 1
	vector<int> parkinglot(n, 0);

	//carParked[m]: m�� ���� �����Ǿ��ִ� �������� ��ȣ
	map<int, int> carParked;

	int pay = 0;
	for (int i = 0; i < (2 * m); ++i) {
		int car;
		cin >> car;

		//���� ������ ���
		if (car > 0) {
			car--;
			
			bool parked = false;
			//�� �������� ã�Ƽ� ����
			for (int p = 0; p < n; ++p) {
				if (parkinglot[p] == 0) {
					carParked[car] = p;
					parkinglot[p] = 1;
					parked = true;
					break;
				}
			}

			//�� �������� ���� ��� ť���� ���
			if(!parked) q.push(car);
		}

		//���� ������ ���
		else {
			car = car * (-1);
			car--;

			//������� ���
			int p = carParked[car];
			pay += (R[p] * W[car]);

			//�����忡�� ����
			carParked.erase(car);
			parkinglot[p] = 0;

			//ť�� ��� ���� �� �ִ� ���
			if (!q.empty()) {

				//�� �������� �ִٸ� ã�Ƽ� ����
				for (int p = 0; p < n; ++p) {
					if (parkinglot[p] == 0) {
						carParked[q.front()] = p;
						parkinglot[p] = 1;
						q.pop();
						break;
					}
				}
			}
		}
	}

	cout << pay;
	return 0;
}