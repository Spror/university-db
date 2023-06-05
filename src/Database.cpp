#include <Database.hpp>

bool Database::add(Student const &student)
{
    for (const auto &it : v_students_)
    {
        if (student == it)
        {
            std::cerr << "There exist that student in database" << std::endl;
            return false;
        }
    }

    v_students_.push_back(student);
    return true;
}

void Database::display()
{

    for (const auto &it : v_students_)
    {
        std::cout << it << std::endl;
    }
}

template <typename F>
auto Database::findStudent(const F *func)
{
    std::vector<Student> matchingStudents;
    std::copy_if(v_students_.begin(), v_students_.end(),
                 std::back_inserter(matchingStudents), (*func));
    return matchingStudents;
}

template <typename F>
void Database::sortStudents(const F *func)
{
    std::sort(v_students_.begin(), v_students_.end(), (*func));
}

std::vector<Student> Database::searchByLastName(std::string const lastName)
{

    auto condition = [lastName](Student const &s)
    {
        return s.getLastName() == lastName;
    };

    return findStudent(&condition);
}

std::vector<Student> Database::searchByPesel(Pesel const pesel)
{
    auto condition = [pesel](Student const &s)
    {
        return s.getPesel().getPesel() == pesel.getPesel();
    };

    return findStudent(&condition);
}

void Database::sortbByPesel()
{

    auto condition = [](Student const &s1, Student const &s2)
    {
        if (s1.getPesel().getPesel().size() != s2.getPesel().getPesel().size())
        {
            return s1.getPesel().getPesel().size() < s2.getPesel().getPesel().size();
        }
        return std::lexicographical_compare(
            (s1.getPesel().getPesel()).begin(), (s1.getPesel().getPesel()).end(),
            (s2.getPesel().getPesel()).begin(), (s2.getPesel().getPesel()).end());

        // const auto& it = s1.getPesel().begin(), it2 = s1.getPesel().begin();
        // fot(; (it == s1.getPesel().end()))
    };

    sortStudents(&condition);
}

void Database::sortByLastName()
{

    auto condition = [](Student const &s1, Student const &s2)
    {
        return s1.getLastName() < s2.getLastName();
    };

    sortStudents(&condition);
}

bool Database::deleteByIndex(std::array<uint8_t, 6> const index)
{

    auto condition = [index](Student const &s)
    {
        return s.getIndex() == index;
    };

    auto toDelete = std::find_if(v_students_.begin(), v_students_.end(), condition);

    if (toDelete != v_students_.end())
    {
        v_students_.erase(toDelete);
        return true;
    }

    return false;
}

bool Database::saveToFile(const std::string &filename)
{
    std::ofstream file(filename);

    if (file.is_open())
    {
        for (auto const &student : v_students_)
        {
            file << student << "\n";
        }

        file.close();

        if (file.fail())
        {
            std::cerr << "Failed to close the file" << std::endl;
            return false;
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool Database::readFromFile(const std::string &filename)
{

    std::ifstream inputFile(filename);
    std::string line, index_str, name, lastName, pesel_str, sex_str, city, street, postCode;
    Sex sex;

    if (inputFile.is_open())
    {
        while (std::getline(inputFile, line))
        {
            if (line.find("#### Student") != std::string::npos)
            {
                index_str = line.substr(line.find("Student ") + 8);

                std::getline(inputFile, line);
                name = line.substr(line.find(": ") + 2);

                std::getline(inputFile, line);
                lastName = line.substr(line.find(": ") + 2);

                std::getline(inputFile, line);
                sex_str = line.substr(line.find(": ") + 2);

                std::getline(inputFile, line);
                pesel_str = line.substr(line.find(": ") + 2);
                

                std::getline(inputFile, line); // Skip the Address data line

                std::getline(inputFile, line); // Read the City line
                city = line.substr(line.find(": ") + 2);

                std::getline(inputFile, line); // Read the Street line
                street = line.substr(line.find(": ") + 2);

                std::getline(inputFile, line); // Read the Post-code line
                postCode = line.substr(line.find(": ") + 2);

                std::getline(inputFile, line); // Read the Apartment number line
                auto apartamentNumber = std::stoi(line.substr(line.find(": ") + 2));

                std::getline(inputFile, line); // Read the Flat number line
                auto flatNumber = std::stoi(line.substr(line.find(": ") + 2));
                
                if(sex_str == "Male")
                {
                    sex = Sex::MALE;
                }
                else    
                    sex = Sex::FEMALE;

                auto pesel = stringToPesel(pesel_str);
                auto index = stringToIndex(index_str);
                
                Student temp{name, lastName, {city, street, postCode, apartamentNumber, flatNumber }, index, {pesel}, sex};
                add(temp);
            }
        }
    }
    else
    {
        std::cerr << "Failed to open the file" << std::endl;
        return false;
    }

    return true;
}

std::array<uint8_t, 6> Database::stringToIndex(std::string index_str)
{
    std::array<uint8_t, 6> a_index;
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

std::array<uint8_t, 11> Database::stringToPesel(std::string pesel_str)
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
