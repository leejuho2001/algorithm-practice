/*
	---- 14940_���¾� ���ϸ� ������ �̴ټ� ----

	���̵��:

	�ؽ��� �Ͽ� �� �̸����� �ּҵ��� �����Ѵ�.
	�ظ��� ��� ù��° ���ĺ��� �빮�� ��� ���� Ȱ���Ͽ�, <(ù��° ���ĺ�), (�ؽ̵� ������ string)> 
	��ǥ�� �ּҰ� ����ǵ��� �Ѵ�.

	hashing ���

	1�� �õ�
	: �ڿ� �ִ� ���ĺ��鿡 ����, 
	�ƽ�Ű �ڵ� ���� ù��° ���ĺ��� 'A'�� �ּҰ��� �� ��, 2�� ���ذ��� ����.
	�׸��� ������� 99999�� ���� �������� ���.

	������ :: �ߺ��Ǵ� ���� ���� �� ����.

	--> ���Ḯ��Ʈ ���·� ������ ���°� �ٲ�����.
	--> Ű�� ���� string�� ���� cmp�� �ϴ� ������ �ʿ���.
	: 
	
	*/

#define _CRT_SECURE_NO_WARNINGS
#define tableSize 47

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<list>
using namespace std;

typedef struct Str {
	char charS[25];
	int key;
}string;

int stringCmp(string a, string b) {
	return strcmp(a.charS, b.charS);
}

int stringLen(string a) {
	return strlen(a.charS);
}

list<string> table[tableSize];
char strings[100005][25] = {};

int hashing(string s) {
	int res = 0;
	for (int i = 0; i < stringLen(s); i++) {
		res += s.charS[i];
	}

	return res % tableSize;
}

void addNode(string str) {
	int hash = hashing(str);
	table[hash].push_back(str);
}

void initializeStr(string* str, char* cStr, int _key) {
	strcpy(str->charS, cStr);
	str->key = _key;
}

int returnKey(char* str) {
	string newStr;
	initializeStr(&newStr, str, -1);

	int hash = hashing(newStr);

	for (list<string>::iterator iter = table[hash].begin(); iter != table[hash].end(); iter++) {
		if (stringCmp(newStr, *iter) == 0) {
			return iter->key;
		}

	}
	return -1;
}


int main() {
	int n, m;
	
	scanf("%d%d", &n, &m);



	for (int i = 1; i <= n; i++) {
		scanf("%s", strings[i]);
		string newStr = {};
		initializeStr(&newStr, strings[i], i);
		addNode(newStr);
	}

	for (int i = 0; i < m; i++) {
		char* temp = (char*)malloc(sizeof(char) * 25);
		scanf("%s", temp);

		if (atoi(temp) != 0) {
			printf("%s\n", strings[atoi(temp)]);
		}
		else {
			printf("%d\n", returnKey(temp));
		}
	}
}
