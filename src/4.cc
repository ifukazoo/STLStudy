#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    // 初期化子
    std::vector<std::string> v { "January", "February", "March", "April", "May",
    "June", "July", "August", "September", "October", "November", "December" };

    for_each(v.begin(), v.end(), [](const std::string& s) { std::cout << s << std::endl;} );

    return 0;
}
