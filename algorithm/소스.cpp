#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;

int N;
//<���� �������, ���� �Ŷ��>
vector<pair<int, int>> hw;

//�� ���� �� �ִ� �Ŷ���� ��
ull cnt = 0;
priority_queue<int> maxheap;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; ++i) {
		int a, b;
		cin >> a >> b;
		hw.push_back(make_pair(a, b));
	}

	sort(hw.begin(), hw.end());

	//deadline N���� 0���� 1�� ���ҽ�Ű�� ���� ����
	for (int deadline = N; deadline > 0; --deadline) {

		//hw ������� ������������ ���ĵ� -> ���������� ��ȸ
		for (int i = hw.size()-1; i >= 0; --i) {
			//��������� deadline�� hw�� �Ŷ�� �� maxheap�� �߰�
			if (hw[i].first == deadline) {
				maxheap.push(hw[i].second);
				hw.pop_back();
			}
			else break;
		}

		if (!maxheap.empty()) {
			cnt += maxheap.top();
			maxheap.pop();
		}
		
	}
	
	cout << cnt;
	return 0;
}