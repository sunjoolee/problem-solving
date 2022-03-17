#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int MAXVAL = 987654321;

map<int, pair<int, int>> node;
vector<int> traverseRes;

struct TreeNode{
	int id;
	TreeNode* left;
	TreeNode* right;
};

TreeNode* newNode(int id) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->id = id;
	temp->left = temp->right = NULL;
	return temp;
}

void makeTree(TreeNode* node, vector<int> leftCand, vector<int> rightCand){
	if (leftCand.empty() && rightCand.empty()) return;

	vector<int> leftCand2;
	vector<int> rightCand2;
	//왼쪽 자식 찾기
	if (!leftCand.empty()) {
		sort(leftCand.begin(), leftCand.end(), cmpID);
		node->left = newNode(leftCand[0]);

		leftCand2.clear();
		rightCand2.clear();
		for (int i = 0; i < leftCand.size(); ++i) {
			if (globalNodeInfo[leftCand[i]].first < globalNodeInfo[leftCand[0]].first) leftCand2.push_back(i);
			if (globalNodeInfo[leftCand[i]].first > globalNodeInfo[leftCand[0]].first)  rightCand2.push_back(i);
		}
		makeTree(node->left, leftCand2, rightCand2);
	}

	//오른쪽 자식 찾기
	if (!rightCand.empty()) {
		sort(rightCand.begin(), rightCand.end(), cmpID);
		node->right = newNode(rightCand[0]);

		leftCand2.clear();
		rightCand2.clear();
		for (int i = 0; i < rightCand.size(); ++i) {
			if (globalNodeInfo[rightCand[i]].first < globalNodeInfo[rightCand[0]].first) leftCand2.push_back(i);
			if (globalNodeInfo[rightCand[i]].first > globalNodeInfo[rightCand[0]].first) rightCand2.push_back(i);
		}
		makeTree(node->right, leftCand2, rightCand2);
	}
	return;
}


//전위 순회: 뿌리 > 왼쪽자식 > 오른쪽 자식
void traverse1(TreeNode* curNode) {
	traverseRes.push_back(curNode->id + 1);

	if (curNode->left != NULL) {
		traverse1(curNode->left);
	}
	if (curNode->right != NULL) {
		traverse1(curNode->right);
	}
}

//후위 순회: 왼쪽자식 > 오른쪽 자식 > 뿌리
void traverse2(TreeNode* curNode) {

	if (curNode->left != NULL) {
		traverse2(curNode->left);
	}
	if (curNode->right != NULL) {
		traverse2(curNode->right);
	}

	traverseRes.push_back(curNode->id + 1);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {

	//전역변수 초기화
	//y좌표가 가장 작은 노드 = 루트 노드 
	int rootId;
	int minY = 

	for (int i = 0; i < nodeinfo.size(); ++i) {
		node[i] = { nodeinfo[i][0], nodeinfo[i][1]};
	}
	
	


	TreeNode* root = newNode(0);
	vector<int> leftCand;
	vector<int> rightCand;
	for (int i = 0; i < globalNodeInfo.size(); ++i) {
		if (globalNodeInfo[i].first < globalNodeInfo[root->id].first) leftCand.push_back(i);
		if (globalNodeInfo[i].first > globalNodeInfo[root->id].first) rightCand.push_back(i);
	}

	makeTree(root, leftCand, rightCand);


	//순회 결과 저장
	vector<vector<int>> answer;

	traverseRes.clear();
	traverse1(root);
	answer.push_back(traverseRes);
	
	traverseRes.clear();
	traverse2(root);
	answer.push_back(traverseRes);

	return answer;
}