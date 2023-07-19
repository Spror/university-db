#pragma once

#include <Person.hpp>

class Employee : public Person
{
private:
    float salary_;

public:
    Employee()
        : Person("", "", Adress(), {{}}, Sex::MALE)
    {
    }
    Employee(std::string name, std::string lastName, Adress adress, Pesel pesel,
             Sex sex, float salary);

    float getSalary() const { return salary_; }
    void setSalary(float newSalary) { salary_ = newSalary; }
    virtual std::ostream &output(std::ostream &os) const;
    virtual std::ifstream &input(std::ifstream &ifs);
    virtual std::string getProffesion() const { return "Employee"; }
};