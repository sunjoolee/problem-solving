#include <iostream>
#include <map>
#include <utility>
using namespace std;

int n;
//<노드, <left child, right child>>
map<char, pair<char, char>> tree;

void preorder(char node) {
	if (node == '.') return;

	cout << node;
	preorder(tree[node].first);
	preorder(tree[node].second);
	return;
}

void inorder(char node) {
	if (node == '.') return;

	inorder(tree[node].first);
	cout << node;
	inorder(tree[node].second);
	return;
}

void postorder(char node) {
	if (node == '.') return;

	postorder(tree[node].first);
	postorder(tree[node].second);
	cout << node;
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; ++i) {
		char node, left, right;
		cin >> node >> left >> right;

		tree[node].first = left;
		tree[node].second = right;
	}

	//항상 A가 루트 노드
	preorder('A');
	cout << "\n";
	inorder('A');
	cout << "\n";
	postorder('A');

	return 0;
}