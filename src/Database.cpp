#include <Database.hpp>

bool Database::add(Student const &student)
{
    for (const auto &it : v_persons_)
    {
        if (*it.get() == student)
        {
            std::cerr << "There exist that person in database" << std::endl;
            return false;
        }
    }

    std::shared_ptr<Person> sharedPtr = std::make_shared<Student>(student);
    v_persons_.push_back(sharedPtr);
    return true;
}

bool Database::add(Employee const &employee)
{
    for (const auto &it : v_persons_)
    {
        if (*it.get() == employee)
        {
            std::cerr << "There exist that person in database" << std::endl;
            return false;
        }
    }

    std::shared_ptr<Person> sharedPtr = std::make_shared<Employee>(employee);
    v_persons_.push_back(sharedPtr);
    return true;
}


void Database::display()
{

    for (const auto &it : v_persons_)
    {
        std::cout << *it.get() << std::endl;
    }
}

template <typename F>
auto Database::findStudent(const F *func)
{
    std::vector<std::shared_ptr<Person>> matchingStudents;
    std::copy_if(v_persons_.begin(), v_persons_.end(),
                 std::back_inserter(matchingStudents), (*func));
    return matchingStudents;
}

template <typename F>
void Database::sortStudents(const F *func)
{
    std::sort(v_persons_.begin(), v_persons_.end(), (*func));
}

std::vector<std::shared_ptr<Person>> Database::searchByLastName(std::string const lastName)
{

    auto condition = [lastName](std::shared_ptr<Person> const &s)
    {
        return (*s.get()).getLastName() == lastName;
    };

    return findStudent(&condition);
}

std::vector<std::shared_ptr<Person>> Database::searchByPesel(Pesel const pesel)
{
    auto condition = [pesel](std::shared_ptr<Person> const &s)
    {
        return (*s.get()).getPesel().getPesel() == pesel.getPesel();
    };

    return findStudent(&condition);
}

void Database::sortbByPesel()
{

    auto condition = [](std::shared_ptr<Person> const &s1, std::shared_ptr<Person> const &s2)
    {
        if ((*s1.get()).getPesel().getPesel().size() != (*s2.get()).getPesel().getPesel().size())
        {
            return (*s1.get()).getPesel().getPesel().size() < (*s2.get()).getPesel().getPesel().size();
        }
        return std::lexicographical_compare(
            ((*s1.get()).getPesel().getPesel()).begin(), ((*s1.get()).getPesel().getPesel()).end(),
            ((*s2.get()).getPesel().getPesel()).begin(), ((*s2.get()).getPesel().getPesel()).end());

        // const auto& it = (*s1.get()).getPesel().getPesel().begin(), it2 = (*s1.get()).getPesel().getPesel().begin();
        // for(; (it == (*s1.get()).getPesel().getPesel().end());)
    };

    sortStudents(&condition);
}

void Database::sortByLastName()
{

    auto condition = [](std::shared_ptr<Person> const &s1, std::shared_ptr<Person>  const &s2)
    {
        return (*s1.get()).getLastName() < (*s2.get()).getLastName();
    };

    sortStudents(&condition);
}

bool Database::deleteByIndex(std::array<uint8_t, 6> const index)
{

    auto condition = [index](std::shared_ptr<Person> const &s)
    {
        if((*s.get()).getProffesion() == "Student")
        {
            Student temp = (*(std::dynamic_pointer_cast<Student>(s)).get());
            return temp.getIndex() == index;
        }
           return false;
    };

    auto toDelete = std::find_if(v_persons_.begin(), v_persons_.end(), condition);

        if (toDelete != v_persons_.end())
        {
            v_persons_.erase(toDelete);
            return true;
        }

     return false;
}

bool Database::saveToFile(const std::string &filename)
{
    auto inc = 0;
    std::ofstream file(filename);
    file << "DATA BASE SIZE => " << v_persons_.size() << std::endl;
    if (file.is_open())
    {
        for (auto const &person_ptr : v_persons_)
        {
            file << ++inc << " " << *(person_ptr.get()) << "\n";
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
            if (line.find("#### Student") != std::string::npos )
            {
                //index_str = line.substr(line.find("Student ") + 8);

                std::getline(inputFile, line);
                index_str = line.substr(line.find(": ") + 2);

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

                std::shared_ptr<Person> sharedPtr = std::make_shared<Student>(temp);
                v_persons_.push_back(sharedPtr);
            }
            else if (line.find("#### Student") != std::string::npos )
            {


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
                
                Employee temp{name, lastName, {city, street, postCode, apartamentNumber, flatNumber },  {pesel}, sex};

                std::shared_ptr<Person> sharedPtr = std::make_shared<Student>(temp);
                v_persons_.push_back(sharedPtr);
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
