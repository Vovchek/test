// test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int hIndex(vector<int>& citations) {
		auto i_max = citations.size();
		auto e_min = min_element(citations.begin(), citations.end());
		while (i_max && i_max > *e_min) {
			swap(*e_min, *citations.rbegin());
			citations.resize(--i_max);
			e_min = min_element(citations.begin(), citations.end());
		}
		return static_cast<int>(i_max);
	}
	int hIndexFast(vector<int>& citations) {
		sort(citations.begin(), citations.end());
		auto sz{ citations.size() };
		auto idx{ sz };
		while (idx && idx > citations[sz - idx])
			--idx;
		return static_cast<int>(idx);
	}
};

void sum2(vector<int>& a, int x)
{
	int i = 0;
	int j = lower_bound(a.begin(), a.end(), x) - a.begin();
	while (j >= 0 && j < a.size() && i < a.size()) {
		int sum = a[i] + a[j];
		if (i != j && sum == x) {
			cout << "found: " << a[i] << " + " << a[j] << " = " << x << endl;
			return;
		}
		if (sum > x)    j--;
		else            i++;
		if (i > j) break;
	}
	cout << x << " not found\n";
}

int max(const vector<int>& v)
{
	return *max_element(v.cbegin(), v.cend());
}

int min(const vector<int>& v)
{
	return *min_element(v.cbegin(), v.cend());
}

int max_lower_or_equal(const vector<int>& sorted_arr, int X) {
	// Сначала проверим, существует ли искомый элемент
	if (sorted_arr.empty() || sorted_arr[0] > X)
		return -1;

	size_t left_idx = 0;
	size_t right_idx = sorted_arr.size();
	while (left_idx < right_idx) {
		size_t mid_idx = (left_idx + right_idx) / 2;
		if (sorted_arr[mid_idx] <= X)
			left_idx = mid_idx;
		else
			right_idx = mid_idx;
	}
	return left_idx;
}

// Сигнатура вспомогательной рекурсивной функции
void generate(
	int left_open, // Сколько открывающих скобок ещё можно поставить
	int left_closed, // Сколько закрывающих скобок ещё можно поставить
	string accum, // Текущая последовательность
	vector<string>* result
);

vector<string> generate(int N) {
	// Наша рекурсивная функция ничего не возвращает,
	// вместо этого заполняет результирующий массив
	vector<string> result;

	generate(N, N, "", &result);
	return result;
}

void generate(
	int left_open,
	int left_closed,
	string accum,
	vector<string>* result
) {
	if (!left_open && !left_closed) {
		result->push_back(accum);
		return;
	}
	if (left_open)
		generate(left_open - 1, left_closed, accum + "(", result);
	if (left_closed > left_open)
		generate(left_open, left_closed - 1, accum + ")", result);
}

template<typename T>
T median(T x1, T x2, T x3)
{
	//T t;
	auto swap([](T& a, T& b) { auto t = b; b = a; a = t; });
	if (x1 > x2)
		swap(x1, x2);
	if (x1 > x3)
		swap(x1, x3);
	if (x2 > x3)
		swap(x2, x3);
	return x2;
}

int main()
{
	vector<int> citations = { 3,0,6,1,5 };
	Solution s;

	//std::cout << "nIndex:" << s.hIndex(citations) << '\n';
	//std::cout << "nIndex:" << s.hIndexFast(citations) << '\n';
	/*
	vector<int> a{ 0, 1, 2, 3, 4, 5, 6 };
	for (auto i : a)
		cout << "idx(" << i << ") = " << max_lower_or_equal(a, i) << '\n';

	cout << "idx(" << -1 << ") = " << max_lower_or_equal(a, -1) << '\n';
	cout << "idx(" << 7 << ") = " << max_lower_or_equal(a, 7) << '\n';
	*/

	const auto bs{ generate(4) };
	for (auto& s : bs)
		cout << s << '\n';

	cout << "Median(2, 5, 3) = " << median<int>(2, 5, 3) << '\n';
}

