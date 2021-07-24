#include <iostream>
#include <string>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string input;
	int flag = 0;

	while (true) {
		cin >> input;
		if (cin.eof()) break;

		int found;

		if (flag == 0) {
			found = input.find('U');
			if (found != -1) {
				input = input.substr(found, -1);
				++flag;
			}
		}
		if (flag == 1) {
			found = input.find('C');
			if (found != -1) {
				input = input.substr(found, -1);
				++flag;
			}
		}
		if (flag == 2) {
			found = input.find('P');
			if (found != -1) {
				input = input.substr(found, -1);
				++flag;
			}
		}
		if (flag == 3) {
			found = input.find('C');
			if (found != -1) {
				cout << "I love UCPC";
				return 0;
			}
		}
	}

	cout << "I hate UCPC";
	return 0;
}