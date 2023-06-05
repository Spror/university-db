#pragma once

#include <Student.hpp>
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include <sstream>

class Database
{

private:
    std::vector<Student> v_students_;

    template <typename F>
    auto findStudent(const F *func);

    template <typename F>
    void sortStudents(const F *func);

    std::array<uint8_t, 6> stringToIndex(std::string index_str);
    std::array<uint8_t, 11> stringToPesel(std::string pesel_str);

public:
    bool add(Student const &student);
    std::vector<Student> getStudents() const { return v_students_; }
    auto getDatabaseSize() const {return v_students_.size();}
    void display();

    std::vector<Student> searchByLastName(std::string const lastName);
    std::vector<Student> searchByPesel(Pesel const pesel);

    void sortbByPesel();
    void sortByLastName();

    bool deleteByIndex(std::array<uint8_t,6> const index);

    bool saveToFile(const std::string &filename);
    bool readFromFile(const std::string &filename);
};