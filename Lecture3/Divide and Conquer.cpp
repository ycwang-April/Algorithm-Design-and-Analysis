#include <iostream>
#include <vector>
using namespace std;

// 二分查找
int binary_search(const vector<int>& v, int key,int left,int right)
{
	int middle = (left + right) / 2;
	if (v[middle] == key)
		return middle;
	else if (v[middle] > key)
		return binary_search(v, key, left, middle - 1);
	else
		return binary_search(v, key, middle + 1, right);
}

// 查找最大子数组
int FindCrossSubarray(const vector<int>& v, int left, int right, int mid)
{
	int l_sum = v[mid];
	int r_sum = v[mid+1];
	int l_maxsum = v[mid];
	int r_maxsum = v[mid + 1];
	for (int i = mid-1; i >= left; --i)
	{
		l_sum += v[i];
		l_maxsum = l_maxsum > l_sum ? l_maxsum : l_sum;
	}
	for (int i = mid+2; i <= right; ++i)
	{
		r_sum += v[i];
		r_maxsum = r_maxsum > r_sum ? r_maxsum : r_sum;
	}
	return l_maxsum + r_maxsum;
}

int FindMaxSubarray(const vector<int>& v, int left, int right)  // 使用const引用防止内存爆了
{
	if (left == right)
		return v[left];
	int mid = (left + right) / 2;
	int l_res = FindMaxSubarray(v, left, mid);
	int r_res = FindMaxSubarray(v, mid + 1, right);
	int c_res = FindCrossSubarray(v, left, right, mid);
	int res = l_res > r_res ? l_res : r_res;
	res = res > c_res ? res : c_res;
	return res;
}

int main()
{
	//vector<int> v0 = { 1,2,5,6,9 };
	//int res_ind = binary_search(v0, 6, 0, 4);
	//cout << res_ind;

	vector<int> v0 = { -2,-1 };
	cout << FindMaxSubarray(v0, 0, v0.size() - 1);
}