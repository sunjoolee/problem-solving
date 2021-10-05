#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

int n, m;
map<string, int> m1;
map<int, string> m2;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		string name;
		cin >> name;

		m1[name] = i + 1;
		m2[i + 1] = name;
	}

	for (int i = 0; i < m; ++i) {
		string input;
		cin >> input;

		//ù���� �빮�ڶ�� �̸�
		if (input[0] >= 65 && input[0] <= 90)
			cout << m1[input] << "\n";
		//�ƴ϶�� ����
		else {
			cout << m2[stoi(input)] << "\n";
		}
	}

	return 0;
}