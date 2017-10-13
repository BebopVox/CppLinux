class MyException : public std::exception
{
  std::string message;
public:
  MyException(std::string const &what_arg) : message(what_arg) {}
  MyException(char const * what_arg) : message(what_arg) {}
  const char* what() const { return message.c_str(); }
};
