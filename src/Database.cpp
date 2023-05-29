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

template <typename F>
auto Database::findStudent(const F*func){
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
// Student searchByLastName(std::string const lastName);
// Student searchByIndex(std::vector<int> const index);
// Student searchByPesel(std::vector<int> const index);

// void sortbByPesel();
// void sortByIndex();

// bool deleteByIndex(std::vector<int> const index);