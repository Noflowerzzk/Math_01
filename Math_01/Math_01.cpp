#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define INT long long unsigned int

using namespace std;

INT sum = 0;
vector<int> list;

INT fac(int n) { // 阶乘
	INT f = 1;
	for (int i = 1; i < n + 1; i++)
		f *= i;
	return f;
}

inline INT Combi(int n, int m) { // 组合数
	return fac(n) / (fac(m) * fac(n - m));
}

INT Circle(int n) {  // 算每个n成一个环种类数
	return static_cast<INT>(exp2(static_cast<double>(n - 1))) * fac(n - 1);
}

INT Choose(int n, int m) {   // 可重复组合
	INT _sum = 0;
	for (int i = 1; i <= min(n, m); i++)
		_sum += Combi(m, i) * ((n > i) ? Combi(n - 1, i - 1) : 1);
	return _sum;
}

INT CountList() { // 算每个列表总环数
	INT _sum = 0;
	int temp = 0;

	for (auto i : list) {
		if (i == temp)
			continue;
		int rp = count(list.begin(), list.end(), i);
		// 重复时。。。可重复组合
		_sum += Choose(rp, Circle(i));
		temp = i;
	}

	return _sum;
}

void Count(int n, int m) {
	if (m == 1)
	{
		list.push_back(n);
		sum += CountList();
		list.clear();
	}
	else
	{
		for (int i = n - m + 1; i >= (n - m + 2) / 2; i--)
		{
			list.push_back(i);
			Count(n - i, m - 1);
		}
	}
	return;
}

int main()
{
	int NU = 0;
	cout << "Number of ropes:" << '\t';
	//cout << fac(3);
	cin >> NU;
	int TO = fac(2 * NU) / (fac(NU) * exp2(NU));
	//for (int i = 1; i < NU + 1; i++)
	//	TO *= Combi(2 * i, 2);
	// list.push_back(3);
	// Count();
	double check = 0;
	for (int i = 1; i < NU + 1; i++) {
		Count(NU, i);
		cout << "P(X = " << i << ')' << " = " << (double)sum / (double)TO << endl;
		check += (double)sum / (double)TO;
		sum = 0;
	}
	cout << check << endl;

	return 0;
}