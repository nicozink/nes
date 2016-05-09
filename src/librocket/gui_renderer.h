#include "Rocket/Core/RenderInterface.h"

class GuiRenderer : public Rocket::Core::RenderInterface
{
	/// Called by Rocket when it wants to render geometry that the application does not wish to optimise. Note that
	/// Rocket renders everything as triangles.
	/// @param[in] vertices The geometry's vertex data.
	/// @param[in] num_vertices The number of vertices passed to the function.
	/// @param[in] indices The geometry's index data.
	/// @param[in] num_indices The number of indices passed to the function. This will always be a multiple of three.
	/// @param[in] texture The texture to be applied to the geometry. This may be NULL, in which case the geometry is untextured.
	/// @param[in] translation The translation to apply to the geometry.
	void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation) override;

	/// Called by Rocket when it wants to enable or disable scissoring to clip content.
	/// @param[in] enable True if scissoring is to enabled, false if it is to be disabled.
	void EnableScissorRegion(bool enable) override;

	/// Called by Rocket when it wants to change the scissor region.
	/// @param[in] x The left-most pixel to be rendered. All pixels to the left of this should be clipped.
	/// @param[in] y The top-most pixel to be rendered. All pixels to the top of this should be clipped.
	/// @param[in] width The width of the scissored region. All pixels to the right of (x + width) should be clipped.
	/// @param[in] height The height of the scissored region. All pixels to below (y + height) should be clipped.
	void SetScissorRegion(int x, int y, int width, int height) override;
};