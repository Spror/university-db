#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cstdint>
#include <Pesel.hpp>
#include <Person.hpp>

class Student : public Person
{

private:
  std::array<uint8_t, 6> a_index_;

public:
  Student(std::string name, std::string lastName, Adress adress,
          std::array<uint8_t, 6> index, Pesel pesel, Sex sex);

   std::array<uint8_t, 6> getIndex() const { return a_index_; }
  virtual std::ostream& output(std::ostream& os) const;
  virtual std::string getProffesion() const {return "Student";}
};


