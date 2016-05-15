/*
Copyright © Nico Zink
All rights reserved.
*/

#include "display.h" 

// Local Includes
#include "renderer.h"

// Project Includes

// External Includes
#include <cstdlib>
#include <iostream>
#include <SDL/SDL.h>

Display::Display()
{
  std::cout << "Initialising SDL" << std::endl;

  // Initialize SDL and the specified subsystems.
  // We only require the video subsystem.
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    std::cout << "Failed initialising SDL: " << SDL_GetError() << std::endl;

    exit(EXIT_FAILURE);
  }

  std::cout << "Getting hardware information" << std::endl;

  // Get information about the current video hardware
  const SDL_VideoInfo* info = SDL_GetVideoInfo();

  if (info == nullptr)
  {
    std::cout << "Failed getting hardware information: " << SDL_GetError() << std::endl;

    exit(EXIT_FAILURE);
  }

  int bpp = info->vfmt->BitsPerPixel;

  // Set the red channel to at least 8 bits.
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  // Set the green channel to at least 8 bits.
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  // Set the blue channel to at least 8 bits.
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  // Set the depth size to at least 24 bits.
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  // Enable double buffering.
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);

  std::cout << "Opening the display";

  // Set the video mode to create a OpenGL in window mode.
  if (SDL_SetVideoMode(800, 400, bpp, SDL_OPENGL) == nullptr)
  {
    std::cout << "Setting of the video mode failed: " << SDL_GetError() << std::endl;

    exit(EXIT_FAILURE);
  }

  // Name the OpenGL window.
  SDL_WM_SetCaption("Chip 8", "Chip 8");

  renderer = new Renderer();
}

Display::~Display()
{
  delete renderer;
}

void Display::PreRender()
{
  renderer->StartRender();
}

void Display::PostRender()
{
  renderer->EndRender();
  
  SDL_GL_SwapBuffers();
}

void Display::Render()
{
  renderer->DrawScreen();
}
