#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

bool compare(string a, string b) {
	//길이 짧은 순으로 정렬
	if (a.size() < b.size()) return true;
	//길이 같다면 사전 순으로 정렬
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
		//중복된 단어 제외 출력
		while (i < n) {
			if (words[i] == words[i + 1]) ++i;
			else break;
		}
	}

	return 0;
}