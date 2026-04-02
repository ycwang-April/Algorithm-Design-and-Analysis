#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void heapadjust(vector<int>& v, int n, int index)
{
	int largest = index;
	int lchild_ind = 2 * index + 1;
	int rchild_ind = 2 * index + 2;
	if (lchild_ind < n && v[lchild_ind] > v[largest])  // 左子节点存在且大于largest
		largest = lchild_ind;
	if (rchild_ind < n && v[rchild_ind] > v[largest])  // 右子节点存在且大于largest
		largest = rchild_ind;

	if (largest != index)
	{
		swap(v[largest], v[index]);
		heapadjust(v, n, largest); // 调整被交换的子树
	}
}

void buildheap(vector<int>& v)
{
	int n = v.size();
	for (int i = n / 2 - 1; i >= 0; --i) // 最后一个非叶子节点为n/2-1
		heapadjust(v, n, i);
}


void heapSort(vector<int>& v)
{
	int n = v.size();
	buildheap(v);
	for (int i = n - 1; i > 0; --i)
	{
		swap(v[0], v[i]);
		heapadjust(v, i, 0);
	}
}

vector<int> CountingSort(const vector<int>& v,int k) // 输入数组v的元素均为正整数，且最大值为k
{
	int n = v.size();
	vector<int> res(n);
	vector<int> aux(k + 1);
	for (int i = 0; i < n; ++i)
		aux[v[i]]++;  // 这里-1是因为vector下标从0开始
	for (int i = 2; i <= k; ++i)
		aux[i] += aux[i - 1];
	for (int i = n - 1; i >= 0; --i)
	{
		res[aux[v[i]]-1] = v[i];
		aux[v[i]]--;
	}
	return res;
}


int main()
{
	vector<int> vi = { 6,5,1,9,3 };
	//cout << "Before heapSort:" << endl;
	//for (auto x : vi)
	//	cout << x << " ";
	//cout << endl;
	//heapSort(vi);
	//cout << "After heapSort:" << endl;
	//for (auto x : vi)
	//	cout << x << " ";
	//cout << endl;
	
	cout << "Before CountingSort:" << endl;
	for (auto x : vi)
		cout << x << " ";
	cout << endl;
	int maxval = *max_element(vi.begin(), vi.end());
	vector<int> res = CountingSort(vi,maxval);
	cout << "After CountingSort:" << endl;
	for (auto x : res)
		cout << x << " ";
	cout << endl;
	
	
	return 0;
}