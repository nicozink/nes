#include "Rocket/Core/RenderInterface.h"

class GuiRenderer : public Rocket::Core::RenderInterface
{
	void EnableScissorRegion(bool enable) override;
	bool GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions) override;
	bool LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source) override;
	void ReleaseTexture(Rocket::Core::TextureHandle texture) override;
	void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation) override;
	void SetScissorRegion(int x, int y, int width, int height) override;
};