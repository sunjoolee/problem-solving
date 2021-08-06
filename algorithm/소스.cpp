#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//허프만 코드 사전순으로 정렬
bool compare(pair<char, string>& a, pair<char, string>& b) {
	return a.second < b.second;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	vector<pair<char, string>> huffman;
	for (int i = 0; i < n; ++i) {
		char a;
		string code;
		cin >> a >> code;

		huffman.push_back(make_pair(a, code));
	}

	//허프만 코드 정렬
	sort(huffman.begin(), huffman.end(), compare);

	string input;
	cin >> input;
	int index = 0;

	while (index < input.size()) {
		for (int i = 0; i < huffman.size(); ++i) {
			char alpha = huffman[i].first;
			string code = huffman[i].second;

			if (input.substr(index, code.size()) == code) {
				cout << alpha;
				index += code.size();
				break;
			}
		}
	}

	return 0;
}