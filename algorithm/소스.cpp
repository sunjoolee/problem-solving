#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef double db;

struct page {
	int index;
	string content;
	vector<string> linkedPages;

	db kibonScore;
	db linkCnt;
	db linkScore;

	page() : index(-1), content(""), kibonScore(0), linkCnt(0), linkScore(0) {
		linkedPages.clear();
	}
	page(int index, string content, vector<string> linkedPages) : index(index), content(content), kibonScore(0), linkCnt(0), linkScore(0){
		linkedPages = linkedPages;
	}
};

int solution(string word, vector<string> pages) {
	
	int N = pages.size();
	transform(word.begin(), word.end(), word.begin(), ::tolower);

	//index�� ���� �������� �ּ�
	map<int, string> pageContent;

	//string �ּҸ� ���� �������� ���� ���� ��
	map<string, page> pageMap;

	//HTML �������κ��� ������ �ּ� & ����� ������ �ּ� ���� 
	//�ش� �������� �⺻ ���� ���
	for (int index = 0; index < pages.size(); ++index) {
		string content;
		db kibon = 0;
		vector<string> links;

		//������ �ּ� & ����� ������ �ּҿ� ����
		string buffer = "";
		//�⺻ ���� ���� ����
		string buffer2 = "";

		for (int j = 0; j < pages[index].length(); ++j) {
			char ch = pages[index][j];

			if (ch == ' ' || ch == '\n') {
				transform(buffer2.begin(), buffer2.end(), buffer2.begin(), ::tolower);
				if (buffer2 == word) ++kibon;
				buffer2 = "";

				buffer = "";
				continue;
			}

			buffer += ch;

			if (!('a' <= ch && ch <= 'z') && !('A' <= ch && ch <= 'Z')) {
				transform(buffer2.begin(), buffer2.end(), buffer2.begin(), ::tolower);
				if (buffer2 == word) ++kibon;
				buffer2 = "";
			}
			else buffer2 += ch;


			//�ش� ������ �ּ� �Է¹ޱ�
			if (buffer == "content=\"") {
				int k = j+1;
				while(true) {
					char ch1 = pages[index][k];
					if (ch1 == '\"') break;
					content += ch1;
					k++;
				}
				j = k;
				buffer = "";
				continue;
			}

			//�ش� �������κ��� ����� �ܺ� ������ �ּ� �Է¹ޱ�
			if (buffer == "href=\"") {
				int k = j + 1;
				string href = "";
				while (true) {
					char ch1 = pages[index][k];
					if (ch1 == '\"') break;
					href += ch1;
					k++;
				}
				links.push_back(href);
				j = k;
				buffer = "";
				continue;
			}			
		}

		pageContent[index] = content;
		page pageInfo = page(index, content, links);
		pageInfo.kibonScore = kibon;

		pageMap.insert({ content, pageInfo });
	}


	//�ܺ� ��ũ��, ��ũ ���� ����ϱ�
	for (int index = 0; index < N; ++index) {
		
		page* pageInfo = &pageMap[pageContent[index]];

		//�ܺ� ��ũ�� ���
		pageInfo->linkCnt = pageInfo->linkedPages.size();

		//�ش� �������� ����� �ܺ� �������� ��ũ ���� ���
		for (int j = 0; j < pageInfo->linkedPages.size(); ++j) {
			string href = pageInfo->linkedPages[j];
			if (pageMap.find(href) == pageMap.end()) continue;

			page linkedPageInfo = pageMap[href];
			pageInfo->linkScore += (linkedPageInfo.kibonScore / linkedPageInfo.linkCnt);
		}
	}

	int answer = 0;
	db maxMatchScore = 0;

	for (int index = 0; index < N; ++index) {
		db matchScore = pageMap[pageContent[index]].kibonScore + pageMap[pageContent[index]].linkScore;
		if (matchScore > maxMatchScore) {
			maxMatchScore = matchScore;
			answer = index;
		}
	}

	return answer;
}

int main() {

	solution("Muzi", { "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://careers.kakao.com/interview/list\"/>\n</head>  \n<body>\n<a href=\"https://programmers.co.kr/learn/courses/4673\"></a>#!MuziMuzi!)jayg07con&&\n\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://www.kakaocorp.com\"/>\n</head>  \n<body>\ncon%\tmuzI92apeach&2<a href=\"https://hashcode.co.kr/tos\"></a>\n\n\t^\n</body>\n</html>" });
}