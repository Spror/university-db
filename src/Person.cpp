#include <Person.hpp>

Person::Person(std::string name, std::string lastName, Adress adress, Pesel pesel, Sex sex) :
name_{name,} , lastName_{lastName}, adress_{adress}, pesel_{pesel}, sex_{sex}
{}


bool Person::operator==(const Person &s1) const
{
    return  s1.getPesel().getPesel() == this->pesel_.getPesel();
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


