#include <Database.hpp>

bool Database::add(Student const &student) {
  for (const auto &it : v_students_) {
    if (student == it) {
      std::cerr << "There exist that student in database" << std::endl;
      return false;
    }
  }

  v_students_.push_back(student);
  return true;
}

void Database::display() {

  for (const auto &it : v_students_) {
    std::cout << it << std::endl;
  }
}

template <typename F> auto Database::findStudent(const F *func) {
  std::vector<Student> matchingStudents;
  std::copy_if(v_students_.begin(), v_students_.end(),
               std::back_inserter(matchingStudents), (*func));
  return matchingStudents;
}

std::vector<Student> Database::searchByLastName(std::string const lastName) {

  auto condition = [lastName](Student const &s) {
    return s.getLastName() == lastName;
  };

  return findStudent(&condition);
}

std::vector<Student> Database::searchByPesel(std::vector<int> const pesel) {
  auto condition = [pesel](Student const &s) { return s.getPesel() == pesel; };

  return findStudent(&condition);
}
