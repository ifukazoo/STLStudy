#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    // 初期化子
    std::vector<std::string> v { "January", "February", "March", "April", "May",
    "June", "July", "August", "September", "October", "November", "December" };

    // lambda
    for_each(v.begin(), v.end(), [](const std::string& s) { std::cout << s << std::endl;} );

    // lambda capture by reference
    int sum = 0;
    std::vector<int> iv { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    for_each(iv.begin(), iv.end(), [&](int n) { sum += n;} );
    std::cout << sum << std::endl;

    // lambda capture by copy
    // copy の場合は const扱いなので基本は変更出来ない
    for_each(iv.begin(), iv.end(), [=](int n) { std::cout << sum + n << std::endl;} );

    // lambda capture by copy and reference
    auto a = 10;
    auto sep = "";
    for_each(iv.begin(), iv.end(), [a, &sep](int n) { std::cout << sep << a + n; sep = ",";} );

    getchar();

    return 0;
}
