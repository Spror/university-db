#include <Database.hpp>
#include <Student.hpp>
#include <Pesel.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>

class DataBaseTests : public ::testing::Test
{
protected:
  Adress adress{"Wroclaw", "Grunwaldzka", "54-300", 15, 32};
  std::array<uint8_t, 6> index{2, 4, 8, 9, 7, 0};
  Pesel pesel{{1, 3, 3, 4, 5, 6, 7, 8, 9, 1, 5}};
  Student student{"Wiktor", "Kowalski", adress, index, pesel, Sex::MALE};
  Database data;
};

class StudentTests : public ::testing::Test
{
protected:
  Adress adress{"Wroclaw", "Grunwaldzka", "54-300", 15, 32};
  std::array<uint8_t, 6> index{2, 4, 8, 9, 7, 0};
  Pesel pesel{{1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 5}};
  Student student{"Wiktor", "Kowalski", adress, index, pesel, Sex::MALE};
};

TEST_F(StudentTests, OperatorEquality)
{

  std::array<uint8_t, 6> index1{2, 4, 8, 9, 7, 0}, index2{1, 3, 5, 6, 6, 7};
  Pesel pesel1{{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}},
      pesel2{{1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 5}};

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

TEST_F(DataBaseTests, addingStudent)
{

  data.add(student);

  EXPECT_EQ(data.getStudents()[0], student);
}

TEST_F(DataBaseTests, studentDuplicationProtection)
{

  EXPECT_EQ(data.add(student), 1);
  EXPECT_EQ(data.add(student), 0);
}

TEST_F(DataBaseTests, displaingDataBase)
{
  data.add(student);

  // TO DO
  EXPECT_EQ(1, 1);
}

TEST_F(DataBaseTests, searchByLastName)
{

  Student student2{"Patryk", "Puzon", adress, {1}, {{2}}, Sex::MALE};
  Student student3{"Kacper", "Kowalski", adress, {3}, {{4}}, Sex::MALE};
  Student student4{"Czarek", "Nowak", {}, {5}, {{6}}, Sex::MALE};
  Student student5{"Wiktor", "Kowalski", adress, {7}, {{8}}, Sex::MALE};

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

TEST_F(DataBaseTests, searchByPesel)
{

  Student student2{"Kacper", "Kowalski", adress, {3}, {{4}}, Sex::MALE};
  Student student3{"Czarek", "Nowak", {}, {5}, {{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}}, Sex::MALE};

  data.add(student);
  data.add(student2);
  data.add(student3);

  std::vector<Student> expected_1{student3}, expected_2{};
  // CHECK SEARCHING IF ONE CASE IN DATABASE
  EXPECT_EQ(data.searchByPesel({{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}}), expected_1);

  // CHECK SEARCHING IF NONE CASE IN DATABASE
  EXPECT_EQ(data.searchByLastName({1, 2, 44, 55}), expected_2);
}

TEST_F(DataBaseTests, sortByPesel)
{
  Student student2{"Patryk", "Puzon", adress, {1}, {{2, 2, 3, 4, 5, 6, 7, 8, 9, 1, 5}}, Sex::MALE};
  Student student3{"Kacper", "Kowalski", adress, {3}, {{9, 3, 3, 4, 5, 6, 7, 8, 3, 1, 5}}, Sex::MALE};
  Student student4{"Czarek", "Nowak", {}, {5}, {{1}}, Sex::MALE};
  Student student5{"Wiktoria", "Pozarska", adress, {7}, {{1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 6}}, Sex::FEMALE};
  Student student6{"Konstanty", "Smith", adress, {33}, {{1, 2, 3, 4, 5, 6, 7, 2, 9, 1, 5}}, Sex::MALE};
  Student student7{"Czeslaw", "Gwint", {}, {54}, {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}, Sex::MALE};
  Student student8{"Wiktor", "Piotrowski", adress, {17}, {{1, 2, 3, 1, 2, 2, 2, 2, 2, 2, 2}}, Sex::MALE};

  data.add(student5);
  data.add(student4);
  data.add(student3);
  data.add(student2);
  data.add(student);
  data.add(student6);
  data.add(student7);
  data.add(student8);

  std::vector<Student> expected{student4, student7, student8, student6, student5, student, student2, student3};

  EXPECT_NE(data.getStudents(), expected);
  data.sortbByPesel();
  EXPECT_EQ(data.getStudents(), expected);
}

TEST_F(DataBaseTests, sortByLastName)
{
  Student student2{"Patryk", "Puzon", adress, {1}, {{2, 2, 3, 4, 5, 6, 7, 8, 9, 1, 5}}, Sex::MALE};
  Student student3{"Kacper", "Kowalski", adress, {3}, {{9, 3, 3, 4, 5, 6, 7, 8, 3, 1, 5}}, Sex::MALE};
  Student student4{"Czarek", "Nowak", {}, {5}, {{1}}, Sex::MALE};
  Student student5{"Wiktoria", "Pozarska", adress, {7}, {{1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 6}}, Sex::FEMALE};
  Student student6{"Konstanty", "Smith", adress, {33}, {{1, 2, 3, 4, 5, 6, 7, 2, 9, 1, 5}}, Sex::MALE};
  Student student7{"Czeslaw", "Gwint", {}, {54}, {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}, Sex::MALE};
  Student student8{"Wiktor", "Adamski", adress, {17}, {{1, 2, 3, 1, 2, 2, 2, 2, 2, 2, 2}}, Sex::MALE};

  data.add(student5);
  data.add(student4);
  data.add(student3);
  data.add(student2);
  data.add(student);
  data.add(student6);
  data.add(student7);
  data.add(student8);

  std::vector<Student> expected{student8, student7, student3, student, student4, student5, student2, student6};

  EXPECT_NE(data.getStudents(), expected);
  data.sortByLastName();
  EXPECT_EQ(data.getStudents(), expected);
}

TEST_F(DataBaseTests, deleteByIndex)
{
  Student student2{"Patryk", "Puzon", adress, {1}, {{2, 2, 3, 4, 5, 6, 7, 8, 9, 1, 5}}, Sex::MALE};
  Student student3{"Kacper", "Kowalski", adress, {3}, {{9, 3, 3, 4, 5, 6, 7, 8, 3, 1, 5}}, Sex::MALE};
  Student student4{"Czarek", "Nowak", {}, {5}, {{1}}, Sex::MALE};
  Student student5{"Wiktoria", "Pozarska", adress, {7}, {{1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 6}}, Sex::FEMALE};
  Student student6{"Konstanty", "Smith", adress, {33}, {{1, 2, 3, 4, 5, 6, 7, 2, 9, 1, 5}}, Sex::MALE};
  Student student7{"Czeslaw", "Gwint", {}, {54}, {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}, Sex::MALE};
  Student student8{"Wiktor", "Adamski", adress, {17}, {{1, 2, 3, 1, 2, 2, 2, 2, 2, 2, 2}}, Sex::MALE};

  data.add(student5);
  data.add(student4);
  data.add(student3);
  data.add(student2);
  data.add(student);
  data.add(student6);
  data.add(student7);
  data.add(student8);

  auto sizeBefore = data.getDatabaseSize();

  EXPECT_EQ(data.deleteByIndex({5}), 1);
  EXPECT_LT(data.getDatabaseSize(), sizeBefore);
}

TEST_F(DataBaseTests, writingToFile)
{

  Student student2{"Patryk", "Puzon", adress, {1}, {{2}}, Sex::MALE};
  Student student3{"Kacper", "Kowalski", adress, {3}, {{4}}, Sex::MALE};
  Student student4{"Czarek", "Nowak", {}, {5}, {{6}}, Sex::MALE};
  Student student5{"Wiktor", "Kowalski", adress, {7}, {{8}}, Sex::MALE};

  data.add(student);
  data.add(student2);
  data.add(student3);
  data.add(student4);
  data.add(student5);

  data.sortByLastName();

  data.display();
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

int main(int argc, char **argv)
{

  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}