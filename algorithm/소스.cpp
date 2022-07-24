#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n;
	cin >> n;

	//row[i]: i��° ����� Ű
	vector<int> row; 
	
	//cntVec[x]: Ű�� x�� ����� ���ʿ� x���� Űī ū ����� ��� �ִ���
	vector<int> cntVec; 
	
	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		cntVec.push_back(input);
		//row �ʱ�ȭ
		row.push_back(i);
	}

	do {
		bool correctRow = true;
		for (int i = 0; i < n; ++i) {
			int cnt = 0;
			for (int left = 0; left < i; ++left) {
				if (row[left] > row[i]) cnt++;
			}
			if (cntVec[row[i]] != cnt) {
				correctRow = false;
				break;
			}
		}
		if (correctRow) break;
	} while (next_permutation(row.begin(), row.end()));

	for (int i = 0; i < n; ++i) {
		cout << row[i] + 1<< " ";
	}

	return 0;
}