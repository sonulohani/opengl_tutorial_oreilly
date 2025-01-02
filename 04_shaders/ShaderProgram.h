#pragma once

#include "GL/glew.h"
#include <string>

class ShaderProgram {
public:
  ShaderProgram();
  virtual ~ShaderProgram();

  enum ShaderType { VERTEX, FRAGMENT, PROGRAM };

  bool loadShader(const char *vsFileName, const char *fsFileName);

  void use();

private:
  std::string fileToString(const char *fileName);
  void compileCompileError(GLuint shader, ShaderType type);

  GLuint mHandle;
};
