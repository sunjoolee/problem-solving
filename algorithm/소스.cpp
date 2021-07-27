#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string input;
	cin >> input;

	vector<char> v;

	for (int i = 0; i < input.size(); ++i) {
		v.push_back(input[i]);
		if (v.size() >= 4) {
			auto it = v.rbegin();
			if (*it == 'P' && *(it + 1) == 'A' && *(it + 2) == 'P' && *(it + 3) == 'P') {
				//P 하나만 남기고 pop
				v.pop_back();
				v.pop_back();
				v.pop_back();
			}
		}
	}

	if (v.size() == 1 && v.back() == 'P') cout << "PPAP";
	else cout << "NP";

	return 0;
}