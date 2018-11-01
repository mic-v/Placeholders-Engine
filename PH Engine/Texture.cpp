#include "Texture.h"

int height = 1;
int width = 1;
int numbercolumns = 2;
//
//
Texture::Texture() {

}
Texture::~Texture() {
	Unload();
}
bool Texture::LoadTexture(const char filename) {
	
	//Textobj = imgstuffs
	//Textobj = SOIL_load_OGL_texture();

	unsigned char* tempimage = SOIL_load_image(&filename, &width, &height, 0, SOIL_LOAD_RGBA);
	
	SOIL_free_image_data(tempimage);
	if (Textobj == 0) {
		std::cout << "Texture failed to load" << SOIL_last_result() << std::endl;
		return false;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempimage);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //u axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //v axis
	return true;
}
void Texture::Unload() {
	if (Textobj != 0) {
		glDeleteTextures(1, &Textobj);
		Textobj = 0;
	}
}
void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, Textobj);
}
void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}