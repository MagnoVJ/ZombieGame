#pragma once

#include <GL/glew.h>

namespace Engine {

	class Texture2D {

	public:
		GLuint id;
		GLuint width, height;
		GLuint internal_format;
		GLuint image_format;

		GLuint wrap_s;
		GLuint wrap_t;
		GLuint filter_min;
		GLuint filter_max;

		Texture2D();

		GLuint getTextureID() const;

		void generate(GLuint width, GLuint height, unsigned char* data);

		void bind() const;

	};

}