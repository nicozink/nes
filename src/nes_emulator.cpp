/*
Copyright � 2012, Nico Zink
All rights reserved.
*/

#include "nes_emulator.h" 

// Local Includes
#include "main.h"

// Project Includes
#include "librocket/nes_element.h"
#include "librocket/system_interface.h"
#include "librocket/gui_renderer.h"
#include "graphics/display.h"
#include "ui/window.h"

// External Includes
#include "Rocket/Core.h" 
#include <iostream>
#include <string>

// Runs the main program.
int run(std::string rom_location)
{
	Display display;

	SystemInterface system_interface;
	GuiRenderer gui_renderer;

	Rocket::Core::SetRenderInterface(&gui_renderer);
	Rocket::Core::SetSystemInterface(&system_interface);

	Rocket::Core::Initialise();

	// Load the font faces required for Invaders.
	Rocket::Core::FontDatabase::LoadFontFace(
		"resources/fonts/Delicious-Roman.otf",
		"Delicious",
		Rocket::Core::Font::STYLE_NORMAL,
		Rocket::Core::Font::WEIGHT_NORMAL);
	Rocket::Core::FontDatabase::LoadFontFace(
		"resources/fonts/Delicious-Italic.otf",
		"Delicious",
		Rocket::Core::Font::STYLE_ITALIC,
		Rocket::Core::Font::WEIGHT_NORMAL);
	Rocket::Core::FontDatabase::LoadFontFace(
		"resources/fonts/Delicious-Bold.otf",
		"Delicious",
		Rocket::Core::Font::STYLE_NORMAL,
		Rocket::Core::Font::WEIGHT_BOLD);
	Rocket::Core::FontDatabase::LoadFontFace(
		"resources/fonts/Delicious-BoldItalic.otf",
		"Delicious",
		Rocket::Core::Font::STYLE_ITALIC,
		Rocket::Core::Font::WEIGHT_BOLD);
	
	Rocket::Core::Context* context = Rocket::Core::CreateContext("main", Rocket::Core::Vector2i(800, 400));

	// Register Invader's custom element and decorator instancers.
	Rocket::Core::ElementInstancer* element_instancer = new Rocket::Core::ElementInstancerGeneric< NesElement >();
	Rocket::Core::Factory::RegisterElementInstancer("game", element_instancer);
	element_instancer->RemoveReference();

	Window main(context, "resources/main.rml");
	main.Show();
	
	Window file(context, "resources/window/file_dialog.rml");
	file.Show();
	
	while (true)
	{
		context->Update();
		
		display.PreRender();
		
		context->Render();
		
		display.PostRender();
	}

	while (true) {}
	
	return 0;
}
