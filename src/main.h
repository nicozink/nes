/*
Copyright © 2012, Nico Zink
All rights reserved.
*/

#ifndef MAIN_H
#define MAIN_H

// System includes
#include <string>

// Main method which initialises the program.
// @param argc The number of arguments.
// @param argv The arguments.
// @returns The success code.
int main(int argc, char** argv);

// Runs the main program.
// @param rom_location The file location of the ROM to run.
int run(std::string param);

#endif

