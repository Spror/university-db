#include <Database.hpp>
#include <Student.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>


class DataBaseTests : public ::testing::Test{
  protected:
  Adress adress{"Wroclaw", "Grunwaldzka", "54-300", 15, 32};
  std::vector<int> index{2, 4, 8, 9, 7, 0},
      pesel{1, 23, 3, 4, 5, 6, 7, 8, 9, 11, 5};
  Student student{"Wiktor", "Kowalski", adress, index, pesel, Sex::MALE};
  Database data;

};


class StudentTests : public ::testing::Test {
protected:
  Adress adress{"Wroclaw", "Grunwaldzka", "54-300", 15, 32};
  std::vector<int> index{2, 4, 8, 9, 7, 0},
      pesel{1, 23, 3, 4, 5, 6, 7, 8, 9, 11, 5};
  Student student{"Wiktor", "Kowalski", adress, index, pesel, Sex::MALE};
};

TEST_F(StudentTests, OperatorEquality) {

  std::vector<int> index1{2, 4, 8, 9, 7, 0}, index2{1, 3, 5, 6, 6, 7};
  std::vector<int> pesel1{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
      pesel2{1, 23, 3, 4, 5, 6, 7, 8, 9, 11, 5};

  Student student2{"Patryk", "Puzon", adress, index1, pesel1, Sex::MALE};
  Student student3{"Kacper", "Kowalski", adress, index2, pesel2, Sex::MALE};
  Student student4{"Czarek", "Nowak", {}, index1, pesel2, Sex::MALE};
  Student student5{"Wiktor", "Kowalski", adress, index2, pesel1, Sex::MALE};

  // Check operator==
  EXPECT_EQ(student, student2); // Same index
  EXPECT_EQ(student, student3); // Same PESEL
  EXPECT_EQ(student, student4); // Same PESEL and index
  // ...

  // Check operator!=
  EXPECT_NE(student, student5); // different index and PESEL
  // ...
}


TEST_F(DataBaseTests, addingStudent) {

  data.add(student);

  EXPECT_EQ(data.getStudents()[0], student);
}

TEST_F(DataBaseTests, studentDuplicationProtection) {


  EXPECT_EQ(data.add(student), 1);
  EXPECT_EQ(data.add(student), 0);
}

TEST_F(DataBaseTests, displaingDataBase){
  data.add(student);
  
  // TO DO 
  EXPECT_EQ(1,1);

}

TEST_F(DataBaseTests, searchByLastName){

  Student student2{"Patryk", "Puzon", adress, {1}, {2}, Sex::MALE};
  Student student3{"Kacper", "Kowalski", adress, {3}, {4}, Sex::MALE};
  Student student4{"Czarek", "Nowak", {}, {5}, {6}, Sex::MALE};
  Student student5{"Wiktor", "Kowalski", adress, {7}, {8}, Sex::MALE};

  data.add(student);
  data.add(student2);
  data.add(student3);
  data.add(student4);
  data.add(student5);
  
  // CHECK SEARCHING IF ONE CASE IN DATABASE
  EXPECT_EQ(data.searchByLastName("Puzon").size(), 1);

  // CHECK SEARCHING IF NONE CASE IN DATABASE
  EXPECT_EQ(data.searchByLastName("Paciorek").size(), 0);

  // CHECK SEARCHING IF MORE THAN ONE CASE IN DATABASE
  EXPECT_EQ(data.searchByLastName("Kowalski").size(), 3);

}



int main(int argc, char **argv) {

  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}