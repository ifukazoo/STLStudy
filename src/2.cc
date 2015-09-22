#include <ctime>

#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

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
  friend std::ostream& operator<<(std::ostream&, const Role*);
  friend bool operator<(const Role& lhs, const Role& rhs);
  friend bool operator==(const Role& lhs, const Role& rhs);
private:
  std::string name_;
};

std::ostream& operator<<(std::ostream& os, const Role* human) {
  std::cout << (human ? human->name_ : "(nil)");
  return os;
}

bool operator<(const Role& lhs, const Role& rhs) {
  return lhs.name_ < rhs.name_;
}
bool operator==(const Role& lhs, const Role& rhs) {
  return lhs.name_ == rhs.name_;
}

int main()
{
  std::string months[] = { "January", "February", "March", "April", "May",
    "June", "July", "August", "September", "October", "November", "December" };

  // ハッシュマップ
  {
    typedef std::unordered_map<int, std::string> MonthMap;
    MonthMap m;

    for (int i = 0; i < 12; i++) {
      m.insert(MonthMap::value_type(i + 1, months[i]));
    }

    {
      // 巡回アクセス
      for (MonthMap::iterator p = m.begin(); p != m.end(); p++) {
        print_key_val(p);
      }
    }
    print_sep(__LINE__);
    // []演算子
    {
      //キーがなければデフォルト作成
      std::string s = m[0];
      print_pair_container(m.begin(), m.end());
    }
    print_sep(__LINE__);
  }
  {
    typedef std::unordered_map<std::string, Role*> ComposerMap;
    ComposerMap m;

    m.insert(ComposerMap::value_type("Italy", new Role("Verdi")));
    m.insert(ComposerMap::value_type("Austria", new Role("Mozart")));
    m.insert(ComposerMap::value_type("Germany", new Role("J.S Bach")));

    {
      // 巡回アクセス
      for (ComposerMap::iterator p = m.begin(); p != m.end(); p++) {
        print_key_val(p);
      }
      print_pair_container(m.begin(), m.end());
      print_sep(__LINE__);
    }
    // []演算子
    {
      std::cout << m["Austria"] << std::endl;
      // // キーが無かったら作成する
      // ポインタ要素のデフォルトはNULL
      std::cout << m["Japan"] << std::endl;
      print_sep(__LINE__);
    }
    struct DeleteMap {
      void operator()(ComposerMap::value_type& p) {
        delete p.second;
        p.second = NULL;
      }
    } delete_map;
    for_each(m.begin(), m.end(), delete_map);
  }
  // set
  {
    // 大文字小文字を区別しないHash, EQを用意する
    // std::unordered_set<std::string, MyHash, HyEq> set;
  }
  {
    struct RolePtrHash {
      size_t operator()(Role* p) const
      {
        std::hash<std::string> hash;
        return hash(p->Name());
      }
    };

    // ポインタコンテナに対する比較関数オブジェクトを指定する
    typedef std::unordered_set<Role*, RolePtrHash, DereferenceEq> RoleHash;
    RoleHash s;
    std::pair<RoleHash::iterator, bool> result;
    s.insert(new Role("figaro"));
    s.insert(new Role("susanna"));
    s.insert(new Role("cherubino"));
    result = s.insert(new Role("figaro")); // 本来は deleteの必要あり
    std::cout << std::boolalpha << result.second << std::endl;
    print_container(s.begin(), s.end());
    std::for_each(s.begin(), s.end(), DeleteObject());
  }
  print_sep(__LINE__);

  getchar();
  return 0;
}
