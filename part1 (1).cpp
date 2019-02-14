#include <iostream>
#include <vector>
#include <string>
#include <map>

template <typename T, int repeat>
void Repeat(const T& arg)
{
    for(int i = 0; i < repeat; i++)
    {
        std::cout << arg << "\n";
    }
}


template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vector)
{
    os << "[";
    for(int i = 0; i < vector.size(); i++)
    {
        os << vector[i];
        if(i != vector.size() -1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}


template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, const std::map<Key, Value>& map)
{
/*
    for(std::map<Key, Value>::iterator it = map.begin();it != map.end(); it++)
    {
        os << it->first << " " << it->second << "\n";
    }
*/
    for(auto it = map.begin(); it != map.end(); it++)
    {
        os << "[" << it->first << ":" << it->second << "]\n";
    }

    return os;
}


int main()
{
    std::map<std::string, int> points;
    points.insert(std::pair<std::string, int> ("first", 1));
    points.insert(std::pair<std::string, int> ("second", 2));
    points.insert(std::pair<std::string, int> ("third", 3));
    std::cout << points;

    std::map<char, int> unicode;
    unicode.insert(std::pair<char, int> ('@', 40));
    unicode.insert(std::pair<char, int> ('A', 41));
    unicode.insert(std::pair<char, int> ('B', 42));
    std::cout << unicode;

    std::cout << "-----------" << "\n";

    std::string test = "I am working";
    Repeat<std::string, 5>(test);

    int digit = 1260;
    Repeat<int, 5>(digit);

    std::cout << "-----------" << "\n";

    std::vector<int> numbers;
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);
    numbers.push_back(4);
    std::cout << numbers << "\n";

    std::vector<char> symbols;
    symbols.push_back('O');
    symbols.push_back('T');
    symbols.push_back('L');
    std::cout << symbols << "\n";


    return 0;
}