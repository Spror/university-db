#include <Pesel.hpp>

Pesel::Pesel(std::array<uint8_t, 11> pesel) : a_pesel_{pesel}
{
    if(!checkDigit()){
        std::cerr << "Wrong pesel number - one of the entered values is not a digit" << std::endl;
    }
}

bool Pesel::checkDigit()
{
    constexpr std::array<uint8_t, 10> digits{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    for (const auto &it : a_pesel_)
    {
        if (*std::find(digits.begin(), digits.end(), it) != it)
        {
            return false;
        }
    }

    return true;
}