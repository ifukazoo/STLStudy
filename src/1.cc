#include <ctime>
#include <cstdio>
#include <cstdlib>

#include <string>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <functional>
#include <iterator>

#include "algorithms.h"
#include "functors.h"
#include "functions.h"

class Role {
public:
  Role(std::string name) :name_(name) {
    std::cout << "construct of " << name_ << std::endl;
  };
  virtual ~Role() {
    std::cout << "destructoin of " << name_ << std::endl;
  };
  std::string Name() {
    return name_;
  }

  void Bark() {
    std::cout << "My name is "<< name_ << "." << std::endl;
  }

  friend std::ostream& operator<<(std::ostream&, const Role*);
  friend bool operator<(const Role& lhs, const Role& rhs);
private:
  std::string name_;
};

std::ostream& operator<<(std::ostream& os, const Role* human) {
  std::cout << human->name_;
  return os;
}

bool operator<(const Role& lhs, const Role& rhs) {
  return lhs.name_ < rhs.name_;
}

class Child :public Role {
public:
  Child(std::string name) :Role(name) {
  };
  virtual ~Child() {
    std::cout << "child destructoin => ";
  };
};

static void TestBark(Role role)
{
  role.Bark();
}

int main()
{
  RandomGenerator<int> random_gen;
  random_gen.init(static_cast<unsigned>(time(NULL)), 10);
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
    generate(v.begin(), v.end(), random_gen);
    print_container(v.begin(), v.end());
  }
  {
    std::list<int> l(10);
    generate(l.begin(), l.end(), random_gen);
    print_container(l.begin(), l.end());
  }
  {
    std::deque<int> d(10);
    generate(d.begin(), d.end(), random_gen);
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
    generate(v.begin(), v.end(), random_gen);
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
    generate(v.begin(), v.end(), random_gen);
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
    std::vector<int> v(10);
    generate(v.begin(), v.end(), random_gen);
    print_container(v.begin(), v.end());

    //// referenceを使用する関数オブジェクト + for_each
    for_each(v.begin(), v.end(), AddSome<10>());
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
  {
    // 単一要素メンバ関数より範囲メンバ関数を使おう
    std::list<std::string> l(10);
    fill(l.begin(), l.end(), "hello");
    print_container(l.begin(), l.end());

    // list -> vector
    std::vector<std::string> v;
    //// assign 素晴らしい
    v.assign(l.begin(), l.end());
    print_container(v.begin(), v.end());

    std::vector<std::string> v2;
    v2.push_back("Ya");
    v2.push_back("today.");
    v2.insert(v2.begin() + 1, l.begin(), l.end());
    print_container(v2.begin(), v2.end());
  }
  print_sep(__LINE__);

  // inject
  {
    int ten[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v(ten, ten + array_length(ten));
    print_container(v.begin(), v.end());
    int sum = accumulate(v.begin(), v.end(), 0, Sum());
    std::cout << "sum:" << sum << std::endl;
  }
  print_sep(__LINE__);

  // バインダ
  {
    // 2項関数をとるalgorithmを1項関数のように振る舞わせる．
    std::list<int> l(10);
    generate(l.begin(), l.end(), random_gen);
    print_container(l.begin(), l.end());

    // greaterの第2引数に常時5がバインドされる．
    std::list<int> v;
    copy_if(l.begin(), l.end(), back_inserter(v),
        std::bind2nd(std::greater<int>(), 5));
    print_container(v.begin(), v.end());
  }
  {
    std::vector<int> v(10);
    generate(v.begin(), v.end(), random_gen);
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

  // コンテナ内のオブジェクトをdeleteする
  {
    std::vector<Role*> v;
    v.push_back(new Role("figaro"));
    v.push_back(new Role("susanna"));
    v.push_back(new Child("cherubino"));
    print_container(v.begin(), v.end());
    for_each(v.begin(), v.end(), DeleteObject());
    // for_eachが非常に役に立っている!!
  }
  print_sep(__LINE__);

  // 要素の削除
  {
    std::vector<int> v(10);
    std::deque<int> d(10);
    std::list<int> l(10);
    generate(v.begin(), v.end(), random_gen);
    generate(d.begin(), d.end(), random_gen);
    generate(l.begin(), l.end(), random_gen);
    print_container(v.begin(), v.end());
    print_container(d.begin(), d.end());
    print_container(l.begin(), l.end());

    v.erase(remove(v.begin(), v.end(), 0), v.end());
    d.erase(remove(d.begin(), d.end(), 0), d.end());
    l.remove(0);

    print_container(v.begin(), v.end());
    print_container(d.begin(), d.end());
    print_container(l.begin(), l.end());

    v.erase(remove_if(v.begin(), v.end(), std::bind2nd(std::greater<int>(), 5)), v.end());
    d.erase(remove_if(d.begin(), d.end(), std::bind2nd(std::greater<int>(), 5)), d.end());
    l.remove_if(std::bind2nd(std::greater<int>(), 5));

    print_container(v.begin(), v.end());
    print_container(d.begin(), d.end());
    print_container(l.begin(), l.end());
  }
  {
    // 削除しながら処理がある場合
    // deque, listも同じ形式でできる
    std::vector<Role*> v;
    v.push_back(new Role("figaro"));
    v.push_back(new Role("susanna"));
    v.push_back(new Child("cherubino"));
    std::string ending("o");
    EndsWith ends_with(ending);

    std::vector<Role*>::iterator p = v.begin();
    while (p != v.end()) {
      std::string name = (*p)->Name();
      if (ends_with(name)) {
        delete *p;
        p = v.erase(p);
      } else {
        p++;
      }
    }
    print_container(v.begin(), v.end());
  }
  print_sep(__LINE__);

  // vector と stringを c api に渡す
  {
    std::vector<int> v(10);
    generate(v.begin(), v.end(), random_gen);
    if (!v.empty()) {
      print_array(&v[0], v.size());
    }

    std::string s("STL is great!!");
    printf("%s\n", s.c_str());
  }
  print_sep(__LINE__);

  //連想コンテナ基礎
  {
    RandomGenerator<int> random_gen_alpha;
    random_gen_alpha.init(static_cast<unsigned>(time(NULL)), 11);
    std::map<int, std::string> m;

    // for (int i = 0; i < 12; i++) {
    //   m.insert(std::pair<int, std::string>(i + 1, months[i]));
    // }
    // make_pairを使えば型が不要
    for (int i = 0; i < 12; i++) {
      m.insert(make_pair(i + 1, months[i]));
    }

    {
      int key = random_gen_alpha() + 1;
      std::map<int, std::string>::iterator p = m.find(key);
      if (p != m.end()) {
        print_key_val(p);
      }
    }
    {
      // 巡回アクセス
      for (std::map<int, std::string>::iterator p = m.begin(); p != m.end(); p++) {
        print_key_val(p);
      }
    }
  }
  print_sep(__LINE__);

  // []演算子
  // 挿入はinsertの効率が優れ，更新は[]の効率が優れる．
  {
    // 代入
    std::map<int, std::string> m;
    for (int i = 0; i < 12; i++) {
      m[i + 1] =  months[i];
    }
    print_pair_container(m.begin(), m.end());
  }
  {
    // キーが無かったら作成する
    std::vector<int> v;
    std::vector<std::pair<int, int> > keyvals;
    for (int i = 0; i < 10; i++) {
      v.push_back(i + 1);
    }
    transform(v.begin(), v.end(), back_inserter(keyvals), CreatePair());
    std::map<int, int> m(keyvals.begin(), keyvals.end());
    print_pair_container(m.begin(), m.end());
    int n = m[100];
    std::cout << "n=" << n << std::endl;
    print_pair_container(m.begin(), m.end());
  }
  print_sep(__LINE__);

  // set
  {
    // 大文字小文字を区別しない関数を渡す
    std::set<std::string, CIStringLess> ciss; // 独自Lessを書く
    ciss.insert("Figaro"); ciss.insert("figaro");
    ciss.insert("Susanna"); ciss.insert("susanna");
    ciss.insert("Cherubino"); ciss.insert("cherubino");
    print_container(ciss.begin(), ciss.end());
    //メンバ関数は渡した関数で比較するので混乱はない
    std::cout << std::boolalpha << (ciss.find("figaro") != ciss.end()) << std::endl;
    // findアルゴリズムでは operator== を使うので，falseが返る
    std::cout << std::boolalpha << (std::find(ciss.begin(), ciss.end(), std::string("figaro")) != ciss.end()) << std::endl;
  }
  {
    // ポインタコンテナに対する比較関数オブジェクトを指定する
    std::set<Role*, DereferenceLess> s;
    s.insert(new Role("figaro"));
    s.insert(new Role("susanna"));
    s.insert(new Child("cherubino"));
    print_container(s.begin(), s.end());
    for_each(s.begin(), s.end(), DeleteObject());
  }
  print_sep(__LINE__);

  // ptr_fun, mem_fun, mem_fun_refについて
  {
    {
      Role roles[] = {
        Role("figaro"),
        Role("susanna"),
        Child("cherubino"),
      };
      std::vector<Role> v(roles, roles + array_length(roles));

      // ptr_fun
      //// 関数を関数オブジェクトに変換する
      //// for_eachは関数も利用できるので，ここでのptr_funはなくてもコンパイルできる
      for_each(v.begin(), v.end(), std::ptr_fun(TestBark));
      print_sep(__LINE__);

      // mem_fun_ref
      //// メンバ関数を参照を受け取る関数オブジェクトに変換する
      for_each(v.begin(), v.end(), std::mem_fun_ref(&Role::Bark));
      print_sep(__LINE__);
    }
    {
      Role* roles[] = {
        new Role("figaro"),
        new Role("susanna"),
        new Child("cherubino"),
      };
      std::vector<Role*> v(roles, roles + array_length(roles));

      // mem_fun
      //// メンバ関数をポインタを受け取る関数オブジェクトに変換する
      for_each(v.begin(), v.end(), std::mem_fun(&Role::Bark));
      for_each(v.begin(), v.end(), DeleteObject());
      print_sep(__LINE__);
    }
  }
  std::cout << __cplusplus << std::endl;
  getchar();

  return 0;
}

