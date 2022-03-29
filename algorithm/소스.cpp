#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// C++ implementation of search and insert
// operations on Trie

const int ALPHABET_SIZE = 26;

// trie node
struct TrieNode {
	struct TrieNode *children[ALPHABET_SIZE];

	// isEndOfWord is true if the node represents
	// end of a word
	bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void) {
	struct TrieNode *pNode = new TrieNode;

	pNode->isEndOfWord = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;

	return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode *root, string key) {
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


int search(struct TrieNode *root, string key) {
	
	int cnt = 0;
	if (key[0] == '?') {
		for (int i = 0; i < ALPHABET_SIZE; ++i) {
			if (root->children[i]) {
				if (key.length() == 1) cnt += root->children[i]->isEndOfWord;
				else cnt += search(root->children[i], key.substr(1));
			}
		}
		if (key.length() == 1) return cnt;
	}
	else {
		int i = key[0] - 'a';
		if (root->children[i]) {
			if (key.length() == 1) return root->children[i]->isEndOfWord;
			cnt += search(root->children[i], key.substr(1));
		}
	}
	return cnt;
}

vector<int> solution(vector<string> words, vector<string> queries) {
	
	struct TrieNode *root = getNode();

	// Construct trie
	for (int i = 0; i < words.size(); i++) {
		insert(root, words[i]);
	}
	
	vector<int> answer;

	// Search
	for (int i = 0; i < queries.size(); ++i) {
		answer.push_back(search(root, queries[i]));
	}

	return answer;
}

int main() {
	solution({ "frodo", "front", "frost", "frozen", "frame", "kakao" }, { "fro??", "????o", "fr???", "fro???", "pro?" });
}



