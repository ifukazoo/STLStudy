#include <ctime>
#include <cstdio>
#include <cstdlib>

#include <string>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
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
    std::vector<std::string> v(months, months + sizeof(months) / sizeof(months[0]));
    std::list<std::string>   l(months, months + sizeof(months) / sizeof(months[0]));
    std::deque<std::string>  d(months, months + sizeof(months) / sizeof(months[0]));
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
    std::vector<std::string> v(months, months + sizeof(months) / sizeof(months[0]));
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
    std::vector<std::string> v(months, months + sizeof(months) / sizeof(months[0]));
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

  // inject map
  {
    int ten[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v(ten, ten + array_length(ten));
    print_container(v.begin(), v.end());
    int sum = for_each(v.begin(), v.end(), Sum<int>());
    std::cout << "sum:" << sum << std::endl;
  }

#if 0
    strs.push_back(s[i]);
  }
  print_container(strs.begin(), strs.end());
  std::vector<int> lens(12);
  transform(strs.begin(), strs.end(), lens.begin(), GetLength());
  print_container(lens.begin(), lens.end());

  // <algorithm>の基底クラスを利用
  std::vector<int> v3(20);
  generate(v3.begin(), v3.end(), my_rand);
  std::cout << "before:";
  print_container(v3.begin(), v3.end());
  int count = count_if(v3.begin(), v3.end(), IsEven());
  std::cout << "even is :" << count << std::endl;

  // バインダ
  // 2項関数をとるalgorithmを1項関数のように振る舞わせる．
  std::vector<int>::iterator p;
  // greaterの第2引数に常時5がバインドされる．
  p = remove_if(v3.begin(), v3.end(), std::bind2nd(std::greater<int>(), 5));
  std::cout << "after:";
  print_container(v3.begin(), p);

  // insert iterator
  std::list<std::string> strv1, strv2;
  strv1.push_back("The");
  strv1.push_back("STL");
  strv1.push_back("are");
  strv1.push_back("powerful.");
  print_container(strv1.begin(), strv1.end());

  strv2.push_back("and");
  strv2.push_back("insert");
  strv2.push_back("iterators");
  print_container(strv2.begin(), strv2.end());

  // 1に2を挿入する
  std::list<std::string>::iterator i = strv1.begin();
  i++; i++;
  copy(strv2.begin(), strv2.end(), inserter(strv1, i));
  print_container(strv1.begin(), strv1.end());

  // 自動で拡張するのでコピー先が空でも大丈夫
  std::list<std::string> strv3;
  copy(strv1.begin(), strv1.end(), inserter(strv3, strv3.begin()));
  print_container(strv3.begin(), strv3.end());

  // 末尾に挿入する２つのやり方
  //   inserter
  copy(strv2.begin(), strv2.end(), inserter(strv1, strv1.end()));
  print_container(strv1.begin(), strv1.end());

  //   back inserter
  copy(strv2.begin(), strv2.end(), back_inserter(strv1));
  print_container(strv1.begin(), strv1.end());

  // 先頭に挿入する２つのやり方
  //   inserter
  copy(strv2.begin(), strv2.end(), inserter(strv1, strv1.begin()));
  print_container(strv1.begin(), strv1.end());

  //   front inserter
  //   ※これは動きが異なる
  copy(strv2.begin(), strv2.end(), front_inserter(strv1));
  print_container(strv1.begin(), strv1.end());


#endif

  getchar();

  return 0;
}
