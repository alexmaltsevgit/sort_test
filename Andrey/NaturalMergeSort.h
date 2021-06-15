#pragma once
#include "ISort.h"
class NaturalMergeSort : public ISort {
private:
  int t[9] = {0};
  int ta = 0;

private:
  void merge_pass(int* x, int* y, int s, int n) {
    int i = 0;
    while (i <= ta - 2 * s) {
      int r = ((i + 2 * s) < ta) ? t[i + 2 * s] : n;

      merge(x, y, t[i], t[i + s] - 1, r - 1);
      i = i + 2 * s;
    }
    if (i + s < ta)
      merge(x, y, t[i], t[i + s] - 1, n - 1);
    else if (i < ta) {
      for (int j = t[i]; j <= n - 1; j++)
        y[j] = x[j];
    }
  }

  void merge(int* c, int* d, int l, int m, int r) {
    int i = l, j = m + 1, k = r;

    while ((i <= m) && (j <= r)) {
      if (c[i] <= c[j])
        d[l++] = c[i++];
      else
        d[l++] = c[j++];
    }
    if (i > m)
      for (int q = j; q <= r; q++)
        d[l++] = c[q];
    else
      for (int p = i; p <= m; p++)
        d[l++] = c[p];
  }

  void get_bpoint(int* a, int* b, int n, int& m) {
    int j = 0;
    b[j++] = 0;
    for (int i = 0; i < n - 1; i++) {
      if (a[i + 1] < a[i])
        b[j++] = i + 1;
    }
    m = j;
  }

public:
	NaturalMergeSort() {
		name = "СОРТИРОВКА ЕСТЕСТВЕННЫМ СЛИЯНИЕМ";
	}

	virtual void operator()(int* array, const size_t length) override {
    int t[9];
    int ta;

    get_bpoint(array, t, length, ta);

    int* b = new int[length];
    int s = 1;
    while (s < ta) {
      merge_pass(array, b, s, length);
      s += s;
      merge_pass(b, array, s, length);
      s += s;
    }
	}
};
