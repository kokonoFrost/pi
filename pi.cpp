#include <cstdio>
using namespace std;
int n;
struct bigdec {
	int size;
	long long elem[2000];
} a, b;
void del(bigdec &x) {
	while ((x.elem[x.size] == 0) && (x.size > 0)) x.size--;
}
void multi(bigdec &x, const long long p) {
	long long temp = 0;
	for (int i = x.size; i > 0; i--) {
		temp = x.elem[i] * p + temp;
		x.elem[i] = temp % 10;
		temp /= 10;
	}
	x.elem[0] += temp;
	del(x);
}
void divi(bigdec &x, const long long p) {
	long long temp;
	for (int i = 0; i <= x.size - 1; i++) {
		temp = x.elem[i] % p;
		x.elem[i] /= p;
		x.elem[i + 1] += temp * 10;
	}
	temp = x.elem[x.size] % p;
	x.elem[x.size] /= p;
	while (temp != 0 && x.size < 1600) {
		x.size++;
		x.elem[x.size] = temp * 10;
		temp = x.elem[x.size] % p;
		x.elem[x.size] /= p;
	}
	del(x);
}
void plus(bigdec &x, const bigdec p) {
	long long temp;
	if (x.size < p.size) x.size = p.size;
	for (int i = x.size; i > 0; i--) {
		temp = (x.elem[i] + p.elem[i]) / 10;
		x.elem[i] = (x.elem[i] + p.elem[i]) % 10;
		x.elem[i - 1] += temp;
	}
	x.elem[0] += p.elem[0];
	del(x);
}
void bigdec_pr(const bigdec x) {
	printf("%lld.", x.elem[0]);
	for (int i = 1; i <= n; i++) {
		printf("%lld", x.elem[i]);
	}
	printf("\n");
}
int main() {
	printf("计算pi小数点后位数：");
	scanf("%d", &n);
	a.elem[1] = 5;
	a.size = 1;
	plus(b, a);
	long long x, y;
	for (int i = 1; i <= n * 10; i++) {
		x = (long long)(2 * i - 1) * (2 * i - 1);
		y = (long long)(2 * i) * (2 * i + 1) * 4;
		multi(a, x);
		divi(a, y);
		plus(b, a);
	}
	multi(b, (long long)6);
	bigdec_pr(b);
	return 0;
}