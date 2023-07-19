#pragma once

#include <Student.hpp>
#include <Employee.hpp>
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

#include <sstream>
#include <memory>

class Database
{

private:
    std::vector<std::shared_ptr<Person>> v_persons_;
    template <typename F>
    auto findStudent(const F *func);

    template <typename F>
    void sortStudents(const F *func);

public:
    bool add(Student const &student);
    bool add(Employee const &employee);

    
    auto getDatabaseSize() const { return v_persons_.size(); }
    
    void display();

    std::vector<std::shared_ptr<Person>> getPersons() const { return v_persons_; }
    std::vector<std::shared_ptr<Person>> searchByLastName(std::string const lastName);
    std::shared_ptr<Person> searchByPesel(Pesel const pesel);

    void sortbByPesel();
    void sortByLastName();
    void sortBySalary();

    bool modifySalary(Pesel pesel, float newSalary);
    bool deleteByIndex(std::array<uint8_t, 6> const index);

    bool saveToFile(const std::string &filename);
    bool readFromFile(const std::string &filename);
};