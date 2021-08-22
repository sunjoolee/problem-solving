#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
set<string> name;
vector<string> ans;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;

	//�赵 ���� ��� ��� set ����
	for (int i = 0; i < n; ++i) {
		string input;
		cin >> input;
		name.insert(input);
	}

	//���� ���� ��� ��� set ����
	for (int i = 0; i < m; ++i) {
		string input; 
		cin >> input;
			
		//�ߺ��� ���ڿ��� ��� set ���� ���� = �赵 ���� ���� ���
		auto it = name.insert(input);
		if (!it.second) ans.push_back(input);
	}

	//�赵 ���� ���� ��� ��� ������ ����
	sort(ans.begin(), ans.end());

	cout << ans.size() << "\n";
	for (int i = 0; i < ans.size(); ++i)
		cout << ans[i] << "\n";

	return 0;
}