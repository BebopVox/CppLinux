#include <iostream>
#include <exception>

using namespace std;

// Exception struct
struct MyException : public exception {
  const char * what () const throw () {
    return "C++ Exception";
  }
};

// Exception class
class MyException: public exception {
  virtual const char* what() const throw() {
    return "My exception happened";
  }
} MyEx;

int main() {
   try {
      throw MyException();
   } catch(MyException& e) {
      std::cout << "MyException caught" << std::endl;
      std::cout << e.what() << std::endl;
   } catch(std::exception& e) {
      //Other errors
   }
}
