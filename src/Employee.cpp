#include <Employee.hpp>

Employee::Employee(std::string name, std::string lastName, Adress adress, Pesel pesel,
                   Sex sex, float salary) : Person(name, lastName, adress, pesel, sex), salary_{salary}
{
}

std::ostream &Employee::output(std::ostream &os) const
{
    os << "#### Employee ";
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

    os << "\n Salary: " << salary_ << " zl";
    os << "\n PESEL number: ";
    for (const auto &it : pesel_.getPesel())
    {
        os << static_cast<int>(it);
    }

    os << "\n"
       << adress_;
    return os;
}