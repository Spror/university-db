#include <Student.hpp>
Student::Student(std::string name, std::string lastName, std::string adress, std::array<size_t, 6> index, Pesel pesel, Sex sex)
    : Person(name, lastName, adress, pesel, sex), a_index_{index}
{
}

std::ostream &Student::output(std::ostream &os) const
{
    os << "\n#### Student "
       << "\n Index: ";
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

    os << "\n Adress: " << adress_;
    return os;
}

std::array<size_t, 6> Student::stringToIndex(std::string index_str)
{
    std::array<size_t, 6> a_index;
    size_t inc{0};
    if (index_str.size() == 6)
    {
        for (const auto &it : index_str)
        {
            a_index[inc++] = it - '0';
        }
    }

    return a_index;
}

std::ifstream &Student::input(std::ifstream &ifs)
{
    std::string line, index_str, pesel_str, sex_str;
    Sex sex;

    std::getline(ifs, line);
    index_str = line.substr(line.find(": ") + 2);

    std::getline(ifs, line);
    name_ = line.substr(line.find(": ") + 2);

    std::getline(ifs, line);
    lastName_ = line.substr(line.find(": ") + 2);

    std::getline(ifs, line);
    sex_str = line.substr(line.find(": ") + 2);

    std::getline(ifs, line);
    pesel_str = line.substr(line.find(": ") + 2);

    std::getline(ifs, line);
    adress_ = line.substr(line.find(": ") + 2);

    if (sex_str == "Male")
    {
        sex = Sex::MALE;
    }
    else
        sex = Sex::FEMALE;

    pesel_ = stringToPesel(pesel_str);
    a_index_ = stringToIndex(index_str);
    return ifs;
}