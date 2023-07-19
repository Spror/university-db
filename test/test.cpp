#include <Database.hpp>
#include <Employee.hpp>
#include <Student.hpp>
#include <Pesel.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>

class PersonTests : public ::testing::Test
{
protected:
    std::array<uint8_t, 6> index1{2, 4, 8, 9, 7, 0}, index2{1, 3, 5, 6, 6, 7};
    Pesel pesel1{{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}},
        pesel2{{1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 5}};

    Student student1{"Kacper", "Kowalski", {}, index1, pesel1, Sex::MALE};
    Employee employee1{"Kacper", "Kowalski", {}, pesel2, Sex::MALE, 6700.0};
    Student student2{"Kacper", "Kowalski", {}, index2, pesel2, Sex::MALE};
    Employee employee2{"Kacper", "Kowalski", {}, pesel1, Sex::MALE, 6700.0};
};

class DataBaseTests : public ::testing::Test
{
protected:
    Adress adress{"Wroclaw", "Grunwaldzka", "54-300", 15, 32};
    std::array<uint8_t, 6> index{2, 4, 8, 9, 7, 0};

    Student student1{"Patryk", "Puzon", {}, {{0}}, {{6}}, Sex::MALE};
    Employee employee1{"Kacper", "Kowalski", {}, {{1}}, Sex::MALE, 6700.0};
    Student student2{"Czarek", "Nowak", {}, {{1}}, {{2}}, Sex::MALE};
    Student student3{"Wiktor", "Kowalski", {}, {{2}}, {{3}}, Sex::MALE};
    Employee employee2{"Kacper", "Kowalski", {}, {{4}}, Sex::MALE, 2322.0};
    Employee employee3{"Kacper", "Kowalski", {}, {{5}}, Sex::MALE, 6210.0};
    Database data;
};

TEST_F(PersonTests, OperatorEquality)
{
    // Check operator==
    EXPECT_EQ(student1, employee2);  // Same PESEL - student and employee comparison
    EXPECT_EQ(employee2, employee2); // Same PESEL - employee and employee comparison
    EXPECT_EQ(student1, student1);   // Same PESEL - student and student comparison

    // Check operator!=
    EXPECT_NE(student1, employee1);  // different PESEL
    EXPECT_NE(employee1, employee2); // different PESEL employee and employee comparison
    EXPECT_NE(student1, student2);   // different PESEL student and student comparison
}

TEST_F(DataBaseTests, addingStudent)
{

    data.add(student1);

    EXPECT_EQ(*(data.getPersons()[0].get()), student1);
}

TEST_F(DataBaseTests, personDuplicationProtection)
{

    EXPECT_EQ(data.add(student1), 1);
    EXPECT_EQ(data.add(student1), 0);
}

TEST_F(DataBaseTests, searchByLastName)
{
    data.add(student1);
    data.add(student2);
    data.add(student3);
    data.add(employee1);
    data.add(employee2);
    data.add(employee3);

    // CHECK SEARCHING IF ONE CASE IN DATABASE
    EXPECT_EQ(data.searchByLastName("Puzon").size(), 1);

    // CHECK SEARCHING IF NONE CASE IN DATABASE
    EXPECT_EQ(data.searchByLastName("Paciorek").size(), 0);

    // CHECK SEARCHING IF MORE THAN ONE CASE IN DATABASE
    EXPECT_EQ(data.searchByLastName("Kowalski").size(), 4);
}

TEST_F(DataBaseTests, searchByPesel)
{

    data.add(student1);
    data.add(student2);
    data.add(student3);
    data.add(employee1);
    data.add(employee2);
    data.add(employee3);

    Student expected_1{student1};
    Employee expected_2{employee1};
    // CHECK SEARCHING IF ONE CASE IN DATABASE
    auto returnedStudent_ptr = data.searchByPesel({{6}});
    Student returnedStudent = *(std::dynamic_pointer_cast<Student>(returnedStudent_ptr).get());
    auto returnedEmployee_ptr = data.searchByPesel({{1}});
    Employee returnedEmployee = *(std::dynamic_pointer_cast<Employee>(returnedEmployee_ptr).get());

   EXPECT_EQ(returnedStudent, expected_1);
   EXPECT_EQ(returnedEmployee, expected_2);
   // CHECK SEARCHING IF NONE CASE IN DATABASE
   EXPECT_EQ(data.searchByLastName({1, 2, 44, 55}).size(), 0);
}

TEST_F(DataBaseTests, sortByPesel)
{

    data.add(student2);
    data.add(employee1);
    data.add(employee3);
    data.add(student3);
    data.add(student1);
    data.add(employee2);

    std::vector<Person *> expected{&employee1, &student2, &student3, &employee2, &employee3, &student1};


    data.sortbByPesel();


    EXPECT_EQ(data.getPersons()[0].get()->getPesel().getPesel() , expected[0]->getPesel().getPesel());
    EXPECT_EQ(data.getPersons()[1].get()->getPesel().getPesel() , expected[1]->getPesel().getPesel());
    EXPECT_EQ(data.getPersons()[2].get()->getPesel().getPesel() , expected[2]->getPesel().getPesel());
    EXPECT_EQ(data.getPersons()[3].get()->getPesel().getPesel() , expected[3]->getPesel().getPesel());
    EXPECT_EQ(data.getPersons()[4].get()->getPesel().getPesel() , expected[4]->getPesel().getPesel());
    EXPECT_EQ(data.getPersons()[5].get()->getPesel().getPesel() , expected[5]->getPesel().getPesel());

}

