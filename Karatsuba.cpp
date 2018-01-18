void karatsuba(long long int *res, const long long int *p, const long long int *q, int sz)
{
	long long int tmp_0[sz];
	long long int tmp_1[sz];
	long long int r[sz << 1];
	
	for (int i = 0; i < 2*sz; i++)
		r[i] = 0;
	if (sz <= 4)
	{
		for (int i = 0; i < sz; i++)
			for (int j = 0; j < sz; j++)
				r[i+j] += p[i]*q[j];
	}
	else
	{
		int sz_half = sz/2;
		for (int i = 0; i < sz_half; i++)
		{
			tmp_0[i] = p[i] + p[sz_half + i];
			tmp_1[i] = q[i] + q[sz_half + i];
			tmp_0[i + sz_half] = 0;
			tmp_1[i + sz_half] = 0;
		}
		karatsuba(r + sz_half, tmp_0, tmp_1, sz_half);
		karatsuba(tmp_0, p, q, sz_half);
		karatsuba(tmp_1, p+sz_half, q+sz_half, sz_half);
		for (int i = 0; i < sz; i++)
		{
			r[i] += tmp_0[i];
			r[i + sz_half] -= tmp_0[i] + tmp_1[i];
			r[i + sz] += tmp_1[i];
		}
	}
    
    for (int i = 0; i < 2*sz; i++)
    	res[i] = r[i];
}

void fast_polymult(long long int *ans, long long int *p, long long int *q, int sz)
{
	if (sz & (sz - 1))
	{
		int k = 1;
		while (k < sz)
			k *= 2;
		while (sz+1 <= k)
		{
			p[sz] = 0;
			q[sz] = 0;
			sz++;
		}
	}
	karatsuba(ans, p, q, sz);
}