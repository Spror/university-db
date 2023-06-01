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

    /* 
     * Function to check whether pesel has digits from the 0-9 range
     * @return true - if it is true else false
     */
    bool checkDigit();

    /* 
     * Function to check whether pesel is valid according to 
     * https://pl.wikipedia.org/wiki/PESEL#Cyfra_kontrolna_i_sprawdzanie_poprawno%C5%9Bci_numeru
     * @return true - if it is valid else false
     */
    bool peselValidation();


    


};
