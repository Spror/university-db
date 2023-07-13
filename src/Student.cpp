#include <Student.hpp>
Student::Student(std::string name, std::string lastName, Adress adress, std::array<uint8_t, 6> index, Pesel pesel, Sex sex)
    : Person(name, lastName, adress, pesel, sex), a_index_{index}
{
}

std::ostream & Student::output(std::ostream &os) const
{
    os << "#### Student " << "\n Index: ";
    for (const auto &it : a_index_)
    {
        os << static_cast<int>(it);
    }
    os << "\n Name: " << name_
       << "\n Last name: " << lastName_;

    switch (sex_)
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
    for (const auto &it : pesel_.getPesel())
    {
        os << static_cast<int>(it);
    }

    os << "\n"
       << adress_;
    return os;
}

