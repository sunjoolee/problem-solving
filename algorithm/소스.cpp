#include <iostream>
#include <deque>
#include <string>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	deque<int> q;

	int n;
	cin >> n;
	while (n--) {
		string input;
		cin >> input;

		if (input == "push_front") {
			int x;
			cin >> x;
			q.push_front(x);
		}
		else if (input == "push_back") {
			int x;
			cin >> x;
			q.push_back(x);
		}
		else if (input == "pop_front"){
			if (q.empty()) cout << -1<<"\n";
			else {
				cout << q.front() << "\n";
				q.pop_front();
			}
		}
		else if (input == "pop_back") {
			if (q.empty()) cout << -1 << "\n";
			else {
				cout << q.back() << "\n";
				q.pop_back();
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