#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

//주어지는 문자열은 알파벳 소문자로만 이루어짐
const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'a'; }

struct TrieNode {
	TrieNode* children[ALPHABETS];
	int terminal;

	TrieNode() : terminal(false) {
		memset(children, 0, sizeof(children));
	}
	~TrieNode() {
		for (int i = 0; i < ALPHABETS; ++i) {
			if (children[i]) delete children[i];
		}
	}

	void insert(const char* key) {
		if (*key == 0) terminal = true;
		else {
			int next = toNumber(*key);
			if (children[next] == NULL)
				children[next] = new TrieNode();

			children[next]->insert(key + 1);
		}
	}

	TrieNode* find(const char* key) {
		if (*key == 0) return this;

		int next = toNumber(*key);
		if (children[next] == NULL)
			return NULL;

		return children[next]->find(key + 1);
	}
};


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, M;
	cin >> N >> M;

	string input;
	TrieNode* root = new TrieNode();
	for (int i = 0; i < N; ++i) {
		cin >> input;
		root->insert(input.c_str());
	}

	int cnt = 0;
	for (int i = 0; i < M; ++i) {
		cin >> input;
		TrieNode* ret = root->find(input.c_str());

		if (ret != NULL && ret->terminal) ++cnt;
	}

	cout << cnt;
	return 0;
}