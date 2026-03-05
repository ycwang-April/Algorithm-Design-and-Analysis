#include <iostream>
#include <vector>
using namespace std;
#define inf 142857

void insertion_sort(vector<int>& v)
{
	int i = 0;
	int j = 0;
	for (j = 1; j < v.size(); j++)
	{
		int key = v[j];
		i = j - 1;
		while (i >= 0 && key < v[i])
		{
			v[i + 1] = v[i];
			i--;
		}
		v[i + 1] = key;
	}
}

void merge(vector<int>& v, int p, int q, int r)
{
	vector<int> vl;
	vector<int> vr;
	int n1 = q - p + 1;
	int n2 = r - q;
	for (int i = 0; i < n1; i++)
		vl.push_back(v[p + i]);
	for (int i = 0; i < n2; i++)
		vr.push_back(v[q + 1 + i]);
	vl.push_back(inf);
	vr.push_back(inf);
	int i = 0;
	int j = 0;
	for (int k = p; k <= r; k++)
	{
		if (vl[i] <= vr[j])
		{
			v[k] = vl[i];
			i++;
		}
		else
		{
			v[k] = vr[j];
			j++;
		}
	}
}

void merge_sort(vector<int>& v,int p,int r)
{
	//×¢Òâ:µÝ¹éÖÕÖ¹Ìõ¼þ
	if (p == r)
		return;
	int q = (p + r) / 2;
	merge_sort(v, p, q);
	merge_sort(v, q + 1, r);
	merge(v, p, q, r);
}

int main()
{
	vector<int> v1 = { 4,2,5,7,3 };


	//insertion_sort(v1);
	merge_sort(v1, 0, v1.size() - 1);
	
	for (auto x : v1)
		cout << x << ' ';
	cout << endl;

	return 0;
}