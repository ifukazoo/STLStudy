#include <ctime>
#include <cstdio>
#include <cstdlib>

#include <string>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <functional>
#include <iterator>

#include "algorithms.h"
#include "functors.h"
#include "functions.h"

inline void print_sep(int n);

int main()
{
  RandomGenerator my_rand(static_cast<unsigned>(time(NULL)), 10);
  std::string months[] = { "January", "February", "March", "April", "May",
    "June", "July", "August", "September", "October", "November", "December" };

  // 要素を生成する
  {
    std::vector<std::string> v(months, months + array_length(months));
    std::list<std::string>   l(months, months + array_length(months));
    std::deque<std::string>  d(months, months + array_length(months));
    print_container(v.begin(), v.end());
    print_container(l.begin(), l.end());
    print_container(d.begin(), d.end());
  }
  {
    std::vector<int> v(10);
    generate(v.begin(), v.end(), my_rand);
    print_container(v.begin(), v.end());
  }
  {
    std::list<int> l(10);
    generate(l.begin(), l.end(), my_rand);
    print_container(l.begin(), l.end());
  }
  {
    std::deque<int> d(10);
    generate(d.begin(), d.end(), my_rand);
    print_container(d.begin(), d.end());
  }
  print_sep(__LINE__);

  // 代入できる
  {
    std::vector<std::string> v(months, months + array_length(months));
    std::list<std::string>   l(months, months + array_length(months));
    std::deque<std::string>  d(months, months + array_length(months));
    std::vector<std::string> v2 = v;
    std::list<std::string>   l2 = l;
    std::deque<std::string>  d2 = d;
    print_container(v2.begin(), v2.end());
    print_container(l2.begin(), l2.end());
    print_container(d2.begin(), d2.end());
  }
  print_sep(__LINE__);

  // 各要素に適用する
  {
    std::vector<std::string> v(months, months + array_length(months));
    for_each(v.begin(), v.end(), Print());
    std::cout << std::endl;
  }
  print_sep(__LINE__);

  // 数える
  {
    std::vector<int> v(10);
    generate(v.begin(), v.end(), my_rand);
    print_container(v.begin(), v.end());
    int zero = count(v.begin(), v.end(), 0);
    std::cout << "0:" << zero << std::endl;
  }
  {
    std::vector<std::string> v(months, months + array_length(months));
    int gt7 = count_if(v.begin(), v.end(), GT(7));
    std::cout << "greater than 7:" << gt7 << std::endl;
    std::string ending("ber");
    int ber = count_if(v.begin(), v.end(), EndsWith(ending));
    std::cout << "ends with \"ber\":" << ber << std::endl;
  }
  print_sep(__LINE__);

  // 各要素に変更適用 Enumerable#map
  {
    // 適用結果を別コンテナにコピー
    std::vector<int> v(10);
    generate(v.begin(), v.end(), my_rand);
    print_container(v.begin(), v.end());

    //// insert iteratorを使って第2vectorの要素数を自動的に確保
    std::vector<int> v2;
    transform(v.begin(), v.end(), inserter(v2, v2.begin()), Square());
    print_container(v2.begin(), v2.end());

    //// vector -> list
    ///  back_inserter も
    std::list<int> l;
    transform(v.begin(), v.end(), back_inserter(l), Square());
    print_container(l.begin(), l.end());

    //// list -> deque
    ///  back_inserter も
    std::deque<int> d;
    transform(l.begin(), l.end(), back_inserter(d), Square());
    print_container(d.begin(), d.end());

    //// 元コンテナの上書き
    transform(v.begin(), v.end(), v.begin(), Square());
    print_container(v.begin(), v.end());

  }
  {
    //// string
    std::deque<std::string> d(months, months + array_length(months));
    std::vector<std::string> v;
    transform(d.begin(), d.end(), back_inserter(v), ToUpper());
    print_container(v.begin(), v.end());

    // 大きくなったvectorをフィットさせる
    {
      std::cout << "capacity:" << v.capacity() << std::endl;
      std::vector<std::string>(v).swap(v);
      std::cout << "capacity:" << v.capacity() << std::endl;
    }
  }
  print_sep(__LINE__);

  // コピー
  {
    std::list<std::string> l(10);
    fill(l.begin(), l.end(), "hello");
    print_container(l.begin(), l.end());

    // list -> vector
    std::vector<std::string> v;
    copy(l.begin(), l.end(), inserter(v, v.begin()));
    print_container(v.begin(), v.end());
  }
  print_sep(__LINE__);

  // inject
  {
    int ten[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v(ten, ten + array_length(ten));
    print_container(v.begin(), v.end());
    int sum = for_each(v.begin(), v.end(), Sum<int>());
    std::cout << "sum:" << sum << std::endl;
  }
  {
    int ten[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v(ten, ten + array_length(ten));
    print_container(v.begin(), v.end());
    int sum = accumulate(v.begin(), v.end(), 0, Sum2<int>());
    std::cout << "sum:" << sum << std::endl;
  }
  print_sep(__LINE__);

  // バインダ
  {
    // 2項関数をとるalgorithmを1項関数のように振る舞わせる．
    std::list<int> l(10);
    generate(l.begin(), l.end(), my_rand);
    print_container(l.begin(), l.end());

    // greaterの第2引数に常時5がバインドされる．
    std::list<int> v;
    copy_if(l.begin(), l.end(), back_inserter(v),
        std::bind2nd(std::greater<int>(), 5));
    print_container(v.begin(), v.end());
  }
  {
    std::vector<int> v(10);
    generate(v.begin(), v.end(), my_rand);
    print_container(v.begin(), v.end());

    std::vector<int>::iterator last =
      remove_if(v.begin(), v.end(), std::bind2nd(std::greater<int>(), 5));
    std::vector<int> newone(v.begin(), last);
    std::cout << "size:" << newone.size() << std::endl;
  }
  print_sep(__LINE__);

  // Enumerable#select 的な動作
  {
    std::vector<std::string> v(months, months + array_length(months));
    std::list<std::string> l;
    std::string ending("ber");
    copy_if(v.begin(), v.end(), back_inserter(l), EndsWith(ending));
    print_container(l.begin(), l.end());
  }
  print_sep(__LINE__);

  // list でのremove
  {
    // vector や deque と異なりメンバ関数を使える
    std::list<std::string> l(months, months + array_length(months));
    std::string ending("ber");
    l.remove_if(EndsWith(ending));
    print_container(l.begin(), l.end());
    std::cout << "size:" << l.size() << std::endl;
  }
  {
    // アルゴリズムも使えるが，IFが直観的ではないし,
    // サイズも小さくなってはいない
    std::list<std::string> l(months, months + array_length(months));
    std::string ending("ber");
    std::list<std::string>::iterator last =
      remove_if(l.begin(), l.end(), EndsWith(ending));
    print_container(l.begin(), last);
    std::cout << "size:" << l.size() << std::endl;
  }
  print_sep(__LINE__);

  std::cout << __cplusplus << std::endl;
  getchar();

  return 0;
}

inline void print_sep(int n)
{
  std::cout << "========== " << n << " ==========" << std::endl;
}
