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

std::ifstream &Employee::input(std::ifstream &ifs)
{
    std::string line, pesel_str, sex_str;
    Sex sex;

    std::getline(ifs, line);
    name_ = line.substr(line.find(": ") + 2);

    std::getline(ifs, line);
    lastName_ = line.substr(line.find(": ") + 2);

    std::getline(ifs, line);
    sex_str = line.substr(line.find(": ") + 2);

    std::getline(ifs, line);
    line = line.substr(line.find(": ") + 2);
    size_t spacePos = line.find(' ');
    line.erase(spacePos);

    salary_ = std::stof(line);

    std::getline(ifs, line);
    pesel_str = line.substr(line.find(": ") + 2);

    std::getline(ifs, line); // Skip the Address data line

    std::getline(ifs, line); // Read the City line
    adress_.city = line.substr(line.find(": ") + 2);

    std::getline(ifs, line); // Read the Street line
    adress_.street = line.substr(line.find(": ") + 2);

    std::getline(ifs, line); // Read the Post-code line
    adress_.postCode = line.substr(line.find(": ") + 2);

    std::getline(ifs, line); // Read the Apartment number line
    adress_.apartamentNumber = std::stoi(line.substr(line.find(": ") + 2));

    std::getline(ifs, line); // Read the Flat number line
    adress_.flatNumber = std::stoi(line.substr(line.find(": ") + 2));

    if (sex_str == "Male")
    {
        sex = Sex::MALE;
    }
    else
        sex = Sex::FEMALE;

    pesel_ = stringToPesel(pesel_str);
    return ifs;
}