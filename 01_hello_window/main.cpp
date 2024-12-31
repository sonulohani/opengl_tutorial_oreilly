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

  while (!glfwWindowShouldClose(gWindow)) {
    showFPS(gWindow);
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(gWindow);
  }

  glfwTerminate();

  return 0;
}
