#include "Texture.h"

//Constructor that generates the Texture !
Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {

	// Assigns the type of the texture to the texture object.
    type = texType;

	// Gets the widtch height and the num color channel of image.
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true); // we have this, as opengl reads from from bottom left corner to top right corner, while stb reads from top left corner to bottom right corner. Basically, this makes our texture show up right side up
	// Reads the image from a filre and stores it in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	//the texture object itself
	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	// here we choose nearest neighbor or linear.
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	// repeating wahooie
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//gl plan to order
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(texType, GL_TEXTURE_BORDER_COLOR, flatColor};

	// gen texture
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	glGenerateMipmap(texType);

	/*
	The most common color channels are
	GL_RGBA -> JPEG files
	GL_RGB -> PNG files
	*/


	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}

// Assignts a texture unit
void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
	GLuint texUniform = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1f(texUniform, unit);
}

// binds texture
void Texture::Bind() {
	glBindTexture(type, ID);
}

// unbinds texture
void Texture::Unbind() {
	glBindTexture(type, 0);
}

// deletes texture
void Texture::Delete() {
	glDeleteTextures(1, &ID);
}