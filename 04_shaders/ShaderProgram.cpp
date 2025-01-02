#include "ShaderProgram.h"

#include <fstream>
#include <iostream>

ShaderProgram::ShaderProgram() : mHandle(0) {}

ShaderProgram::~ShaderProgram() {
  if (mHandle != 0) {
    glDeleteProgram(mHandle);
  }
}

bool ShaderProgram::loadShader(const char *vsFileName, const char *fsFileName) {
  std::string vsSource = fileToString(vsFileName);
  std::string fsSource = fileToString(fsFileName);

  const char *vsSourceChar = vsSource.c_str();
  const char *fsSourceChar = fsSource.c_str();

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vsSourceChar, NULL);
  glCompileShader(vs);
  compileCompileError(vs, VERTEX);

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fsSourceChar, NULL);
  glCompileShader(fs);
  compileCompileError(fs, FRAGMENT);

  mHandle = glCreateProgram();
  glAttachShader(mHandle, vs);
  glAttachShader(mHandle, fs);
  glLinkProgram(mHandle);
  compileCompileError(mHandle, PROGRAM);
  glValidateProgram(mHandle);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return true;
}

void ShaderProgram::use() { glUseProgram(mHandle); }

std::string ShaderProgram::fileToString(const char *fileName) {
  std::string content;
  std::ifstream fileStream(fileName, std::ios::in);
  if (!fileStream.is_open()) {
    std::cerr << "Could not read file " << fileName << ". File does not exist."
              << std::endl;
    return "";
  }
  std::string line = "";
  while (!fileStream.eof()) {
    std::getline(fileStream, line);
    content.append(line + "\n");
  }
  fileStream.close();
  return content;
}

void ShaderProgram::compileCompileError(GLuint shader, ShaderType type) {
  int success;
  char infoLog[512];
  if (type == PROGRAM) {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 512, NULL, infoLog);
      std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                << infoLog << std::endl;
    }
  } else {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 512, NULL, infoLog);
      std::cerr << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n"
                << infoLog << std::endl;
    }
  }
}
