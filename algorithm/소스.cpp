#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
	//ȸ�� ������ �ð� ���� ������ ����
	if(a.second < b.second) return true;
	//ȸ�� ������ �ð� ���� ���
	//ȸ�� �����ϴ� �ð� ���� ������ ����
	if (a.second == b.second) return a.first < b.first;

	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n;
	cin >> n;

	vector<pair<int, int>> meeting;
	for (int i = 0; i < n; ++i) {
		int start, end;
		cin >> start >> end;
		meeting.push_back({ start, end });
	}
	sort(meeting.begin(), meeting.end(), cmp);

	int cnt = 0;
	int meetingEnd = 0;
	for (int i = 0; i < n; ++i) {
		if (meetingEnd <= meeting[i].first) {
			cnt++;
			meetingEnd = meeting[i].second;
		}
	}
	cout << cnt;
	return 0;
}