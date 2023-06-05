#include <iostream>
#include <Student.hpp>
#include <Database.hpp>
#include <Pesel.hpp>


int main()
{

    // Adress addres_1;
    // addres_1.apartamentNumber = 12;

    // Student student_1{"Wiktor", "Kowalski", addres_1, {2, 4, 8, 9, 7, 0}, {9}, Sex::MALE},
    //     student_2{"Wiktor", "Raczek", addres_1, {2, 4, 8, 9, 3, 0}, {1}, Sex::MALE},
    //     student_3{"Wiktor", "Raczek", addres_1, {2, 4, 8, 1, 3, 22}, {2}, Sex::MALE},
    //     student_4{"Wiktor", "Raczek", addres_1, {2, 4, 8, 1, 3, 33}, {3}, Sex::MALE},
    //     student_5{"Wiktor", "Raczek", addres_1, {2, 4, 8, 1, 3, 44}, {21}, Sex::MALE},
    //     student_6{"Wiktor", "Raczek", addres_1, {2, 4, 8, 1, 3, 55}, {3}, Sex::MALE},
    //     student_7{"Wiktor", "Raczek", addres_1, {2, 4, 8, 1, 3, 66}, {11}, Sex::MALE};

    // Database dataBase1;
    // dataBase1.add(student_1);
    // dataBase1.add(student_2);
    // dataBase1.add(student_3);
    // dataBase1.add(student_4);
    // dataBase1.add(student_5);
    // dataBase1.add(student_6);
    // dataBase1.add(student_7);

    // dataBase1.sortbByPesel();

    // for(const auto &it: dataBase1.getStudents()){
    //     std::cout << it << std::endl;
    // }

    Database data;

    data.readFromFile("dane#1.txt");

    return 0;
}