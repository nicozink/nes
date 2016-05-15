/*
Copyright © Nico Zink
All rights reserved.
*/

#ifndef RENDERER_H
#define RENDERER_H

// Local Includes

// Project Includes

// External Includes
#include <array>

// Required classes
class SystemState;

// A class which displays the screen for each frame.
class Renderer
{
	public:

		Renderer();

		void StartRender();
		void EndRender();
		void DrawScreen();

	private:

		double GetScreenX(int c);

		double GetScreenY(int r);

		void DrawQuad(int r, int c);

		std::array<uint8_t, 100> texture;
};

#endif
