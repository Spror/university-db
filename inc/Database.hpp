#pragma once

#include <vector>
#include <Student.hpp>

class Database{

private:
    std::vector<Student> v_students_;

public:
    bool add( Student const &student);
    void display();
    Student searchByLastName(std::string const lastName);
    Student searchByIndex(std::vector<int> const index);
    Student searchByPesel(std::vector<int> const index);

    void sortbByPesel();
    void sortByIndex();

    bool deleteByIndex(std::vector<int> const index);
};