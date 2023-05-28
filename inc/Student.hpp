#pragma once

#include <iostream>
#include <string>
#include <vector>

struct Adress {

  std::string city{'-'};
  std::string street{'-'};
  std::string postCode{'-'};
  int apartamentNumber{NULL};
  int flatNumber{NULL};
};

enum class Sex { MALE, FEMALE };

class Student {

private:
  std::string const name_;
  std::string const lastName_;
  Adress adress_;
  std::vector<int> const v_index_{6};
  std::vector<int> const v_pesel_{11};
  Sex const sex_;

public:
  Student(std::string name, std::string lastName, Adress adress,
          std::vector<int> index, std::vector<int> pesel, Sex sex);

  std::string getName() const { return name_; }
  std::string getLastName() const { return lastName_; }
  Adress getAddres() const { return adress_; }
  std::vector<int> getIndex() const { return v_index_; }
  std::vector<int> getPesel() const { return v_pesel_; }
  Sex getSex() const { return sex_; }


  bool operator==(const Student &s1) const;
  bool operator!=(const Student &s1) const;
};


std::ostream &operator<<(std::ostream &os, const Adress &adress);
std::ostream &operator<<(std::ostream &os, const Student &obj);


