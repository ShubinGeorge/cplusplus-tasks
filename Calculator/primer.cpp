#include <iostream>
#include <vector>
#include <utility>

int main()
{
    std::pair<std::string, std::string> data;
    data.first = "qwerty";
    data.second = "qwer";

    std::cout << data.first << " - " << data.second << "\n";
    return 0;
}
