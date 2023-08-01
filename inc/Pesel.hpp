#pragma once

#include <iostream>
#include <array>
#include <cstdint>
#include <algorithm>

class Pesel
{

    std::array<size_t, 11> a_pesel_;

public:
    Pesel(std::array<size_t, 11> pesel);
    std::array<size_t, 11> getPesel() const { return a_pesel_; }
    Pesel(std::string pesel_str);
    Pesel() = default;

    bool checkDigit();
    bool operator==(const Pesel &s1) const;
    bool operator!=(const Pesel &s1) const;
    bool peselValidation();
};
