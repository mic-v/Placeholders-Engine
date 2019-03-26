#include "Texture.h"


int numbercolumns = 2;
//
//
Texture::Texture() {

}
Texture::~Texture() {
	Unload();
}

void Texture::generateMipMaps()
{
	glGenerateTextureMipmap(this->_TexHandle);
	glTextureParameterf(this->_TexHandle, GL_TEXTURE_MAX_ANISOTROPY, 16.f);
}

bool Texture::LoadTexture(const std::string& filename) {
	int height;
	int width;
	int numComponents;
	//Textobj = imgstuffs
	//Textobj = SOIL_load_OGL_texture();

	unsigned char* imageData = SOIL_load_image(filename.c_str(), &width, &height, &numComponents, SOIL_LOAD_RGBA);
	
	if (imageData == NULL) {
		cout << "LOADING IMAGE FAILED" << endl;
		return false;
	
	}
	glGenTextures(1, &Textobj);
	glBindTexture(GL_TEXTURE_2D, Textobj);
	glGenerateMipmap(GL_TEXTURE_2D);



	//what happens when the image goes outside of height/width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);



	//what happens if image doesn't take up height/width
	//GL_LINEAR interpolates between the colors that are there
	//min = when the texture takes up fewer pixels than its resolution
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//mag = when the texture takes up more pixels than its resolution 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//sends textimage to opengl, (what kind of texture, level is for mipmapping, how opengl stores individual pixels on the gpu, 
	// height, width, border, the format of the data we're sending TO the gpu, data type(unsigned char), imagedata) 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	SOIL_free_image_data(imageData);


	//if (Textobj == 0) {
	//	std::cout << "Texture failed to load" << SOIL_last_result() << std::endl;
	//	return false;
	//}

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	//glBindTexture(GL_TEXTURE_2D, 0);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //u axis
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //v axis
	return true;
}
void Texture::Unload() {
	if (Textobj != 0) {
		glDeleteTextures(1, &Textobj);
		Textobj = 0;
	}
}
void Texture::Bind(unsigned int unit) {
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, Textobj);
}
void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::Bind3D(int textureSlot) const {
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(this->_Target, this->_TexHandle);
}
void Texture::unbind3D(int textureSlot) const
{
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(this->_Target, GL_NONE);
	
}