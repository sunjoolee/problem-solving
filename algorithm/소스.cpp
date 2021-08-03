#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;
	string input;
	cin >> input;

	//���ݱ��� ���� ����� ��ȣ
	int appleNo = 0;
	//���ݱ��� ���� ����� �������� ������Ű�� ���� ����ϴ� ����
	stack<int> apple;

	//appleTree[i]: �������� i��° �ڸ��� �����Ǵ� ����� ��ȣ
	vector<int> appleTree;

	for (int i = 0; i < 2 * n; ++i) {
		if (input[i] == '0') {
			//���ο� ��� �湮 -> ���ÿ� ����
			apple.push(appleNo);
			appleTree.push_back(appleNo);

			appleNo++;
		}

		if (input[i] == '1') {
			//������ ������� ���� -> ���ÿ��� pop
			appleTree.push_back(apple.top());
			apple.pop();
		}
	}

	//applePair[i]: <��� i�� �湮�� ���� ������������ 0�� ��ġ,��� i���� ���ϵ� ���� ������������ 1�� ��ġ> 
	vector<pair<int, int>> applePair(n, make_pair(0,0));
	
	for (int i = 0; i < 2 * n; ++i) {
		int curapple = appleTree[i];
		//curapple ����� �湮�� ���� ������������ 0�� ��ġ
		if (input[i] == '0')
			applePair[curapple].first = i;
		//curapple ������� ������ ���� ������������ 1�� ��ġ
		if (input[i] == '1')
			applePair[curapple].second = i;
	}

	//���� ���
	int x, y;
	cin >> x >> y;
	
	//���� ����� ���������� ó������ ��Ÿ�� ��ġ 
	int badappleStart = min(applePair[appleTree[x-1]].first, applePair[appleTree[y-1]].first);
	//���� ����� ���������� ���������� ��Ÿ�� ��ġ
	int badappleEnd = max(applePair[appleTree[x-1]].second, applePair[appleTree[y-1]].second);

	int ansi = 0;
	int ansj = 2*n-1;

	for (int i = 0; i < n; ++i) {
		if ((applePair[i].first <= badappleStart) && (applePair[i].second >= badappleEnd)) {
			if (applePair[i].first >= ansi) {
				ansi = applePair[i].first;
				ansj = applePair[i].second;
			}
		}
	}

	cout << ansi+1 << " " << ansj+1;
	return 0;
}