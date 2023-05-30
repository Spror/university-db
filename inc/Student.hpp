#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cstdint>
#include <Pesel.hpp>


struct Adress
{

  std::string city{'-'};
  std::string street{'-'};
  std::string postCode{'-'};
  int apartamentNumber{NULL};
  int flatNumber{NULL};
};

enum class Sex
{
  MALE,
  FEMALE
};

class Student
{

private:
  std::string  name_;
  std::string  lastName_;
  Adress adress_;
  std::array<uint8_t,6>  a_index_{6};
  Pesel pesel_;
  Sex sex_;

public:
  Student(std::string name, std::string lastName, Adress adress,
          std::array<uint8_t,6>  index, Pesel pesel, Sex sex);

  std::string getName() const { return name_; }
  std::string getLastName() const { return lastName_; }
  Adress getAddres() const { return adress_; }
  std::array<uint8_t,6>  getIndex() const { return a_index_; }
  Pesel getPesel() const { return pesel_; }
  Sex getSex() const { return sex_; }

  bool operator==(const Student &s1) const;
  bool operator!=(const Student &s1) const;
};

std::ostream &operator<<(std::ostream &os, const Adress &adress);
std::ostream &operator<<(std::ostream &os, const Student &obj);
