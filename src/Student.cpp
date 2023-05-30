#include <Student.hpp>

std::ostream &operator<<(std::ostream &os, const Student &obj)
{
    os << "#### Student data:"
       << "\n Name: " << obj.getName()
       << "\n Last name: " << obj.getLastName();

    auto sex = obj.getSex();

    switch (sex)
    {
    case Sex::MALE:
        std::cout << "\n Sex: Male";
        break;
    case Sex::FEMALE:
        std::cout << "\n Sex: Female";
        break;

    default:
        break;
    }

    std::cout << "\n Index number: ";
    for (const auto &it : obj.getIndex())
    {
        std::cout << it;
    }

    std::cout << "\n PESEL number: ";
    for (const auto &it : obj.getPesel())
    {
        std::cout << it;
    }

    std::cout << "\n"
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

Student::Student(std::string name, std::string lastName, Adress adress, std::vector<int> index, std::vector<int> pesel, Sex sex)
    : name_{name}, lastName_{lastName}, adress_{adress}, v_index_{index}, v_pesel_{pesel}, sex_{sex}
{
}

bool Student::operator==(const Student &s1) const
{
    return this->v_index_ == s1.getIndex() || s1.getPesel() == this->v_pesel_;
}

bool Student::operator!=(const Student &s1) const
{
    return !(*this == s1);
}
