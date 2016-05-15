#include "gui_renderer.h"

#if OPERATING_SYSTEM == WINDOWS
#include <windows.h>
#endif

#include <GL/glew.h>

void GuiRenderer::EnableScissorRegion(bool enable)
{
	if (enable)
	{
		glEnable(GL_SCISSOR_TEST);
	}
	else
	{
		glDisable(GL_SCISSOR_TEST);
	}
}

bool GuiRenderer::GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions)
{
	GLuint textureId;

	glGenTextures(1, &textureId);					// Create The Texture

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, source_dimensions.x, source_dimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, source);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	texture_handle = (Rocket::Core::TextureHandle)textureId;
	
	return true;
}

bool GuiRenderer::LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source)
{
	FILE *file = fopen(source.CString(), "rb");

	fseek(file, 18, SEEK_CUR);

	unsigned int width;
	unsigned int height;
	fread(&width, 4, 1, file);
	fread(&height, 4, 1, file);

	short int bpp;
	short int planes;
	fread(&bpp, 2, 1, file);
	fread(&planes, 2, 1, file);

	fseek(file, 24, SEEK_CUR);

	long input_size = width * height * 3;
	unsigned char* contents = new unsigned char[input_size];

	fread(contents, input_size, 1, file);

	long output_size = width * height * 4;
	unsigned char* texture_data = new unsigned char[output_size];
	
	int i = 0;
	int j = 0;
	while (i != output_size)
	{
		texture_data[i] = contents[j + 2];
		texture_data[i + 1] = contents[j + 1];
		texture_data[i + 2] = contents[j];
		texture_data[i + 3] = 255;
		
		i += 4;
		j += 3;
	}

	fclose(file);
	
	texture_dimensions.x = width;
	texture_dimensions.y = height;
	
	bool success = GenerateTexture(texture_handle, texture_data, texture_dimensions);
	
	delete[] contents;
	delete[] texture_data;
	
	return success;
}

void GuiRenderer::ReleaseTexture(Rocket::Core::TextureHandle texture)
{
	glDeleteTextures(1, (GLuint*)texture);
}

void GuiRenderer::RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation)
{
	glPushMatrix();
	glTranslatef(translation.x, translation.y, 0);

	glVertexPointer(2, GL_FLOAT, sizeof(Rocket::Core::Vertex), &vertices[0].position);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Rocket::Core::Vertex), &vertices[0].colour);

	if (!texture)
	{
		glDisable(GL_TEXTURE_2D);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	else
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, (GLuint) texture);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Rocket::Core::Vertex), &vertices[0].tex_coord);
	}

	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, indices);

	glPopMatrix();
}

void GuiRenderer::SetScissorRegion(int x, int y, int width, int height)
{
	glScissor(x, y, width, height);
}
