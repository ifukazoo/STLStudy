#include <iostream>
#include <random>
#include <future>

bool is_three_seven(int seed)
{
    std::mt19937 mt(seed);
    for (int i = 0; i < 100; i++) {
        auto n = mt() % 100UL;
        if (n == 777) {
            return true;
        }
    }
    return false;
}
int main()
{
    std::random_device rnd;
    auto future1  = std::async(is_three_seven, rnd());
    auto future2  = std::async(is_three_seven, rnd());
    auto future3  = std::async(is_three_seven, rnd());
    auto future4  = std::async(is_three_seven, rnd());
    auto future5  = std::async(is_three_seven, rnd());
    auto future6  = std::async(is_three_seven, rnd());
    auto future7  = std::async(is_three_seven, rnd());
    auto future8  = std::async(is_three_seven, rnd());
    auto future9  = std::async(is_three_seven, rnd());
    auto future10 = std::async(is_three_seven, rnd());
    std::cout << 1  << ":" << future1.get() << std::endl;
    std::cout << 2  << ":" << future2.get() << std::endl;
    std::cout << 3  << ":" << future3.get() << std::endl;
    std::cout << 4  << ":" << future4.get() << std::endl;
    std::cout << 5  << ":" << future5.get() << std::endl;
    std::cout << 6  << ":" << future6.get() << std::endl;
    std::cout << 7  << ":" << future7.get() << std::endl;
    std::cout << 8  << ":" << future8.get() << std::endl;
    std::cout << 9  << ":" << future9.get() << std::endl;
    std::cout << 10 << ":" << future10.get() << std::endl;

    return 0;
}
