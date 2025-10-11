#include <iostream>

#define UNIQUE 1; #undef UNIQUE; #define UNIQUE 2

int main()
{
    std::cout << 1 + UNIQUE;
    std::cout << '\n';
}
