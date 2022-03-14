#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory.h>
#include <algorithm>
using namespace std;

/*
struct Trie {
	bool finish; // ������ ������ ǥ������ 
	Trie* next[26]; // 26���� ���ĺ��� ���� Ʈ���� 
					
	// ������ 
	Trie() : finish(false) { 
		memset(next, 0, sizeof(next)); 
	} 

	// �Ҹ��� 
	~Trie() { 
		for (int i = 0; i < 26; i++) 
			if (next[i]) delete next[i]; 
	} 
	
	// Ʈ���̿� ���ڿ� ���� 
	void insert(const char* key) {

		// ���ڿ��� ������ ������ ��� ǥ�� 
		if (*key == '\0') finish = true; 

		else {
			int curr = *key - 'A';
			if (next[curr] == NULL) {
				// Ž���� ó���Ǵ� ������ ��� �����Ҵ� 
				next[curr] = new Trie();
			}
			// ���� ���� ���� 
			next[curr]->insert(key + 1); 
		} 
	}
	
	// Ʈ���̿��� ���ڿ� ã�� 
	Trie* find(const char* key) { 

		// ���ڿ��� ������ ��ġ�� ��ȯ 
		if (*key == '\0') return this;

		int curr = *key - 'A'; 
		
		// ã�� ���� �������� ���� 
		if (next[curr] == NULL) return NULL; 

		// ���� ���ڸ� Ž��
		return next[curr]->find(key + 1); 
		
	} 
};

*/

struct TrieNode {
	bool isEnd;
	map<char, TrieNode*> children;

	TrieNode() : isEnd(false) {}
};

//Trie �ڷᱸ���� �ܾ� �߰�
void recursiveAdd(TrieNode* curNode, string word) {
	if (word.length() == 0) {
		curNode->isEnd = true;
	}
	else {
		int ch = word[0] - 'a';
		if (curNode->children.find(ch) == curNode->children.end()) {
			curNode->children[ch] = &TrieNode();
		}
		recursiveAdd(curNode->children[ch], word.substr(1));
	}
}

void add(TrieNode* root, string word) {
	if (word.length() == 0) return;
	recursiveAdd(root, word);
}

//Trie �ڷᱸ������ �ܾ� �˻�
bool recursiveSearch(TrieNode* curNode, string word) {
	if (word.length() == 0) {
		return curNode->isEnd;
	}
	else {
		char ch = word[0];
		if (curNode->children.find(ch) == curNode->children.end()){
			return false;
		}
		return recursiveSearch(curNode->children[ch], word.substr(1));
	}
}

bool search(TrieNode* root, string word) {
	if (word.length() == 0) return true;
	return recursiveSearch(root, word);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	TrieNode root;

	add(&root, "baby");
	add(&root, "boy");

	cout << search(&root, "baby");
	cout << search(&root, "boo");

	return 0;
}

