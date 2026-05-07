#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define inf 142857

void MCM(vector<vector<int>>& m, vector<vector<int>>& s, const vector<int>& p)
{
	int n = p.size() - 1;
	for (int i = 1; i <= n; ++i)
		m[i][i] = 0;
	for (int L = 2; L <= n; ++L)
	{
		for (int i = 1; i <= n - L + 1;++i)
		{
			int j = i + L - 1;
			m[i][j] = inf;
			for (int k = i; k < j; ++k)
			{
				int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (q < m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
}

void MCMtest()
{
	vector<int> p = { 5,4,6,2,7 };
	int n = p.size() - 1;
	vector<vector<int>> m(n + 1, vector<int>(n + 1));
	vector<vector<int>> s(n + 1, vector<int>(n + 1));
	MCM(m, s, p);
	for (int i = 1; i <= n; ++i)
	{
		for (int j = i; j <= n; ++j)
			cout << "m[" << i << "]" << "[" << j << "]: " << m[i][j] << endl;
	}
	for (int i = 1; i <= n; ++i)
	{
		for (int j = i + 1; j <= n; ++j)
			cout << "s[" << i << "]" << "[" << j << "]: " << s[i][j] << endl;
	}
}

void _01dp(vector<int> value, vector<int> weight,int w)
{
	int n = value.size() - 1;
	vector<vector<int>> dp(n+1, vector<int>(w+1));
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= w; ++j)
		{
			if (j - weight[i] < 0)
				dp[i][j] = dp[i - 1][j];
			else
				dp[i][j] = max(dp[i - 1][j],dp[i - 1][j - weight[i]] + value[i]);
		}
	}
	cout << dp[n][w] << endl;
}

void dptest()
{
	vector<int> value = { 0,10,40,30,50 };
	vector<int> weight = { 0,5,4,6,3 };
	int w = 10;
	_01dp(value, weight, w);
}

int main()
{
	//MCMtest();
	dptest();
	return 0;
}