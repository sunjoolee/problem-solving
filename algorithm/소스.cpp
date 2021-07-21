#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

bool compare(string a, string b) {
	//���� ª�� ������ ����
	if (a.size() < b.size()) return true;
	//���� ���ٸ� ���� ������ ����
	else if (a.size() == b.size())
		return a < b;
	else return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string words[20001];
	
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> words[i];

	sort(words, words + n, compare);

	for (int i = 0; i < n; ++i) {
		cout << words[i]<<"\n";
		//�ߺ��� �ܾ� ���� ���
		while (i < n) {
			if (words[i] == words[i + 1]) ++i;
			else break;
		}
	}

	return 0;
}