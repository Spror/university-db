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

std::shared_ptr<Person> Database::searchByPesel(Pesel const pesel)
{
    auto condition = [pesel](std::shared_ptr<Person> const &s)
    {
        return (*s.get()).getPesel() == pesel;
    };

    return findStudent(&condition)[0];
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

bool Database::modifySalary(Pesel pesel, float newSalary)
{

    auto condition = [pesel](std::shared_ptr<Person> const &s)
    {
        if((*s.get()).getProffesion() == "Employee")
        {
            Employee temp = (*(std::dynamic_pointer_cast<Employee>(s)).get());
            return temp.getPesel() == pesel;
        }
           return false;
    };

    auto toModify = std::find_if(v_persons_.begin(), v_persons_.end(), condition);

        if (toModify != v_persons_.end())
        {
            Employee *temp = (std::dynamic_pointer_cast<Employee>(toModify[0])).get();
            temp->setSalary(newSalary);
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
            file  << *(person_ptr.get()) << "\n";
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
    std::string line;

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return false;
    }
    

    while (std::getline(inputFile, line))
    {
        if (line.find("#### Student") != std::string::npos)
        {
            Student temp;
            inputFile >> temp;
            v_persons_.push_back(std::make_shared<Student>(temp));

        }
        else if(line.find("#### Employee") != std::string::npos)
        {
            Employee temp; 
            inputFile >> temp;
            v_persons_.push_back(std::make_shared<Employee>(temp));

        }
    }
    return true;
}

