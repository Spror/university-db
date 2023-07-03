#pragma once

#include <string>
#include <Pesel.hpp>

enum class Sex
{
    MALE,
    FEMALE
};

struct Adress
{
    std::string city{'-'};
    std::string street{'-'};
    std::string postCode{'-'};
    int apartamentNumber{NULL};
    int flatNumber{NULL};
};

class Person
{
protected:
    std::string name_;
    std::string lastName_;
    Adress adress_;
    Pesel pesel_;
    Sex sex_;

public: 
    Person(std::string name, std::string lastName, Adress adress, Pesel pesel, Sex sex);

    std::string getName() const { return name_; }
    std::string getLastName() const { return lastName_; }
    Adress getAddres() const { return adress_; }
    Pesel getPesel() const { return pesel_; }
    Sex getSex() const { return sex_; }

    bool operator==(const Person &s1) const;
    bool operator!=(const Person &s1) const;


   // virtual std::ostream &operator<<(std::ostream &os) const;
    //virtual std::string getProfession();
};