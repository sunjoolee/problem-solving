#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
	bool isEndOfWord;
	struct TrieNode *children[ALPHABET_SIZE];
	
	//현재 트라이 노드 아래 리프 노드의 수 저장
	int numOfLeaf;
};


//새로운 트라이 노드 생성
struct TrieNode *getNode(void) {
	struct TrieNode *pNode = new TrieNode;

	pNode->isEndOfWord = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;

	pNode->numOfLeaf = 0;

	return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node

void insert(struct TrieNode *root, string key) {
	struct TrieNode *pCrawl = root;

	for (int i = 0; i < key.length(); i++){
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		//자식 노드로 내려가기 전, 자신의 리프 노드의 수++
		pCrawl->numOfLeaf++;
		pCrawl = pCrawl->children[index];
	}

	// mark last node as leaf
	pCrawl->isEndOfWord = true;
}


int search(struct TrieNode *root, string key) {
	struct TrieNode *pCrawl = root;

	for (int i = 0; i < key.length(); i++){
		//query의 다음 문자가 ?인 경우 현재 트라이 노드 아래 리프 노드의 개수 반환
		if (i+1 < key.length() && key[i] == '?') {
			return pCrawl->numOfLeaf;
		}

		int index = key[i] - 'a';
		if (!pCrawl->children[index]) return 0;
		pCrawl = pCrawl->children[index];
	}
	return (pCrawl->isEndOfWord);
}

vector<int> solution(vector<string> words, vector<string> queries) {
	
	//단어의 길이, 같은 길이의 단어로만 만든 트라이 
	map<int, TrieNode*> trieRoot;

	//단어의 길이, 같은 길이의 뒤집은 단어로만 만든 트라이 
	map<int, TrieNode*> reverseTrieRoot;
	
	// Construct trie
	for (int i = 0; i < words.size(); i++) {
		int len = words[i].length();

		if (trieRoot.find(len) == trieRoot.end()) {
			struct TrieNode *root = getNode();
			trieRoot[len] = root;

			struct TrieNode *reverseRoot = getNode();
			reverseTrieRoot[len] = reverseRoot;
		}

		insert(trieRoot[len], words[i]);
		reverse(words[i].begin(), words[i].end());
		insert(reverseTrieRoot[len], words[i]);
	}
	
	vector<int> answer;

	// Search
	for (int i = 0; i < queries.size(); ++i) {
		int len = queries[i].length();
		if (trieRoot.find(len) == trieRoot.end()) {
			answer.push_back(0);
			continue;
		}

		if (queries[i][0] == '?') {
			reverse(queries[i].begin(), queries[i].end());
			answer.push_back(search(reverseTrieRoot[len], queries[i]));
		}
		else {
			answer.push_back(search(trieRoot[len], queries[i]));
		}
	}

	return answer;
}

int main() {
	solution({ "frodo", "front", "frost", "frozen", "frame", "kakao" }, { "fro??", "????o", "fr???", "fro???", "pro?" });
}



