#include <iostream>
#include <Person.hpp>
#include <Database.hpp>
#include <Pesel.hpp>
#include <Student.hpp>
#include <Employee.hpp>
#include <memory>


int main()
{

    Adress addres_1;
    addres_1.apartamentNumber = 12;

   // Person person1{"Wiktor", "Kowalski", addres_1, {{9}}, Sex::MALE};
    Student student_1{"Wiktor", "Kowalski", addres_1, {2, 4, 8, 9, 7, 0}, {{9}}, Sex::MALE};
    Employee employee_1{"Wiktor", "Kowalski", addres_1, {{9}}, Sex::MALE, 6700.0};
    std::vector<std::unique_ptr<Person>> vec_;

    // vec_.push_back(std::make_unique<Employee>(employee_1));
    // vec_.push_back(std::make_unique<Student>(student_1));
    Database data1;

    data1.add(employee_1);
    data1.add(student_1);

    for(auto const &it: vec_){
        std::cout << *it.get();
    }

    return 0;
}