#include "Texture2D.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

Texture2D::Texture2D() : mTexture(0) {}

Texture2D::~Texture2D() {
  if (mTexture != 0) {
    glDeleteTextures(1, &mTexture);
  }
}

bool Texture2D::loadTexture(const std::string &textureFileName,
                            bool generateMipMaps) {
  int width, height, channels;

  // Flip the image
  stbi_set_flip_vertically_on_load(true);

  unsigned char *data =
      stbi_load(textureFileName.c_str(), &width, &height, &channels, STBI_rgb_alpha);

  if (data == nullptr) {
    std::cerr << "Failed to load texture: " << textureFileName << std::endl;
    return false;
  }

  glGenTextures(1, &mTexture);
  glBindTexture(GL_TEXTURE_2D, mTexture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  generateMipMaps ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);

  if (generateMipMaps) {
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  stbi_image_free(data);
  glBindTexture(GL_TEXTURE_2D, 0);
  return true;
}

void Texture2D::bindTexture(GLuint textureUnit) {
  glActiveTexture(GL_TEXTURE0 + textureUnit);
  glBindTexture(GL_TEXTURE_2D, mTexture);
}
