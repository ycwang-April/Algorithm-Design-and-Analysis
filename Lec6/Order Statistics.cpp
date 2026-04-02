#include <iostream>
#include <vector>
using namespace std;

void myswap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

int Random_Partition(vector<int>& v, int p, int q)
{
	int pivot = v[p];
	int i = p;
	for (int j = p + 1; j <= q; ++j)
	{
		if (v[j] < pivot)
		{
			i++;
			myswap(v[i], v[j]);
		}
	}
	swap(v[p], v[i]);
	return i;
}

int Random_Select(vector<int>& v, int p, int q, int i)
{
	if (p == q)
		return v[p];
	int r = Random_Partition(v, p, q);
	int k = r - p + 1;
	if (i == k)
		return v[r];
	else if (i < k)
		return Random_Select(v, p, r - 1, i);
	else
		return Random_Select(v, r + 1, q, i - k);
}

int main()
{
	vector<int> v = {-1,1,4,3,9,6 }; // -1占位，使得下标从1开始
	int i = 1;
	int res = Random_Select(v, 1, v.size() - 1, i);
	cout << "第" << i << "大的元素是" << res << endl;
	return 0;
}