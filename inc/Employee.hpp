#pragma once

#include <Person.hpp>

class Employee : public Person
{
private:
    float salary_;

public:
    Employee(std::string name, std::string lastName, Adress adress, Pesel pesel,
             Sex sex, float salary);

    float getSalary() const {return salary_;}
    virtual std::ostream& output(std::ostream& os) const;
    virtual std::string getProffesion() const {return "Employee";}
};