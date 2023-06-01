#include <Pesel.hpp>

Pesel::Pesel(std::array<uint8_t, 11> pesel) : a_pesel_{pesel}
{
    if(!checkDigit()){
        std::cerr << "Wrong pesel number - one of the entered values is not a digit" << std::endl;
        exit(-1);
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

bool Pesel::peselValidation(){
    constexpr std::array<uint8_t, 10> a_coefficients{1, 3, 7, 9, 1, 3, 7, 9, 1, 3};

    auto iter_pesel = a_pesel_.begin();
    auto iter_coeff = a_coefficients.begin();
    uint checksum{0};

    for(; iter_coeff != a_coefficients.end(); iter_coeff++, iter_pesel++){
        checksum += *iter_coeff*(*iter_pesel);
    }

    checksum %= 10;

    if(checksum != 0){
        checksum = 10 - checksum;
    }

    if(checksum == a_pesel_[10])
        return true;

    return false;

}
