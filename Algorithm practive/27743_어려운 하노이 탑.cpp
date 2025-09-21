#define _CRT_SECURE_NO_WARNINGS

/*
	---- 27743_����� �ϳ��� ž ----

	���̵�� :

	1. ���� ũ���� �ǵ鳢�� ������ ������ �ϳ���ž�� �ϳ��� ���� �ű� ��, 
	������ ���鼭 �ű�� �Ͱ� ���� �ǹ̸� ������.

	2. ������ ���鼭 �ϳ��� ž�� �ű�ٰ� ���� ��, ���������� ������ Destination���� �ű�� �� �ɸ��� Ƚ���� ���ϴ� �����̴�.
	������ ��� �������̾�� �Ѵ� = ��� ���� ¦������ �������� �Ѵ�.

	3.  ��� ���� ¦������ ������ �ϳ���ž�� Ƚ�� >> �Ϲ� �ϳ��� ž�� Ƚ��
	because, ��� ������ ���� �� �� �Űܾ� �ϱ� ����.

	4. ������, n-1��° �Ǻ��� �Ϲ� �ϳ��� ž���� �ű���� ������ ¦������ �ű�� �ȴ�. 
	==> ����� �ϳ���ž�� Ƚ���� ���ϴ� �� �Ϲ� �ϳ��� ž�� Ƚ���� �̿��ϸ� �ȴ�.

	2�� �÷���Ʈ�� �ű�� �ǹǷ�, �� ���� ž�� 2ȸ�� �ƴ� �ι�, 4ȸ �ű�� �ȴ�.


	5. ���� ����� �ƴ�, ũ�Ⱑ ���� ���� �������� ���� ��,
	�� ������ ���� �� �� �̵��� ���� �� ���� �̵��� �� �ִ�. 

	���� ������ ũ���� �ǵ��� �̵���Ű�� �� �ɸ��� Ƚ���� 2m - 1 �̴�.


	��� :
	n ���� �ϳ��� ž�� �ű�� �� �ɸ��� �ּ� Ƚ���� f(n)�̶�� �ΰ�,
	�� ���� m���� ������ �����Ǿ� ������ n���� �ϳ��� ž�� �ű�� �� �ɸ��� �ּ� Ƚ���� f'(n,m)�̶�� ����.

	�� ��, f(n,m) = 4 * m * f(n-1) + 2 * m - 1.

	������, �ش� ������� �Ϲ� �ϳ��� ž�� Ƚ���� Ŀ���� �� �����Ƿ�,
	m = 1�� �� f(m)�� ����ϵ��� �Ѵ�.



	++n, m�� ������ 3 * 10^9�̴�.
	�̴� int�� ���� ������ 1.5�� �ణ �ȵǹǷ�, unsigned int�� n, m�� �����Ѵ�. 
	*/

/*
	---- power_divided(int a, int b) ----
	�Է� : unsigned int a, b
	��� : a�� b������ 1000000007�� ���� ���� ������.

	�̴� �Ϲ����� power�� �ƴ� ���������� ���� �ŵ������� �����ϱ� ������.
*/
#include<stdio.h>

unsigned long long int power_divided(unsigned a, unsigned b) {
	if (b == 0) return (unsigned int)1;
	if (b == 1) return a;
	unsigned int half_result = power_divided(a, b / 2);
	unsigned long long int result;
	unsigned long long int temp = (unsigned long long int) half_result;
	

	if (b % 2) { // Ȧ�����
		result = (temp * temp * (unsigned long long int) a) % 1000000007;
	}

	else {
		result = (temp * temp ) % 1000000007;
	}

	return result;
}

unsigned int hanoi(unsigned n) {
	return power_divided(2, n) - 1;
}

unsigned long long int hard_hanoi(unsigned int n, unsigned int m) {
	unsigned long long int result = (unsigned long long int) (4 * m * hanoi(n - 1) + 2 * m - 1) % 1000000007;
	return result;
}

int main() {
	unsigned int N, M;

	scanf("%u %u", &N, &M);
	unsigned int result;

	if (M == 1) result = hanoi(N);
	else result = hard_hanoi(N, M);

	printf("%llu", result);
}

// �ٸ�, ���� �ڵ�� �ణ�� ���� �޶����� �־� ������ �ʿ���