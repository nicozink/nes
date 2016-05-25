#ifndef ROCKETINVADERSELEMENTGAME_H
#define ROCKETINVADERSELEMENTGAME_H

#include <array>

#include <Rocket/Core/Element.h>

class NesElement : public Rocket::Core::Element
{
public:
	NesElement(const Rocket::Core::String& tag);
	
	virtual ~NesElement();

protected:

	void OnUpdate() override;
	
	void OnRender() override;

private:

	std::array<uint8_t, 100> texture;
};

#endif
