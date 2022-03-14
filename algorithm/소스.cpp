#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory.h>
#include <algorithm>
using namespace std;

/*
struct Trie {
	bool finish; // 끝나는 지점을 표시해줌 
	Trie* next[26]; // 26가지 알파벳에 대한 트라이 
					
	// 생성자 
	Trie() : finish(false) { 
		memset(next, 0, sizeof(next)); 
	} 

	// 소멸자 
	~Trie() { 
		for (int i = 0; i < 26; i++) 
			if (next[i]) delete next[i]; 
	} 
	
	// 트라이에 문자열 삽입 
	void insert(const char* key) {

		// 문자열이 끝나는 지점일 경우 표시 
		if (*key == '\0') finish = true; 

		else {
			int curr = *key - 'A';
			if (next[curr] == NULL) {
				// 탐색이 처음되는 지점일 경우 동적할당 
				next[curr] = new Trie();
			}
			// 다음 문자 삽입 
			next[curr]->insert(key + 1); 
		} 
	}
	
	// 트라이에서 문자열 찾기 
	Trie* find(const char* key) { 

		// 문자열이 끝나는 위치를 반환 
		if (*key == '\0') return this;

		int curr = *key - 'A'; 
		
		// 찾는 값이 존재하지 않음 
		if (next[curr] == NULL) return NULL; 

		// 다음 문자를 탐색
		return next[curr]->find(key + 1); 
		
	} 
};

*/

struct TrieNode {
	bool isEnd;
	map<char, TrieNode*> children;

	TrieNode() : isEnd(false) {}
};

//Trie 자료구조에 단어 추가
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

//Trie 자료구조에서 단어 검색
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

