#include <Student.hpp>

std::ostream &operator<<(std::ostream &os, const Student &obj)
{
    os << "#### Student ";
    for (const auto &it : obj.getIndex())
    {
        os << static_cast<int>(it);
    } 
     os  << "\n Name: " << obj.getName()
       << "\n Last name: " << obj.getLastName();

    auto sex = obj.getSex();

    switch (sex)
    {
    case Sex::MALE:
        os << "\n Sex: Male";
        break;
    case Sex::FEMALE:
        os << "\n Sex: Female";
        break;

    default:
     break;
    }

   

    os << "\n PESEL number: ";
    for (const auto &it : obj.getPesel().getPesel())
    {
        os << static_cast<int>(it);
    }

    os << "\n"
       << obj.getAddres();
    return os;
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

Student::Student(std::string name, std::string lastName, Adress adress, std::array<uint8_t, 6> index, Pesel pesel, Sex sex)
    : name_{name}, lastName_{lastName}, adress_{adress}, a_index_{index}, pesel_{pesel}, sex_{sex}
{
}

bool Student::operator==(const Student &s1) const
{
    return this->a_index_ == s1.getIndex() || s1.getPesel().getPesel() == this->pesel_.getPesel();
}

bool Student::operator!=(const Student &s1) const
{
    return !(*this == s1);
}
