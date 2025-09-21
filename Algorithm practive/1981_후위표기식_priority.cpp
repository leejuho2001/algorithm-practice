/*
	---- 1918_쉬운 최단거리 ----

	이전 풀이방식은 하드코딩에 가까운 예외를 처리하는 방식.
	카데고리를 중요도를 반환하는 방식으로 변경.
	이를 통해 중요도의 크기를 비교하는 방식으로 행동을 변경함.

	--> 기대효과 : 식 처리에 대한 일반화가 가능해짐.
	*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stack>
#include <queue>

using namespace std;

queue<char> result;
stack<char> st;
char fomula[150];

int priority(char _c) {
	char character = _c;

	
	if (character == '*' || character == '/') return 1;
	if (character == '+' || character == '-') return 2;
	if (character == '(') return 3;
	if (character == ')') return 4;
	else return -1;
}

int main() {
	scanf("%s", fomula);
	int len = strlen(fomula);



	for (int i = 0; i < len; i++) {
		char current = priority(fomula[i]);
		if (current == -1) {
			result.push(fomula[i]);
		}
		else {
			if (fomula[i] == ')') {
				while (st.top() != '(') {
					result.push(st.top());
					st.pop();
				}
				st.pop();
			}

			else {
				while (!st.empty() && current >= priority(st.top())) {
					result.push(st.top());
					st.pop();
				}
				st.push(fomula[i]);
			}
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
