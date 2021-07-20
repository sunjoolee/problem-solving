#include <iostream>
#include <string>
using namespace std;

struct Node {
	char data;
	Node* right, *left;
};


Node* head;
Node* cursor;

//head -> input -> cursor
void createList(string input) {
	head= new Node;
	head->left = NULL;
	head->right = NULL;

	int len = input.size();
	Node* prevNode = head;
	for (int i = 0; i < len; ++i) {
		Node* NewNode = new Node;
		NewNode->data = input[i];

		prevNode->right = NewNode;
		NewNode->left = prevNode;
		NewNode-> right = NULL;
			
		prevNode = NewNode;
	}

	cursor = new Node;
	prevNode->right = cursor;
	cursor->left = prevNode;
	cursor->right = NULL;
	return;
}

	
void deleteNode() {
	if (cursor->left == NULL) return;

	Node* delNode = cursor->left;

	cursor->left = delNode->left;
	delNode->left->right = cursor;
	free(delNode);

	return;
}


void addNode(int x) {
	Node* NewNode = new Node;
	NewNode->data = x;

	NewNode->left = cursor->left;
	NewNode->right = cursor;
	cursor->left = NewNode;

	return;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string input;
	cin >> input;

	createList(input);

	int M;
	cin >> M;
	while (M--) {
		char instruction;
		cin >> instruction;

		//커서 왼쪽으로 이동
		if (instruction == 'L') {
			if (cursor->left == NULL) continue;
			cursor = cursor->left;
		}

		//커서 오른쪽으로 이동
		else if (instruction == 'D') {
			if (cursor->right == NULL) continue;
			cursor = cursor->right;
		}

		//커서 왼쪽에 노드 노드 삭제
		else if (instruction == 'B')
			deleteNode();

		//커서 왼쪽에 노드 삽입
		else if (instruction == 'P') {
			char x;
			cin >> x;
			addNode(x);
		}		
	}

	Node* printNode = head ->right;
	while (printNode != NULL) {
		cout << printNode -> data;
		printNode = printNode->right;
	}

	return 0;
}