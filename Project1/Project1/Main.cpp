#include <iostream>

class My_class {
public:
    My_class() {}
    My_class(int a) : a(a) {}
    ~My_class()
    {
        std::cout << "destroyed\n";
    }

    int a = 1;
};

int main()
{
    My_class c;
    if (c.a) {
        c = My_class(25);
    }

    std::cout << c.a;
    std::cin.get();
    return 0;
}