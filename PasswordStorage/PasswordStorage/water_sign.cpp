#include <iostream>
#include <string>
#include <cassert>


std::string GetWaterSign(const std::string& string_to_hide)
{
    std::string water_sign;

    for (size_t i = 0; i < string_to_hide.size(); i++)
    {
        const char curr_character = string_to_hide[i];
        const char first_half = (curr_character & 0xF0) | 0x0E;
        const char second_half = (curr_character & 0x0F) | 0x10;
        water_sign.push_back(first_half);
        water_sign.push_back(second_half);
    }

    return water_sign;
}



std::string GetOriginalString(const std::string& water_sign)
{
    assert(water_sign.size() % 2 == 0);
    std::string original_string;

    for (size_t i = 0; i < water_sign.size(); i += 2)
    {
        const char curr_first_byte = water_sign[i];
        const char curr_second_byte = water_sign[i + 1];
        original_string.push_back(
            (curr_first_byte & 0xF0) + (curr_second_byte & 0x0F)
        );
    }

    return original_string;
}



int main()
{
    std::cout << "Input string which you would like to hide: ";
    std::string string_to_hide;
    std::getline(std::cin, string_to_hide);

    const std::string water_sign = GetWaterSign(string_to_hide);
    std::cout << "water sign = [" << water_sign << "]\n";
    std::cout << "water sign in HEX = [ ";
    for (size_t i = 0; i < water_sign.size(); i++)
    {
        std::cout << std::hex << std::uppercase << (int)water_sign[i] << " ";
    }
    std::cout << "]\n";

    //const std::string original_string = GetOriginalString(water_sign);
    //std::cout << "original string = [" << original_string << "]" << std::endl;
    std::cout << "-------------------------------------------\n";

    std::cout << "Input size of water sign: ";
    size_t water_sign_size = 0;
    std::cin >> water_sign_size;

    std::cout << "Input water sign (in HEX): ";
    std::string input_water_sign;
    for (size_t i = 0; i < water_sign_size; i++)
    {
        int curr_hex = 0;
        std::cin >> std::hex >> curr_hex;
        input_water_sign.push_back(curr_hex);
    }

    std::cout << "original string = ["
              << GetOriginalString(input_water_sign)
              << "]" << std::endl;
    return 0;
}
