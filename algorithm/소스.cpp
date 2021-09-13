#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

//주어지는 문자열은 0 ~ 9 숫자로 이루어짐 
const int ALPHABETS = 10;
int toNumber(char ch) { return ch - '0'; }

struct TrieNode {
	TrieNode* children[ALPHABETS];
	int terminal;

	TrieNode() : terminal(false) {
		memset(children, 0, sizeof(children));
	}
	~TrieNode(){
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

	int T;
	cin >> T;
	while(T--){
		int N;
		cin >> N;

		vector<string> inputs;
		TrieNode* root = new TrieNode();

		for (int i = 0; i < N; ++i) {
			string input;
			cin >> input;
			
			inputs.push_back(input);
			root->insert(input.c_str());
		}

		bool flag = true;
		for (int i = 0; i < N; ++i) {
			TrieNode* ret = root->find(inputs[i].c_str());
			
			if (ret != NULL) {
				for (int next = 0; next < 10; next++) {
					if (ret->children[next]) {
						flag = false;
						break;
					}
				}
				if (!flag) break;
			}
		}

		if (flag)cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}