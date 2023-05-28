#include <Student.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>



TEST(StudentTest, OperatorEquality) {
  Adress adress;
  std::vector<int> index1{2, 4, 8, 9, 7, 0}, index2{1, 3, 5, 6};
  std::vector<int> pesel1{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}, pesel2{1, 2, 3, 4, 5, 6};

  Student student1{"Wiktor", "Kowalski", adress, index1, pesel1, Sex::MALE};
  Student student2{"Patryk", "Puzon", adress, index1, pesel2, Sex::MALE};
  Student student3{"Kacper", "Kowalski", adress, index2, pesel1, Sex::MALE};
  Student student4{"Czarek", "Nowak", adress, index1, pesel1, Sex::MALE};
  Student student5{"Wiktor", "Kowalski", adress, index2, pesel2, Sex::MALE};


  // Check operator==
  EXPECT_EQ(student1, student2);  // Same index
  EXPECT_EQ(student1, student3);  // Same PESEL
  EXPECT_EQ(student1, student4);  // Same PESEL and index
  // ...

  // Check operator!=
  EXPECT_NE(student1, student5); // different index and PESEL
  // ...
}


int main(int argc, char **argv) {

  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}