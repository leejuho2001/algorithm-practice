#define _CRT_SECURE_NO_WARNINGS
/*
	---- 2448_����� 11 ----

                       *                3, 12
                      * *
                     *****
                    *     *
                   * *   * *
                  ***** *****          2, -6  , 2, +6 
                 *           *
                * *         * *
               *****       *****        
              *     *     *     *
             * *   * *   * *   * *
            ***** ***** ***** *****
           *   
    :: 12�� ���.

    base : n��° ���� ���� ������ ����
    = 24-n��.

    �ԷµǴ� ���� 3 * 2^n�� ���¸� ������.
    --> 2^n�� ������ ���踦 ������.

    ����� ���¸� ������ �ִ�.
    = ��ͷ�, ������ �迭�� ���� ���·� �����Ѵ�.
    ����� = �ٸ��� �Է��� �ʿ䰡 ���� = true/false�� ���� ����.

    ��� ������ΰ�?
    �ϳ��� �ﰢ�� = ���̰� ���� �ﰢ�� -> ���ʹ�, �����, ������ ��.
    
    �ﰢ���� ���� �� �������� ��ġ��, ���̷� ǥ���Ѵ�.
    �׷��� �� ���, ���ʹݰ� ������ ���� �� ������ ��ġ��
    ���ʹ� : ���� - ���� ��(x), +0.5����(y), ������ �� : ���� +0.5����(x), +0.5����(y)�� ǥ���ȴ�.
*/

#include<stdio.h>
bool graph[3500][7000] = {};


void triangle(int x, int y, int size, int length) {
    //printf("%d %d\n", x, y);
    if (size == 1) {
        graph[x][y] = true;
        graph[x + 1][y - 1] = true;
        graph[x + 1][y + 1] = true;
        for (int i = -2; i <= 2; i++) {
            graph[x + 2][y+i] = true;
        }
        return;
    }
    triangle(x, y, size - 1, length / 2);
    triangle(x + length / 2, y - length / 2, size - 1, length / 2);
    triangle(x + length / 2, y + length / 2, size - 1, length / 2);
}

int main() {
    int n;
    scanf("%d", &n);
    int temp = n;
    int cnt = 0;
    temp /= 3;
    while (temp > 0) {
        cnt++;
        temp /= 2;
    }

    triangle(1, n, cnt, n);

    for (int i = 1; i <= n; i++) {
        for (int q = 1; q <= n *2; q++) {
            if (graph[i][q] == true) printf("*");
            else printf(" ");
        }
        puts("");
    }
}