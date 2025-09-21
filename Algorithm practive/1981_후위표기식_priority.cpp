/*
	---- 1918_���� �ִܰŸ� ----

	���� Ǯ�̹���� �ϵ��ڵ��� ����� ���ܸ� ó���ϴ� ���.
	ī������ �߿䵵�� ��ȯ�ϴ� ������� ����.
	�̸� ���� �߿䵵�� ũ�⸦ ���ϴ� ������� �ൿ�� ������.

	--> ���ȿ�� : �� ó���� ���� �Ϲ�ȭ�� ��������.
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
