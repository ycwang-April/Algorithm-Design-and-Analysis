#include <iostream>
#include <string>
#include <vector>
using namespace std;


int LCS_length(string x, string y, vector<vector<int>>& dp,vector<vector<int>>& aux,int m,int n)
{
	for (int i = 0; i <= m; ++i)
		dp[i][0] = 0;
	for (int j = 0; j <= n; ++j)
		dp[0][j] = 0;
	for (int i = 1; i <= m; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			if (x[i - 1] == y[j - 1])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
				aux[i][j] = 0;
			}
			else
			{
				if (dp[i][j - 1] > dp[i - 1][j])
				{
					dp[i][j] = dp[i][j - 1];
					aux[i][j] = 1;
				}
				else
				{
					dp[i][j] = dp[i - 1][j];
					aux[i][j] = 2;
				}
			}
		}
	}
	return dp[m][n];
}

void LCS_print(string x,const vector<vector<int>>& aux, int i, int j)
{
	if (i == 0 || j == 0)
		return;
	if (aux[i][j] == 0)
	{
		LCS_print(x, aux, i - 1, j - 1);
		cout << x[i - 1];
	}
	else if (aux[i][j] == 1)
		LCS_print(x, aux, i, j - 1);
	else
		LCS_print(x, aux, i - 1, j);
}

void LCS(string x, string y)
{
	int m = x.size();
	int n = y.size();
	vector<vector<int>> dp(m + 1, vector<int>(n + 1));
	vector<vector<int>> aux(m + 1, vector<int>(n + 1));  // 辅助信息，0代表对角线,1代表左，2代表上
	int max_length = LCS_length(x,y,dp,aux,m,n);
	cout << "最长公共子序列的长度为" << max_length << endl;
	LCS_print(x, aux, m, n);
}

int main()
{
	string x = "ABCBDAB";
	string y = "BDCABA";
	LCS(x, y);
	return 0;
}