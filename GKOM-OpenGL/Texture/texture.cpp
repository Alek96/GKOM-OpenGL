#include "texture.h"
#include <SOIL.h>
#include <stdexcept>

Texture::Texture(std::string filename) {
    int width, height;
    unsigned char* imgData;
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    imgData = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    if (imgData == nullptr) {
        throw std::runtime_error("Could not load file: " + filename);
    }
    
    glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(imgData);
}