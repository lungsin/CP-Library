const int maxn = 1e7+7;
int lp[maxn],mobius[maxn];
vector<int> prime;

void build_sieve() {
	lp[1] = 1;
	for (int k = 2; k < maxn; k++) {
		if(lp[k]==0)prime.pb(k), lp[k] = k;
		for(auto a : prime){
			if(a>lp[k] || a*k>=maxn)break;
			lp[a*k] = a;
		}
	}
}

void build_mobius_sieve() {
	mobius[1] = lp[1] = 1;
	for (int k = 2; k < maxn; k++) {
		if(lp[k]==0)prime.pb(k), lp[k] = k;
		
		for(auto a : prime){
			if(a>lp[k] || a*k>=maxn)break;
			lp[a*k] = a;
		}
		
		if(lp[k]==k)mobius[k] = -1;
		else if(k/lp[k]%lp[k]==0)mobius[k] = 0;
		else mobius[k] = mobius[k/lp[k]]*mobius[lp[k]];
	}
}

