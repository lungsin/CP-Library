// Randomized Primality Test (Miller-Rabin):
//   Error rate: 2^(-TRIAL)
//   Almost constant time. srand is needed

#include <stdlib.h>

#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define f first
#define s second
#define mp make_pair

vector<LL> A; // store prime from 2..23 (there are 9 prime)
// if n < 3,825,123,056,546,413,051 (3*10^18), it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, and 23.
inline LL fastmul(LL a, LL b, LL n) {
    LL ret = 0;
    while (b) {
        if (b & 1) ret = (ret + a) % n;
        a = (a + a) % n;
        b >>= 1;
    }
    return ret;
}

inline LL fastexp(LL a, LL b, LL n) {//compute (a^b) mod n
    LL ret = 1;
    while (b) {
        if (b & 1) ret = fastmul(ret, a, n);
		a = fastmul(a, a, n);
        b >>= 1;
    }
    return ret;
}

bool miller_test(LL n, LL s, LL d, LL a) {
	LL as = fastexp(a, s, n); //as = a^s mod n
	if(as == 1 || as == n-1) return true;
	for(int r = 1; r <= d-1; r++) {
		as = fastmul(as, as, n); // as = as^2 mod n
		if (as == 1) return false;
		if (as == n-1) return true;
	}
	return false;
}

inline bool is_prime(LL n) {
	if(n == 2) return true;
    if(n == 1 || (n % 2 == 0)) return false;
    LL s = n-1, d = 0;
    while(s % 2 == 0) {
		d++, s /= 2;
    }
	int idx;
	if (n <= 1000000) idx = 5;
	else if (n <= 100000000) idx = 7;
	else idx = 9;
    for(int j = 0; j < idx; j++) {
		if (A[j] >= n) break;
		if (!miller_test(n, s, d, A[j])) 
			return false;
    }
    return true;
}