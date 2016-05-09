/*
Copyright © 2012, Nico Zink
All rights reserved.
*/

#include "main.h" 

// Local Includes

// Project Includes

// External Includes
#include <string>
#include <iostream>

// Main method which initialises the program.
// @param argc The number of arguments.
// @param argv The arguments.
// @returns The success code.
int main(int argc, char** argv)
{
  if (argc == 2)
  {
    std::string param(argv[1]);
    
    if (param == "-v" || param == "--version")
    {
      std::cout << "0.0.0.0" << std::endl;
    }
    else
    {
      return run(param);
    }
  }
  else
  {
    return run("");
  }
  
  return 0;
}
