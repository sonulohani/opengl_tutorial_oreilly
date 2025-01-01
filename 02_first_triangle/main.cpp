#include <iostream>
#include <sstream>
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

const char *APP_TITLE = "Introduction to modern opengl - hello window";
const int gWindowWidth = 800;
const int gWindowHeight = 600;
bool gFullScreen = false;
GLFWwindow *gWindow = nullptr;

const GLchar *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 vertColor;\n"
    "void main()\n"
    "{\n"
    "   vertColor = aColor;\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const GLchar *fragmentShaderSource = "#version 330 core\n"
                                     "in vec3 vertColor;\n"
                                     "out vec4 FragColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   FragColor = vec4(vertColor, 1.0);\n"
                                     "}\n\0";

bool initOpengl() {
  if (!glfwInit()) {
    std::cerr << "GLFW Initialization failed" << std::endl;
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  if (gFullScreen) {
    GLFWmonitor *pMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *pVideoMode = glfwGetVideoMode(pMonitor);
    gWindow = glfwCreateWindow(pVideoMode->width, pVideoMode->height, APP_TITLE,
                               pMonitor, nullptr);
  } else {

    gWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, APP_TITLE, nullptr,
                               nullptr);
    if (gWindow == nullptr) {
      std::cerr << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return false;
    }
  }

  glfwMakeContextCurrent(gWindow);

  glfwSetKeyCallback(gWindow, [](GLFWwindow *window, int key, int scancode,
                                 int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
  });

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "GLEW Initialization failed" << std::endl;
    return false;
  }

  glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

  return true;
}

void showFPS(GLFWwindow *window) {
  static double previousSeconds = 0.0;
  static int frameCount = 0;
  double currentSeconds;
  double elapsedSeconds;
  currentSeconds = glfwGetTime();
  elapsedSeconds = currentSeconds - previousSeconds;
  if (elapsedSeconds > 0.25) {
    previousSeconds = currentSeconds;
    double fps = (double)frameCount / elapsedSeconds;

    std::ostringstream fpsStream;
    fpsStream.precision(2);
    fpsStream << APP_TITLE << " - FPS: " << fps;
    glfwSetWindowTitle(window, fpsStream.str().c_str());

    frameCount = 0;
  }
  frameCount++;
}

int main(int argc, char *argv[]) {
  if (!initOpengl()) {
    std::cerr << "GLFW Initialization failed" << std::endl;
    return -1;
  }

  // clang-format off
  GLfloat vertices[] = {
    // positions
    0.0f, 0.5f, 0.0f, // Top
    -0.5f, -0.5f, 0.0f,// Right
    0.5f, -0.5f, 0.0f }; // Left
  
  GLfloat vert_color[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f };

  // clang-format on

  GLuint vbo, vb02;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &vb02);
  glBindBuffer(GL_ARRAY_BUFFER, vb02);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vert_color), vert_color, GL_STATIC_DRAW);

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Position attribute
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (GLvoid *)0);

  glEnableVertexAttribArray(0);

  // COlor attribute
  glBindBuffer(GL_ARRAY_BUFFER, vb02);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (GLvoid *)0);
  glEnableVertexAttribArray(1);

  // create the shader
  GLuint vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  // report error
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  GLuint fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  GLuint shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  while (!glfwWindowShouldClose(gWindow)) {
    showFPS(gWindow);
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(gWindow);
  }

  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteProgram(shaderProgram);

  glfwTerminate();

  return 0;
}
