#pragma once

#include <Student.hpp>
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

class Database
{

private:
    std::vector<Student> v_students_;

    template <typename F>
    auto findStudent(const F *func);

    template <typename F>
    void sortStudents(const F *func);

public:
    bool add(Student const &student);
    std::vector<Student> getStudents() const { return v_students_; }

    void display();

    std::vector<Student> searchByLastName(std::string const lastName);
    std::vector<Student> searchByPesel(std::vector<int> const index);

    void sortbByPesel();
    void sortByIndex();

    bool deleteByIndex(std::vector<int> const index);
};