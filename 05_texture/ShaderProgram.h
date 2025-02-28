#pragma once

#include "GL/glew.h"
#include <glm/glm.hpp>
#include <map>
#include <string>

class ShaderProgram {
public:
  ShaderProgram();
  virtual ~ShaderProgram();

  enum ShaderType { VERTEX, FRAGMENT, PROGRAM };

  bool loadShader(const char *vsFileName, const char *fsFileName);

  void use();

  void setUniform(const char *name, const glm::vec2 &value);
  void setUniform(const char *name, const glm::vec3 &value);
  void setUniform(const char *name, const glm::vec4 &value);

  auto getProgramHandle() const { return mHandle; }

private:
  std::string fileToString(const char *fileName);
  void compileCompileError(GLuint shader, ShaderType type);
  GLint getUniformLocation(const char *name);

  GLuint mHandle;
  std::map<std::string, GLint> mUniformLocations;
};
