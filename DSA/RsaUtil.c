#include <math.h>
#include "RsaUtil.h"

//check if number is prime for key genus
int prime(int pr) {
	int i, j;
	j = sqrt(pr);
	for (i = 2; i <= j; i++)
	{
		if (pr % i == 0)
			return 0;
	}
	return 1;

}

//The Euclidean algorithm for greatest common divisor
// (calculate public exponent 'e' 
int gcd(int a, int h) {
	int temp;
	while (1)
	{
		temp = a % h;
		if (temp == 0)
			return h;
		a = h;
		h = temp;
	}
};

//calculates the least common multiple (LCM) of two integers a and b
//the LCM is used in RSA key generation to calculate the modulus n
int lcm(int a, int b) {
	int temp = gcd(a, b);

	return temp ? (a / temp * b) : 0;
};

//calculate the result of n % p, ensure the result is a positive int
int modulo(int n, int p) {
	int r = n % p;
	if (((p > 0) && (r < 0)) || ((p < 0) && (r > 0)))
		r += p;
	return r;
};

//calculate the modular multiplicative inverse of 'n' modulo p(private exponent 'd' in RSA key generation)
int modInverse(int n, int p) {
	int x = 1;
	n = modulo(n, p);
	while (1)
	{
		if (modulo(n * x, p) == 1)
			return x;
		x++;
	}


	return 0;
};

//a^(b mod n)
//encryption and decryption for raising to a power modulo n.

int moduloPow(int a, int b, int n) {
	long long x = 1, y = a;
	while (b > 0) {
		if (b % 2 == 1) {
			x = (x * y) % n;
		}
		y = (y * y) % n;
		b /= 2;
	}
	return (x % n);
};


