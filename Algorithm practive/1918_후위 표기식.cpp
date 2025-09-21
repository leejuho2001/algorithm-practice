#define _CRT_SECURE_NO_WARNINGS

/*
	---- 1918_���� �ִܰŸ� ----

	���̵�� : ����� ������ �������� ����ǹǷ�, ������ ����Ͽ� ǥ��

	������ ����ϰ�, ����� ť�� Ǫ���ϴ� ������� ����.
	�� ��ȣ���� ������ ���� �ൿ����� �޶������� ��.
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
