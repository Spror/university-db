#pragma once

#include <Pesel.hpp>
#include <string>
#include <fstream>

enum class Sex
{
    MALE,
    FEMALE
};

class Person
{
protected:
    std::string name_;
    std::string lastName_;
    std::string adress_;
    Pesel pesel_;
    Sex sex_;

    std::array<size_t, 11> stringToPesel(std::string pesel_str) const;

public:
    Person(std::string name, std::string lastName, std::string adress, Pesel pesel,
           Sex sex);

    std::string getName() const { return name_; }
    std::string getLastName() const { return lastName_; }
    std::string getAddres() const { return adress_; }
    Pesel getPesel() const { return pesel_; }
    Sex getSex() const { return sex_; }

    bool operator==(const Person &s1) const;
    bool operator!=(const Person &s1) const;

    virtual std::ostream &output(std::ostream &os) const = 0;
    virtual std::ifstream &input(std::ifstream &ifs) = 0;
    virtual std::string getProfession() const = 0;
    virtual ~Person() = default;
};

inline std::ostream &operator<<(std::ostream &os, const Person &obj) { return obj.output(os); }
inline std::ifstream &operator>>(std::ifstream &ifs, Person &obj) { return obj.input(ifs); }
