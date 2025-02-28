#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Texture2D {
public:
  Texture2D();
  virtual ~Texture2D();
  bool loadTexture(const std::string &textureFileName,
                   bool generateMipMaps = true);
  void bindTexture(GLuint textureUnit = 0);

private:
  GLuint mTexture;
};
