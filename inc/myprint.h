#pragma once

#include <iostream>
#include <string>


namespace utils
{
  static void PrintHeader1(const std::string s)
  {
    std::cout << "############## " << s << std::endl;
  }

  static void PrintHeader2(const std::string s)
  {
    std::cout << "##############" << s << std::endl;
  }

  static void Print1(const std::string s)
  {
    std::cout << "    " << s;
  }

  static void Print2(const std::string s)
  {
    std::cout << "        " << s;
  }

  static void Print3(const std::string s)
  {
    std::cout << "            " << s;
  }

  static void Print4(const std::string s)
  {
    std::cout << "                " << s;
  }

}


