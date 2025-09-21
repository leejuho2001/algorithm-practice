#define _CRT_SECURE_NO_WARNINGS
#define epsilon 1e-5
/*
	---- 2166_�ٰ��� ----

	�ٽ� ������ �����ΰ�? �ܺ��ΰ��� �����ϴ� ��.

	�ϳ��� ���� ������ �� ������ �����ٰ� ��������.
	�׷� ��� �� ���� ������ ������ ������ �� ���̴�.

	�׸��� �ϳ��� �� + �ϳ��� ������ �̷���� �ﰢ���� �ݽð��������
	������ �־��� ��, �ش� ���� ���� ������
	�� ó�� �� ������ �������� ����� �ݴ��� �ܺ�,
	������ ���ٸ� ���ο� �ش��Ѵ�.

	���� �ܺο� �ش��ϴ� ���̸� ��� ����, ���ο� �ش��ϴ� ���̸� ��� �����ָ� ���� ������ �ȴ�.

	1. y�� ���� ���� ū ���� �������� ���� ���� ������ ���صд�.
	2. �ش� ���� �ﰢ���� �̷� �� �ִ� ���鿡 ���� ������ ���ϰ�, �ش� ���⿡ ���� ���ϰų�, ���� ���θ� ���Ѵ�.

	�ش� �˰����� ���� Ž���� �ݽð� �������� �����Ѵٴ� ���� ������ �Ѵ�.
	���� �Է¹��� ������ Ž���� �ð� �������� ���� �� ���, ������ �ݴ�� �Ͽ� Ž���Ѵ�.
	���� :: ����ġ�� -1�� ������. (������ �ݴ� ����� ����)

	��� ������ �� �� �ִ°�?
	a->b->c�� ������, b->c->d�� ������ ������ ��, ��ȣ�� �ݴ��� ���
	������ �ݴ����� �� �� �ִ�. ���� �� ���� ���� ������ ���ϴ� ���� �ֿ� 
	*/


/*
#include<stdio.h>
#include<math.h>

typedef struct _coord {
	long long int x;
	long long int y;
}crd;

typedef struct _vector {
	long long int x;
	long long int y;
}vector;

int n;
crd coords[10005];
int currentdir = 0;

long double triangle(crd a, crd b, crd c);
void setVector(vector* v, crd s, crd e);
long double norm(vector v);
long double dotP(vector a, vector b);
void input();

long long int detZ(vector A, vector B) {
	return (long long int)A.x * B.y - B.x * A.y;
}

long long int getDir(crd a, crd b, crd c) {
	vector vectorA = {};
	vector vectorB = {};
	setVector(&vectorA, a, b);
	setVector(&vectorB, b, c);

	long long int det = detZ(vectorA, vectorB);
	if (det > 0) { currentdir = 1;  return 1; }
	else if (det == 0) return currentdir;
	else { currentdir = -1; return -1; }
}

long double triangle(crd a, crd b, crd c) {
	vector vectorA = {};
	vector vectorB = {};
	vector vectorC = {};
	setVector(&vectorA, a, b);
	setVector(&vectorB, b, c);
	setVector(&vectorC, a, c);
	long double normA = norm(vectorA);
	long double normB = norm(vectorB);
	long double normC = norm(vectorC);
	//printf("%lf %lf %lf\n", normA, normB, normC);
	long double normS = (normA + normB + normC) / 2;

	return (long double)sqrt(normS * (normS - normA) * (normS - normB) * (normS - normC));
}

void setVector(vector* v, crd s, crd e) {
	v->x = e.x - s.x;
	v->y = e.y - s.y;
}

long double norm(vector v) {
	long long int sqdist = (long long int) v.x * v.x + v.y * v.y;
	return (long double)sqrt(sqdist);
}

long double dotP(vector a, vector b) {
	long long int dotp = (long long int )a.x * b.x + a.y * b.y;
	return (long double)dotp;
}


void input() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lld%lld", &coords[i].x, &coords[i].y);
	}
}

long double polygon() {
	long double result = 0;
	int a, b, c;
	for (int i = 1; i < n - 1; i++) {
		a = 0, b = (i) % n,  c = (i + 1) % n;
		result += (long double)getDir(coords[a], coords[b], coords[c]) * triangle(coords[a], coords[b], coords[c]);
		
	}

	if (result < 0) return -1 * result;
	else return result;
}


int main() {
	input();

	printf("%.1lf\n", round(polygon() * 10) / 10);
}
*/

#include<stdio.h>
#include<math.h>

typedef struct _coord {
	double x;
	double y;
}crd;

crd coords[10005];

int main() {
	double res = 0;
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		double x, y;
		scanf("%lf%lf", &x, &y);
		coords[i] = { x, y };
	}

	for (int i = 0; i < n ; i++) {
		int b = i, f = (i + 1) % n;

		res += coords[b].x * coords[f].y;
		res -= coords[b].y * coords[f].x;
	}
	res /= (double)2;
	if (res < 0) res *= (double) - 1;
	printf("%.1lf\n", (double)round((res * 10)) / 10);
}

// ��� 2. �Ź߲� ���� ���