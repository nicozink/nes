/*
Copyright © Nico Zink
All rights reserved.
*/

#include "renderer.h" 

// Local Includes
#include "system.h"

// Project Includes

// External Includes
#if OPERATING_SYSTEM == WINDOWS
#include <windows.h>
#endif

#include <GL/glew.h>
#include <iostream>
#include <algorithm>
#include <vector>

static void CheckGLError()
{
  GLenum error = GL_NO_ERROR;

  error = glGetError();

  if (GL_NO_ERROR != error)
  {
    std::cout << "OpenGL error: " << error << std::endl;
  }
}

Renderer::Renderer()
{
  GLenum err = glewInit();

  if (GLEW_OK != err)
  {
    std::cout << "Error loading GLEW: " << glewGetErrorString(err) << std::endl;
  }
  else
  {
    std::cout << "Using GLEW: " << glewGetString(GLEW_VERSION) << std::endl;
  }

  CheckGLError();

  /*glViewport(0, 0, 800, 400);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(0, 800, 400, 0, -1, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_SMOOTH);
  glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
  
  glEnable(GL_MULTISAMPLE);*/

  int width = 800;
  int height = 400;
  
  glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
  
  glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
  
  glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  CheckGLError();
}

void Renderer::StartRender()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.5f, 0.5f, 0.5f, 1.0);
  glLoadIdentity();

  CheckGLError();
}

void Renderer::EndRender()
{
  
}

void Renderer::DrawScreen()
{
  glColor3f(1.0, 0.0, 0.0);
  
  glBegin(GL_QUADS);
  
  glVertex3d(10.0, 20.0, 0.0);
  glVertex3d(30.0, 380.0, 0.0);
  glVertex3d(780.0, 390.0, 0.0);
  glVertex3d(790.0, 50.0, 0.0);
  
  glEnd();
}