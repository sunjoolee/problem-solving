#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	queue<int> q;

	int n;
	cin >> n;
	while (n--) {
		string input;
		cin >> input;

		if (input == "push") {
			int x;
			cin >> x;
			q.push(x);
		}
		else if (input == "pop"){
			if (q.empty()) cout << -1<<"\n";
			else {
				cout << q.front() << "\n";
				q.pop();
			}
		}
		else if (input == "size") {
			cout << q.size() << "\n";
		}
		else if (input == "empty") {
			cout << q.empty() << "\n";
		}
		else if (input == "front") {
			if (q.empty()) cout << -1 << "\n";
			else cout << q.front() << "\n";
		}
		else if (input == "back") {
			if (q.empty()) cout << -1 << "\n";
			else cout << q.back() << "\n";
		}
	}

	return 0;
}