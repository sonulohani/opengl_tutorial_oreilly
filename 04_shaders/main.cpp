#include "ShaderProgram.h"
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
bool gWireFrame = false;

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

    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
      gWireFrame = !gWireFrame;
      if (gWireFrame) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      }
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
    -0.5f,  0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
  };
  // clang-format on

  GLuint indices[] = {
      0, 1, 2, // first triangle
      0, 2, 3  // second triangle
  };

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (GLvoid *)0);

  glEnableVertexAttribArray(0);

  GLuint ibo;
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  ShaderProgram shaderProgram;
  shaderProgram.loadShader("shaders/vertexShader.glsl",
                           "shaders/fragmentShader.glsl");
  shaderProgram.use();

  while (!glfwWindowShouldClose(gWindow)) {
    showFPS(gWindow);
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.use();

    GLfloat time = glfwGetTime();
    GLfloat greenValue = (sin(time) / 2.0f) + 0.5f;
    glm::vec2 pos;
    pos.x = (sin(time) / 2.0f) + 0.5f;
    pos.y = (sin(time) / 2.0f) + 0.5f;
    shaderProgram.setUniform("posOffset", pos);
    shaderProgram.setUniform("vertColor",
                             glm::vec4(1.0f, greenValue, 0.31f, 1.0f));

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glfwSwapBuffers(gWindow);
  }

  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ibo);

  glfwTerminate();

  return 0;
}
