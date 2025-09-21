#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<math.h>
#include<stack>
#include<algorithm>
using namespace std;

typedef struct _crd {
	long long int x;
	long long int y;
}crd;

crd piv;
bool cmp(crd a, crd b) {
	long long int xdiv1 = a.x - piv.x;
	long long int xdiv2 = b.x - piv.x;
	long long int ydiv1 = a.y - piv.y;
	long long int ydiv2 = b.y - piv.y;

	float angle1, angle2;

	angle1 = atan2(ydiv1, xdiv1);
	angle2 = atan2(ydiv2, xdiv2);
	if (angle1 == angle2) {
		if (a.y == b.y) return a.x < b.x;
		return a.y < b.y;

	}
	return angle1 < angle2;
}

bool isRight(crd first, crd second, crd third) {
	crd vec1 = { second.x - first.x , second.y - first.y };
	crd vec2 = { third.x - first.x, third.y - first.y };

	long long int detP = vec1.x * vec2.y - vec1.y * vec2.x;
	if (detP > 0) return false;
	else return true;
}
crd crds[100010] = {};
stack<crd> ready;

int main() {
	
	
	long long int n, a, b;
	scanf("%lld", &n);
	for (long long int i = 0; i < n; i++) {
		scanf("%lld %lld", &a, &b);
		crds[i].x = a;
		crds[i].y = b;
	}

	for (long long int i = 1; i < n; i++) {
		if (crds[i].y < crds[0].y) {
			crd indx = { crds[i].x, crds[i].y };
			crds[i] = { crds[0].x, crds[0].y };
			crds[0] = { indx.x, indx.y };
		}
		else if(crds[i].y == crds[0].y && crds[i].x < crds[0].x) {
			crd indx = { crds[i].x, crds[i].y };
			crds[i] = { crds[0].x, crds[0].y };
			crds[0] = { indx.x, indx.y };
		}
	}

	piv = {crds[0].x, crds[0].y};
	sort(crds + 1, crds + n, cmp);

	int i = 0;
	ready.push(crds[i++]);
	ready.push(crds[i++]);

	while (i < n) {
		while (ready.size() >1) {
			crd f, s;
			f = ready.top();
			ready.pop();
			s = ready.top();

			if (isRight(s, f, crds[i]) == false) {
				ready.push(f);
				break;
			}
		}
		ready.push(crds[i++]);
	}

	if (isRight(crds[n - 2], crds[n - 1], crds[0]) == true) ready.pop();


	printf("%d", ready.size());
}
