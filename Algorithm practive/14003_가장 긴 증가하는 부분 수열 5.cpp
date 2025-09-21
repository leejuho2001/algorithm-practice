#define _CRT_SECURE_NO_WARNINGS
/*
    ---- 11053_���� �� �����ϴ� �κ� ���� 5 ----

    :: ������ : ������ ������ -10^9 ~ 10^9�� �þ���.
    ���׸�Ʈ Ʈ���� ������ ������ ������ �̿��� Ǯ�̿�����, 
    ������ ������ �ʹ� Ŀ�� ���׸�Ʈ Ʈ���� Ȱ���� �� ���� �Ǿ���.

    -> �ٸ� DP Ǯ�� ����� �ʿ��ϴ�.

    idea : ���� DP ����� ������� ���� �� ������ ������� �Ѵ�.
    ���� �� ���ڴ� ������� �ʴ´�.

    ���� ��ȣ�� ���̰� n�� ������ ������ ���� �Ǳ� ���ؼ�, n-1��° ������ �� Ŀ���Ѵ�.
    �� ���� ������, ���̰� n-1�� ���� �߿��� ���� ���� ���Ҹ� ���� ������ �����ϴ�.
    �� ���� �̿��� ���̰� n�� �������� ���� ���� ������ ���Ҹ� �����ϴ� �迭�� ����� Ȱ���ϸ� �ȴ�.
    �׷��� �� ���, �ش� �迭�� ������������ ���ĵȴ�.
    �̸� �̿���, �̺�Ž���� �Ͽ� ���� ������ ���� ã�´�.

    �̺�Ž���� O(logN)�� ���⵵�� �����Ƿ�, ���������� O(NlogN)�� �ð����⵵�� ������.

    ����� ��� �� ���ΰ�?
    :: ���� �� ���̰� ������ ���, �� ���� element�� ���� �� �ֵ��� ���־�� �Ѵ�.
    ���� ���̰� n�� ���� ��, ������ ���Ұ� ���� ���� �������� n-1��° ���� �����ϴ� 
    */
#include<stdio.h>
#include<stack>
using namespace std;
#define end 1000000
#define start 1
stack<int>subseq;

int SLE[1000050]; // smallest last element.
int SLE_add[1000050];
int sequence[1000050];
int before[1000050];
int n;
int MAX;

int biSearch(int s, int e, int value) {
    if (s == e) return s-1;

    int center = (s + e) / 2;
    if (sequence[SLE[center]] >= value) return biSearch(s, center, value);
    else return biSearch(center + 1, e, value);
}

void LIS() {
    for (int i = 1; i <= n; i++) {
        int curr = sequence[i];
        int address = biSearch(start, end, curr);
        //printf("%d - %d\n",curr, address);

        if (SLE[address+1] == 0 ||sequence[SLE[address + 1]] > curr) { 
            SLE[address + 1] = i; 
            before[i] = SLE[address];
            if (address + 1 > MAX) MAX = address + 1;
        }


    }
    int st = SLE[MAX];
    while(before[st] >= 0){
        subseq.push(sequence[st]);
        if (before[st] == 0) break;
        st = before[st];
    } 


    
    printf("%d\n", MAX);

    while (!subseq.empty()) {
        printf("%d ", subseq.top());
        subseq.pop();
    }
}

void initialize() {
    sequence[0] = 1000000050;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", sequence + i);
    initialize();
    LIS();
}

//10 20 30 20 50 70 60 40 80