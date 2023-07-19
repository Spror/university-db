#include <Person.hpp>

Person::Person(std::string name, std::string lastName, Adress adress, Pesel pesel, Sex sex) : name_{
                                                                                                  name,
                                                                                              },
                                                                                              lastName_{lastName}, adress_{adress}, pesel_{pesel}, sex_{sex}
{
}

bool Person::operator==(const Person &s1) const
{
    return s1.getPesel().getPesel() == this->pesel_.getPesel();
}

bool Person::operator!=(const Person &s1) const
{
    return !(*this == s1);
}

std::ostream &operator<<(std::ostream &os, const Adress &obj)
{
    os << " #### Adress data:"
       << "\n  City: " << obj.city
       << "\n  Street: " << obj.street
       << "\n  Post-code: " << obj.postCode
       << "\n  Apartament number: " << obj.apartamentNumber
       << "\n  Flat number: " << obj.flatNumber;
    return os;
}

std::array<uint8_t, 11> Person::stringToPesel(std::string pesel_str) const
{

    std::array<uint8_t, 11> a_pesel;
    size_t inc{0};
    if (pesel_str.size() == 11)
    {
        for (const auto &it : pesel_str)
        {
            a_pesel[inc++] = it - '0';
        }
    }

    return a_pesel;
}
