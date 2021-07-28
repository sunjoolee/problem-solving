#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	vector<string> coin;

	for (int i = 0; i < n; ++i) {
		string input;
		cin >> input;
		coin.push_back(input);
	}
	
	int minT = 401;

	//��� �࿡ ���ؼ� �������� ���� ����
	for (ull k = 0; k < (1 << n); ++k) {
		//��ü ���� �޸��� ����;
		int totalT = 0;

		for (int j = 0; j < n; ++j) {

			//���� ������ ���� �޸��� ����
			int colT = 0;
			for (int i = 0; i < n; ++i) {
				char now;

				//i�� ° ���� ������� ������ ���
				if ((1 << i) & k) {
					if (coin[i][j] == 'T') now = 'H';
					if (coin[i][j] == 'H') now = 'T';
				}
				else now = coin[i][j];

				if (now == 'T') ++colT;
			}
			
			//���� ������ ���� ������ �ʴ� ��� �� ���� �޸��� ���� ���� ����� ��츦 ����
			totalT += min(n - colT, colT);
		}

		minT = min(minT, totalT);
	}

	cout << minT;
	return 0;
}