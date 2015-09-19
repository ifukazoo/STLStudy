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

int main()
{
  RandomGenerator my_rand(static_cast<unsigned>(time(NULL)), 10);
  std::string months[] = { "January", "February", "March", "April", "May",
    "June", "July", "August", "September", "October", "November", "December" };


  {
    // 要素を生成する
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

  // 各要素に適用する
  {
    std::vector<std::string> v(months, months + array_length(months));
    // 適用関数をリファレンス引数にすることで，破壊的な関数として扱える
    for_each(v.begin(), v.end(), ToUpper());
    print_container(v.begin(), v.end());
  }

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

  // 各要素に変更適用
  {
    // 適用結果を別コンテナにコピー
    std::vector<int> v(10);
    generate(v.begin(), v.end(), my_rand);
    print_container(v.begin(), v.end());

    //// insert iteratorを使って第2vectorの要素数を自動的に確保
    std::vector<int> v2;
    transform(v.begin(), v.end(), inserter(v2, v2.begin()), Square());
    print_container(v2.begin(), v2.end());

    //// vector -> list もできる
    ///  back_inserter も
    std::list<int> l;
    transform(v.begin(), v.end(), back_inserter(l), Square());
    print_container(l.begin(), l.end());

    //// 元コンテナの上書き
    transform(v.begin(), v.end(), v.begin(), Square());
    print_container(v.begin(), v.end());
  }

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

  // Enumerable#select 的な動作
  {
    std::vector<std::string> v(months, months + array_length(months));
    std::list<std::string> l;
        std::string ending("ber");
    copy_if(v.begin(), v.end(), back_inserter(l), EndsWith(ending));
    print_container(l.begin(), l.end());
  }

  getchar();

  return 0;
}
