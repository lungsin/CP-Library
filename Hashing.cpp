// index one base
const int maxn = 5e5+5;
struct HASH{
	ll base[maxn], val[maxn];
	ll mod;
	
	ll hashing(int l, int r){ 
		ll ret = (val[r] - val[l-1]*base[r-l])%mod;
		return (ret+mod)%mod;
	}
	HASH(){}
	void init(string &s, int bse, int mod){
		this->mod = (ll)mod;
		base[0] = bse;
		rep(k,1,s.size()+1) base[k] = base[k-1]*bse%mod;
		rep(k,1,s.size()+1) 
			val[k] = (val[k-1]*base[0] + s[k-1]) % mod;
	}
};