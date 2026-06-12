#define GLFW_INCLUDE_NONE
#include "../include/GLFW/glfw3.h"
#include "../include/glad/glad.h"
#include <stdio.h>

struct Screen {
  int width;
  int height;
  char title[16];
};

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
  (void)window;
}

int main(void) {
  struct Screen viewport = {
      .width = 500,
      .height = 300,
      .title = "Ooniverse",
  };

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for MacOS

  GLFWwindow *window = glfwCreateWindow(viewport.width, viewport.height,
                                        viewport.title, NULL, NULL);
  if (window == NULL) {
    printf("Failed to create GLFW window");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD");
    return -1;
  }

  glViewport(0, 0, viewport.width, viewport.height);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glfwPollEvents(); // checks for events (e.g. keyboard or mouse inputs)
  }

  glfwTerminate();
  return 0;
}
