#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::stringstream;

#define _countof(a) (sizeof(a)/sizeof(*(a)))

class exception : public std::exception {
public:
  exception(std::string const &message) : msg_(message) { }
  virtual char const *what() const noexcept { return msg_.c_str(); }

private:
  string msg_;
};
