#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// C++ implementation of search and insert
// operations on Trie

const int NUMBER_SIZE = 10; //0 ~ 9

// trie node
struct TrieNode{
	struct TrieNode *children[NUMBER_SIZE];

	// isEndOfWord is true if the node represents
	// end of a word
	bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void){
	struct TrieNode *pNode = new TrieNode;

	pNode->isEndOfWord = false;

	for (int i = 0; i < NUMBER_SIZE; i++)
		pNode->children[i] = NULL;

	return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode *root, string key){
	struct TrieNode *pCrawl = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - '0';
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	// mark last node as leaf
	pCrawl->isEndOfWord = true;
}

//트리에 key가 존재하는 경우 1
//트리에 key가 다른 단어의 접두사로 존재하는 경우 0
//트리에 key가 존재하지 않는 경우 -1
int search(struct TrieNode *root, string key){
	struct TrieNode *pCrawl = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - '0';
		if (!pCrawl->children[index])
			return -1;

		pCrawl = pCrawl->children[index];
	}

	return (pCrawl->isEndOfWord);
}

bool cmp(string a, string b) {
	return a.length() > b.length();
}

// Driver
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;

		vector<string> keys;
		for (int i = 0; i < n; ++i) {
			string input;
			cin >> input;
			keys.push_back(input);
		}
		//keys: string 길이 내림차순으로 정렬
		sort(keys.begin(), keys.end(), cmp);

		struct TrieNode *root = getNode();

		// Construct trie
		bool flag = true;
		for (int i = 0; i < n; i++) {
			if (search(root, keys[i]) != -1) {
				cout << "NO\n";
				flag = false;
				break;
			}
			insert(root, keys[i]);
		}
		if (flag) cout << "YES\n";
	}
	return 0;
}