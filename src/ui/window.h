#ifndef WINDOW_H
#define WINDOW_H

#include "Rocket/Core.h" 

class Window
{
public:

	Window(Rocket::Core::Context* context, const std::string file);
	
	virtual ~Window();

	void Show();
	
	void Hide();
	
private:

	Rocket::Core::ElementDocument* document;
};

#endif