TEST_F(DataBaseTests, sortByLastName)
{
    Student student2{"Patryk", "Puzon", adress, {1}, {{2, 2, 3, 4, 5, 6, 7, 8, 9, 1, 5}}, Sex::MALE};
    Student student3{"Kacper", "Kowalski", adress, {3}, {{9, 3, 3, 4, 5, 6, 7, 8, 3, 1, 5}}, Sex::MALE};
    Student student4{"Czarek", "Nowak", {}, {5}, {{1}}, Sex::MALE};
    Employee employee1{"Wiktoria", "Pozarska", adress, {{1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 6}}, Sex::FEMALE, 7373.0};
    Student student6{"Konstanty", "Smith", adress, {33}, {{1, 2, 3, 4, 5, 6, 7, 2, 9, 1, 5}}, Sex::MALE};
    Employee employee2{"Czeslaw", "Gwint", {}, {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}, Sex::MALE, 3930.0};
    Student student8{"Wiktor", "Adamski", adress, {17}, {{1, 2, 3, 1, 2, 2, 2, 2, 2, 2, 2}}, Sex::MALE};

    data.add(employee1);
    data.add(student4);
    data.add(student3);
    data.add(student2);
    data.add(student6);
    data.add(employee2);
    data.add(student8);

    std::vector<Person *> expected{&student8, &employee2, &student3, &student4, &employee1, &student2, &student6};
    EXPECT_NE(data.getPersons()[0].get()->getLastName(), expected[0]->getLastName());
    data.sortByLastName();
    EXPECT_EQ(data.getPersons()[0].get()->getLastName(), expected[0]->getLastName());
    EXPECT_EQ(data.getPersons()[1].get()->getLastName(), expected[1]->getLastName());
    EXPECT_EQ(data.getPersons()[2].get()->getLastName(), expected[2]->getLastName());
    EXPECT_EQ(data.getPersons()[3].get()->getLastName(), expected[3]->getLastName());
    EXPECT_EQ(data.getPersons()[4].get()->getLastName(), expected[4]->getLastName());
    EXPECT_EQ(data.getPersons()[5].get()->getLastName(), expected[5]->getLastName());
    EXPECT_EQ(data.getPersons()[6].get()->getLastName(), expected[6]->getLastName());
}

TEST_F(DataBaseTests, deleteByIndex)
{


  data.add(employee1);
  data.add(employee3);
  data.add(student1);
  data.add(student2);
  data.add(employee2);
  data.add(student3);


  auto sizeBefore = data.getDatabaseSize();

  EXPECT_EQ(data.deleteByIndex({1}), 1);
  EXPECT_LT(data.getDatabaseSize(), sizeBefore);
}


TEST_F(DataBaseTests, writingToFile)
{


  data.add(student1);
  data.add(employee1);
  data.add(student2);
  data.add(student3);
  data.add(employee2);
    data.add(employee3);


  EXPECT_EQ(data.saveToFile("dane#1.txt"), 1);
}


TEST(PeseleTest, PeselValidationTest)
{
  Pesel pesel_1({5, 5, 0, 3, 0, 1, 0, 1, 1, 9, 3}), pesel_2({9, 9, 0, 2, 2, 7, 0, 0, 1, 5, 7}),
        pesel_3({1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5}), pesel_4({5, 5, 0, 3, 0, 1, 0, 1, 2, 3, 0});

  EXPECT_EQ(pesel_1.peselValidation(), 1); // Standard PESEL #1
  EXPECT_EQ(pesel_2.peselValidation(), 1); // Standard PESEL #2
  EXPECT_NE(pesel_3.peselValidation(), 1); // Wrong PESEL
  EXPECT_EQ(pesel_4.peselValidation(), 1); // Standard PESEL - checksum = 0
}


TEST_F(DataBaseTests, readingFromFile)
{



  data.add(student1);
  data.add(student2);
  data.add(student3);
  data.add(employee1);
  data.add(employee2);
  data.add(employee3);

  data.sortByLastName();
  Database data2;

  EXPECT_EQ(data.saveToFile("dane#1.txt"), 1);
  EXPECT_EQ(data2.readFromFile("dane#1.txt"), 1);
  auto vec1 = data.getPersons(), vec2=data2.getPersons();

  for(auto i = 0; i < vec1.size(); i++ ){
    EXPECT_EQ(*(vec1[i].get()),*(vec2[i].get()));
  }

}

TEST_F(DataBaseTests, SalaryModifying)
{



  data.add(student1);
  data.add(student2);
  data.add(student3);
  data.add(employee1);
  data.add(employee2);
  data.add(employee3);

  auto pesel = employee1.getPesel();
  float newSalary = 8900.90;
  float lastSalary = employee1.getSalary();

  // check whether salaries are not equal
  EXPECT_NE(newSalary, lastSalary);

  // try to modify employee1's salary 
  EXPECT_EQ(data.modifySalary(pesel, newSalary), 1);

  auto person = *(std::dynamic_pointer_cast<Employee>(data.searchByPesel(pesel)));


  EXPECT_EQ(person.getPesel(), pesel);

  //check whether the salary has changed
  EXPECT_EQ(person.getSalary(), newSalary);

}

// TEST_F(DataBaseTests, displaingDataBase)
// {
//   data.add(student);

//   // TO DO
//   EXPECT_EQ(1, 1);
// }








int main(int argc, char **argv)
{

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}