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


bool prime[10000000];
#define MAXP 700000
int prime_ke[MAXP];

void generate_sieve() {
	prime[0] = true;
	prime[1] = true;
	prime[2] = false;
	int cnt = 0;
	for(int i = 2; i < 10000000; i++) {
		if (!prime[i]) {
			prime_ke[++cnt] = i;
			for(int j = i+i; j < 10000000; j += i) {
				prime[j] = true;
			}
		}
	}
}

void init() {
	A.push_back(2);
	A.push_back(3);
	A.push_back(5);
	A.push_back(7);
	A.push_back(11);
	A.push_back(13);
	A.push_back(17);
	A.push_back(19);
	A.push_back(23); //9
	generate_sieve();
}

void print(vector<LL> &x) {
	sort(x.begin(), x.end());
	int size = x.size();
	for(int i = 0; i < size; i++) {
		int j;
		int cnt = 1;
		for(j = i+1; j < size; j++) {
			if (x[j] == x[i]) {cnt++;} else break;
		}
		if (i) printf(" * ");
		if (cnt == 1) printf("%lld",x[i]);
		else printf("%lld^%d",x[i],cnt);
		i = j-1;
	}
	printf("\n");
}

inline LL g(LL x, LL mod) {
	if (x >= 1e9) x = fastmul(x, x, mod);
	else x = (x * x) % mod;
	x += 1;
	return x % mod;
}

void factorize(LL N) {
	queue<LL> q;
	vector<LL> result;
	q.push(N);
	while(!q.empty()) {
		LL num = q.front(); q.pop();		
		if (num < 10000000) {
			if (!prime[num]) {
				result.push_back(num);
				continue;
			}
			int sq = sqrt(num);
			if (!prime[sq] && sq*sq == num) {
				result.push_back(sq);
				result.push_back(sq);
				continue;
			} 
			for(int i = 1; i < MAXP; i++) {
				if (num == 1) break;;
				if (!prime[num]) {
					result.push_back(num);
					break;
				}
				while (num % prime_ke[i] == 0) {
					result.push_back(prime_ke[i]);
					num /= prime_ke[i];
				}
			}
			continue;
		}
		
		if (is_prime(num)) {
			result.push_back(num);
			continue;
		}
		LL x = 2, y = 2, d = 1;
		int step = 0;
		int cyc_size = 1;
		int iter = 0;
		while(d == 1) {
			step++;
			x = g(x, num);
			LL k = x - y;
			if (k < 0) k = -k;
			d = __gcd(k, num);
			if (++iter == cyc_size) y = x, cyc_size <<= 1;
			// printf("%lld %lld %lld %d %d\n",x, y, d, iter, cyc_size);
		}
		q.push(d);
		q.push(num/d);
	}
	
	printf("%lld = ",N);
	print(result);
}

void read() {
	int tc; scanf("%d",&tc);
	while (tc--) {
		LL n;
		scanf("%lld",&n);
		factorize(n);
	}
}

int main() {
	init();
	read();
	return 0;
}