#include <iostream>
#include <Student.hpp>


int main(){

Adress addres_1;
addres_1.apartamentNumber =12;

Student student_1{"Wiktor", "Kowalski", addres_1, {2,4,8,9,7,0}, {9,9,9,9,9,9,9,9,9,9,9}, Sex::MALE},
        student_2{"Wiktor", "Kowalski", addres_1, {2,4,8,9,3,0}, {9,9,9,9,9,9,9,9,9,9,9}, Sex::MALE};

if(student_1 == student_2)
    std::cout << student_1 << std::endl;

    return 0;
}