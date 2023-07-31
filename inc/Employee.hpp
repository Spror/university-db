#pragma once

#include <Person.hpp>

class Employee : public Person
{
private:
    float salary_;

public:
    Employee()
        : Person("", "", "", {{}}, Sex::MALE)
    {
    }
    Employee(std::string name, std::string lastName, std::string  adress, Pesel pesel,
             Sex sex, float salary);

    float getSalary() const { return salary_; }
    void setSalary(float newSalary) { salary_ = newSalary; }
    virtual std::ostream &output(std::ostream &os) const;
    virtual std::ifstream &input(std::ifstream &ifs);
    virtual std::string getProfession() const { return "Employee"; }
};