#include "Rocket/Core/SystemInterface.h"

class SystemInterface : public Rocket::Core::SystemInterface
{
	/// Get the number of seconds elapsed since the start of the application.
	/// @return Elapsed time, in seconds.
	float GetElapsedTime() override;
};