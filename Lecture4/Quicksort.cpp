#include <iostream>
#include <vector>
using namespace std;

void myswap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

// 划分方式1：取第一个为pivot
int Partition1(vector<int>& v, int p, int q)
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
	myswap(v[p], v[i]);
	return i;
}

// 划分方式2：取中间为pivot
int Partition2(vector<int>& v, int p, int q)
{
	int mid = (p + q) / 2;
	int pivot = v[mid];
	int i = p;
	int j = q;
	while (i <= j)
	{
		while (v[i] < pivot) i++;
		while (v[j] > pivot) j--;  // 注意：这里加等于号容易越界
		if (i <= j)
		{
			myswap(v[i], v[j]);
			i++;
			j--;
		}
	}
	return i;
}

// 划分方式3:取最后一个为pivot
int Partition3(vector<int>& v, int p, int q)
{
	int pivot = v[q];
	int i = q;
	for (int j = q - 1; j >= p; --j)
	{
		if (v[j] > pivot)
		{
			i--;
			myswap(v[i], v[j]);
		}
	}
	myswap(v[i], v[q]);
	return i;
}

// 快速排序
void Quicksort(vector<int>& v,int p, int q)
{
	if (p >= q)
		return;   // 递归别漏了终止条件
	//int pivot_index = Partition1(v, p, q);
	//Quicksort(v, p, pivot_index - 1);
	//Quicksort(v, pivot_index + 1, q);

	int pivot_index = Partition2(v, p, q);
	Quicksort(v, p, pivot_index - 1);
	Quicksort(v, pivot_index , q);
}

int main()
{
	vector<int> vi = { 6,5,1,9,3 };
	cout << "Before Quicksort:" << endl;
	for (auto x : vi)
		cout << x << " ";
	cout << endl;
	Quicksort(vi, 0, vi.size() - 1);
	cout << "After Quicksort:" << endl;
	for (auto x : vi)
		cout << x << " ";
	cout << endl;
	return 0;
}