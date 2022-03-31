#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
	//���̰� ���� �ܾ�鳢�� Ʈ���� ���� -> string �� ǥ���� �ʿ� X
	//bool isEndOfWord;
	
	struct TrieNode *children[ALPHABET_SIZE];
	
	//���� Ʈ���� ����� �θ� �Ʒ� ���� ����� �� ����
	int numOfLeaf;
};


//���ο� Ʈ���� ��� ����
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
		//�ڽ��� ���� ����� �� ����
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

		//query�� ���ڰ� ?�� ��� ���� Ʈ���� ����� �θ��� numOfLeaf ��ȯ
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
	
	//words ���� �ߺ� ���� ����
	words.erase(unique(words.begin(), words.end()), words.end());

	//�ܾ��� ����, ���� ������ �ܾ�θ� ���� Ʈ���� 
	map<int, TrieNode*> trieRoot;

	//�ܾ��� ����, ���� ������ ������ �ܾ�θ� ���� Ʈ���� 
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



