#include "window.h"

Window::Window(Rocket::Core::Context* context, const std::string file)
{
	document = context->LoadDocument(file.c_str());
}

Window::~Window()
{
	
}

void Window::Show()
{
	document->Show();
}

void Window::Hide()
{
	document->Hide();
}
