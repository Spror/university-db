#pragma once

#include <Pesel.hpp>
#include <string>

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
    Person(std::string name, std::string lastName, Adress adress, Pesel pesel,
           Sex sex);

    std::string getName() const { return name_; }
    std::string getLastName() const { return lastName_; }
    Adress getAddres() const { return adress_; }
    Pesel getPesel() const { return pesel_; }
    Sex getSex() const { return sex_; }

    bool operator==(const Person &s1) const;
    bool operator!=(const Person &s1) const;

    virtual std::ostream& output(std::ostream& os) const = 0;
    virtual std::string getProffesion() const = 0;
    virtual ~Person() = default;
};

std::ostream &operator<<(std::ostream &os, const Adress &adress);
inline std::ostream &operator<<(std::ostream &os, const Person &obj) { return obj.output(os); }