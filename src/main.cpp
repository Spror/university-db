#include <iostream>
#include <Student.hpp>
#include <Database.hpp>



int main(){

Adress addres_1;
addres_1.apartamentNumber =12;

Student student_1{"Wiktor", "Kowalski", addres_1, {2,4,8,9,7,0}, {9,9,9,9,9,9,9,9,9,9,9}, Sex::MALE},
        student_2{"Wiktor", "Raczek", addres_1, {2,4,8,9,3,0}, {9,9,1,9,9,9,9,9,9,9,9}, Sex::MALE},
        student_3{"Wiktor", "Raczek", addres_1, {2,4,8,1,3,0}, {1,9,1,9,9,9,9,9,9,9,9}, Sex::MALE};

Database dataBase1;
dataBase1.add(student_1);
dataBase1.add(student_2);
dataBase1.add(student_3);

auto set = dataBase1.searchByLastName("Kowalskia");

for(auto const &it: set){
    std::cout << it;
}

    return 0;
}