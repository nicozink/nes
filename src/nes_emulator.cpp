/*
Copyright � 2012, Nico Zink
All rights reserved.
*/

#include "nes_emulator.h" 

// Local Includes
#include "main.h"

// Project Includes
#include "librocket/system_interface.h"
#include "librocket/gui_renderer.h"

// External Includes
#include "Rocket/Core.h" 
#include <iostream>
#include <string>

// Runs the main program.
int run(std::string rom_location)
{
  SystemInterface system_interface;
  GuiRenderer gui_renderer;
  
  Rocket::Core::SetRenderInterface(&gui_renderer);
	Rocket::Core::SetSystemInterface(&system_interface);
  
  Rocket::Core::Initialise();
  
  return 0;
}
