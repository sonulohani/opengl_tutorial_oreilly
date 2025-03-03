#include "ShaderProgram.h"
#include <iostream>
#include <sstream>
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Texture2D.h"
#include "glm/gtc/matrix_transform.hpp"

const char *APP_TITLE = "Introduction to modern opengl - hello window";
int gWindowWidth = 1024;
int gWindowHeight = 768;
bool gFullScreen = false;
GLFWwindow *gWindow = nullptr;
bool gWireFrame = false;
const std::string texture1FileName = "airplane.jpg";
// const std::string texture2FileName = "crate.jpg";

void glfw_OnFramebufferSizeCallback(GLFWwindow *window, int width, int height);

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
  glfwSetFramebufferSizeCallback(gWindow, glfw_OnFramebufferSizeCallback);

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

  glViewport(0, 0, gWindowWidth, gWindowHeight);
  glEnable(GL_DEPTH_TEST);

  return true;
}

void glfw_OnFramebufferSizeCallback(GLFWwindow *window, int width, int height) {
  gWindowWidth = width;
  gWindowHeight = height;

  glViewport(0, 0, width, height);
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
    // front face
    -1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, 0.0f,

    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
    -1.0f,  1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,

    -1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
    -1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

     1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
     1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
     1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

    -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
     1.0f, -1.0f, -1.0f,  1.0f, 1.0f,
     1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
     1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,

    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f
  };
  // clang-format on

  glm::vec3 cubePos = glm::vec3(0.f, 0.f, -5.0f);

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                        (GLvoid *)0);

  glEnableVertexAttribArray(0);

  // tex coord
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                        (GLvoid *)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);


  ShaderProgram shaderProgram;
  shaderProgram.loadShader("shaders/vertexShader.glsl",
                           "shaders/fragmentShader.glsl");

  Texture2D texture1;
  texture1.loadTexture(texture1FileName, true);

  // Texture2D texture2;
  // texture2.loadTexture(texture2FileName, true);

  float cubeAngle = 0.f;
  double lastTime = glfwGetTime();

  while (!glfwWindowShouldClose(gWindow)) {
    showFPS(gWindow);

    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);
    lastTime = currentTime;

    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture1.bindTexture(0);
    // texture2.bindTexture(1);

    glUniform1i(glGetUniformLocation(shaderProgram.getProgramHandle(), "myTexture1"), 0);

    cubeAngle += deltaTime * 50.f;
    if(cubeAngle > 360.f) {
      cubeAngle = 0.f;
    }

    glm::mat4 model, view, projection;

    model = glm::mat4(1.0f);
    model = glm::translate(model, cubePos);
    model = glm::rotate(model, glm::radians(cubeAngle), glm::vec3(0.f, 1.f, 0.f));
    glm::vec3 camPos(0.f, 0.f, 0.f);
    glm::vec3 targetPos(0.f, 0.f, -1.f);
    glm::vec3 up(0.f, 1.f, 0.f);
    view = glm::lookAt(camPos, targetPos, up);

    projection = glm::perspective(glm::radians(45.f), gWindowWidth /
    (float)gWindowHeight, 0.1f, 100.f);

    shaderProgram.use();

    shaderProgram.setUniform("model", model);
    shaderProgram.setUniform("view", view);
    shaderProgram.setUniform("projection", projection);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glfwSwapBuffers(gWindow);

    lastTime = currentTime;
  }

  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);

  glfwTerminate();

  return 0;
}
