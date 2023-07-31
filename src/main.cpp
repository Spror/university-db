#include <iostream>
#include <Person.hpp>
#include <Database.hpp>
#include <Pesel.hpp>
#include <Student.hpp>
#include <Employee.hpp>
#include <memory>


int main()
{

    std::string addres_1;

   // Person person1{"Wiktor", "Kowalski", addres_1, {{9}}, Sex::MALE};
    Student student_1{"Wiktor", "Kowalski", addres_1, {2, 4, 8, 9, 7, 0}, {{9}}, Sex::MALE};
    Employee employee_1{"Wiktor", "Kowalski", addres_1, {{9,1}}, Sex::MALE, 6700.0};
    std::vector<std::shared_ptr<Person>> vec_;

    Database data1;

    data1.add(employee_1);
    data1.add(student_1);

    for(auto const &it: vec_){
        std::cout << *it.get();
    }

    return 0;
}