#define _CRT_SECURE_NO_WARNINGS

/*
	---- 1918_쉬운 최단거리 ----

	아이디어 : 계산이 기존의 역순으로 진행되므로, 스택을 사용하여 표현

	스택을 사용하고, 결과는 큐에 푸시하는 방식으로 구현.
	각 기호들의 유형에 따라 행동방식이 달라지도록 함.
	*/

#include <stdio.h>
#include <string.h>
#include <stack>
#include <queue>

using namespace std;

queue<char> result;
stack<char> st;
char fomula[150];

int category(char _c) {
	char character = _c;

	if (character == '+' || character == '-') return 1;
	if (character == '*' || character == '/') return 2;
	if (character == '(') return 3;
	if (character == ')') return 4;
	else return 0;
}

int main() {
	scanf("%s", fomula);
	int len = strlen(fomula);

	for (int i = 0; i < len; i++) {
		char current = category(fomula[i]);
		switch (current) {
		case 0:
			result.push(fomula[i]);
			break;
		case 1:
			while (!st.empty() && category(st.top())!=3) {
				//  && category(st.top()) == 2
				result.push(st.top());
				st.pop();
			}
			st.push(fomula[i]);
			break;
		case 2:
			while (!st.empty() && category(st.top()) == 2) {
				result.push(st.top());
				st.pop();
			}
			st.push(fomula[i]);
			break;
		case 3:
			st.push(fomula[i]);
			break;
		case 4:
			while (st.top() != '(') {
				result.push(st.top());
				st.pop();
			}
			st.pop();
			break;
		}
	}

	while (!st.empty()) {
		result.push(st.top());
		st.pop();
	}

	while (!result.empty()) {
		printf("%c", result.front());
		result.pop();
	}

}
