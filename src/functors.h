#ifndef _FUNCTORS_H_
#define _FUNCTORS_H_


//
// 関数オブジェクト
//
// struct とすることで "public:" を書く必要がない

struct RandomGenerator {
  RandomGenerator(unsigned int seed, int div) : div_(div) {
    srand(seed);
  }
  int operator()() {
    return rand() % div_;
  }
  int div_;
};

struct EndsWith {
  EndsWith(std::string& ending) :ending_(ending){}
  bool operator()(std::string& s) {
    if (ending_.size() > s.size()) return false;
    return std::equal(ending_.rbegin(),  ending_.rend(),  s.rbegin());
  }
  std::string& ending_;
};

struct GT: public std::unary_function<std::string, bool> {
  GT(size_t n) :n_(n){}
  size_t n_;
  result_type operator()(argument_type s) {
    return static_cast<result_type>(s.size() > n_);
  }
};

struct ToUpper {
  void operator()(std::string& s) {
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
  }
};

struct Square {
  int operator()(int n) {
    return n * n;
  }
};

template<typename T>
struct Sum {
  Sum():sum_(0){};
  void operator()(T& val) {
    sum_ += val;
  }
  operator T () {
    return static_cast<T>(sum_);
  }
  T sum_;
};
template<typename T>
struct Sum2 {
  T operator()(T lhs, T rhs) {
    return lhs + rhs;
  }
};

struct GetLength
{
  int operator()(std::string s) {
    return s.size();
  }
};

struct IsEight {
  bool operator()(int n) {
    return n == 8;
  }
};



struct IsEven: public std::unary_function<int, bool> {
  result_type operator()(argument_type i) {
    return static_cast<result_type>(i % 2 == 0);
  }
};

struct Print {
  template<typename T>
  void operator()(T val) {
    std::cout << val << " ";
  }
};


#endif
