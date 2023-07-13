#pragma once

#include <iostream>
#include <array>
#include <cstdint>
#include <algorithm>


class Pesel {
    
    std::array<uint8_t, 11> a_pesel_;

    public:

    Pesel(std::array<uint8_t, 11> pesel );
    std::array<uint8_t, 11> getPesel() const {return a_pesel_;}

    bool checkDigit();

    bool peselValidation();


    


};
