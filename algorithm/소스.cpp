#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// C++ implementation of search and insert
// operations on Trie

const int ALPHABET_SIZE = 26; 

// trie node
struct TrieNode{
	struct TrieNode *children[ALPHABET_SIZE];

	// isEndOfWord is true if the node represents
	// end of a word
	bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void){
	struct TrieNode *pNode = new TrieNode;

	pNode->isEndOfWord = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
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
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	// mark last node as leaf
	pCrawl->isEndOfWord = true;
}


bool search(struct TrieNode *root, string key){
	struct TrieNode *pCrawl = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			return false;

		pCrawl = pCrawl->children[index];
	}

	return pCrawl->isEndOfWord;
}

bool cmp(string a, string b) {
	return a.length() > b.length();
}

// Driver
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n, m;
	cin >> n >> m;

	struct TrieNode *root = getNode();

	for (int i = 0; i < n; ++i) {
		string input;
		cin >> input;

		insert(root, input);
	}

	int cnt = 0;
	for (int i = 0; i < m; ++i) {
		string input;
		cin >> input;

		if (search(root, input)) ++cnt;
	}

	cout << cnt;

	return 0;
}