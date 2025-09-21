/*
	---- 14940_나는야 포켓모 마스터 이다솜 ----

	아이디어:

	해싱을 하여 각 이름들의 주소들을 저장한다.
	왠만한 경우 첫번째 알파벳만 대문자 라는 점을 활용하여, <(첫번째 알파벳), (해싱된 나머지 string)> 
	좌표에 주소가 저장되도록 한다.

	hashing 방식

	1번 시도
	: 뒤에 있는 알파벳들에 대해, 
	아스키 코드 기준 첫번째 알파벳인 'A'의 주소값을 뺀 뒤, 2를 곱해가며 더함.
	그리고 결과값을 99999로 나눈 나머지를 사용.

	문제점 :: 중복되는 값이 나올 수 있음.

	--> 연결리스트 형태로 구현의 형태가 바뀌어야함.
	--> 키의 원본 string을 적고 cmp를 하는 과정이 필요함.
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
