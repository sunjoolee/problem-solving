#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
	//길이가 같은 단어들끼리 트라이 생성 -> string 끝 표시할 필요 X
	//bool isEndOfWord;
	
	struct TrieNode *children[ALPHABET_SIZE];
	
	//현재 트라이 노드의 부모 아래 리프 노드의 수 저장
	int numOfLeaf;
};


//새로운 트라이 노드 생성
struct TrieNode *getNode(void) {
	struct TrieNode *pNode = new TrieNode;

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
		//자신의 리프 노드의 수 증가
		pCrawl->numOfLeaf++;

		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}
}


int search(struct TrieNode *root, string key) {
	struct TrieNode *pCrawl = root;

	for (int i = 0; i < key.length(); i++){

		//query의 문자가 ?인 경우 현재 트라이 노드의 부모의 numOfLeaf 반환
		if (key[i] == '?') {
			return pCrawl->numOfLeaf;
		}

		int index = key[i] - 'a';
		if (!pCrawl->children[index]) return 0;
		pCrawl = pCrawl->children[index];
	}
	return 1;
}

vector<int> solution(vector<string> words, vector<string> queries) {
	
	//words 벡터 중복 원소 제거
	words.erase(unique(words.begin(), words.end()), words.end());

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
	solution({ "frodo", "front", "frost", "frozen", "frame", "kakao" }, { "frod?", "????o", "fr???", "fro???", "pro?", "?????" });
}



