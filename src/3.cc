#include <ctime>
#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <vector>
#include <algorithm>
#include "functions.h"

template <typename T>
class RandomGenerator {
public:
  void init(unsigned int seed, T div) {
    div_ = div;
    srand(seed);
  }

  T operator()() {
    int num = rand() % static_cast<int>(div_);
    return static_cast<T>(num);
  }
private:
  T div_;
};

inline int cmp_double_f(double l, double r)
{
  return l > r;
}
inline int cmp_double(const void* l, const void* r)
{
  return static_cast<int>(*(static_cast<const double*>(l)) - *(static_cast<const double*>(r)));
}

int main()
{
  RandomGenerator<double> random_gen;
  random_gen.init(static_cast<unsigned>(time(NULL)), 65535.0);

  std::vector<double> org(1000000);
  generate(org.begin(), org.end(), random_gen);

  {
    std::vector<double> copy = org;
    clock_t begin = clock();
    sort(copy.begin(), copy.end(), std::greater<double>());
    clock_t end = clock();
    std::cout << (end - begin) << std::endl;
    // print_array(&copy[0], copy.size());
    // getchar();
  }
  {
    std::vector<double> copy = org;
    clock_t begin = clock();
    sort(copy.begin(), copy.end(), cmp_double_f);
    clock_t end = clock();
    std::cout << (end - begin) << std::endl;
    // print_array(&copy[0], copy.size());
    // getchar();
  }

  {
    std::vector<double> copy = org;
    clock_t begin = clock();
    qsort(&copy[0], copy.size(), sizeof(double), cmp_double);
    clock_t end = clock();
    std::cout << (end - begin) << std::endl;
    // print_array(&copy[0], copy.size());
    // getchar();
  }

  return 0;
}
