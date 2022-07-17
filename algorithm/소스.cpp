#include <queue>
#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n;
	cin >> n;

	queue<int> router;

	while (true) {
		int input;
		cin >> input;
		if (input == -1) break;
		
		//패킷 처리
		if (input == 0) router.pop();

		//패킷 도착
		else if (router.size() < n) router.push(input);
	}
	
	if (router.empty()) cout << "empty";
	else {
		while (!router.empty()) {
			cout << router.front()<<" ";
			router.pop();
		}
	}
	return 0;
}