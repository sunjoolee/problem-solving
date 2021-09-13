#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

struct TrieNode {
	string food;
	vector<TrieNode*> children;

	void insert(const vector<string>& key, int index) {
		if (index == key.size()) return;

		else {
			string nextFood = key[index];

			for (int i = 0; i < children.size(); ++i) {
				if (children[i]->food == nextFood) {
					children[i]->insert(key, index + 1);
					return;
				}
			}

			TrieNode* t = new TrieNode();
			t->food = nextFood;
			this->children.push_back(t);

			t->insert(key, index + 1);
			return;
		}
	}

};

bool cmp(TrieNode* t1, TrieNode* t2) {
	if (t1->food < t2->food) return true;
	else return false;
}

void dfs(TrieNode* root, int dep) {

	if (dep > 0) {
		for (int i = 1; i < dep; ++i) {
			cout << "--";
		}
		cout << root->food << "\n";
	}
	
	sort(root->children.begin(), root->children.end(), cmp);

	for (int i = 0; i < root->children.size(); ++i) {
		TrieNode* child = root->children[i];
		dfs(child, dep+1);
	}
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N;
	cin >> N;

	TrieNode* root = new TrieNode();
	root->food = "";

	for (int i = 0; i < N; ++i) {
		int K;
		cin >> K;

		vector<string> inputFood;
		for (int j = 0; j < K; ++j) {
			string input;
			cin >> input;
			inputFood.push_back(input);
		}
		root->insert(inputFood, 0);
	}

	dfs(root, 0);

	return 0;
}