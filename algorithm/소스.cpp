#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	int root;
	int parent[21] = { 0 };
	for (int i = 1; i <= n; ++i) {
		int p;
		cin >> p;
		parent[i] = p;

		if (p == -1) root = i;
	}

	for (int i = 1; i <= n; ++i) {
		int node = i;
		int height = 0;

		if (node == root) {
			cout << height << "\n";
			continue;
		}

		while (node != root) {
			node = parent[node];
			height++;
		}
		cout << height << "\n";
	}

	return 0;
}