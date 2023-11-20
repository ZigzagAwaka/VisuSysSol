#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/geometric.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "planets.hpp"


std::vector<GLuint> createTextureObjects(glimac::FilePath binPath);
glimac::Sphere createSphere(GLuint* vbo, GLuint* vao, int radius, int discLat, int discLong);

void drawObjects(glimac::FilePath applicationPath, GLuint texoEarth, GLuint texoCloud, float r, glm::mat4 globalMVMatrix, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glimac::Sphere ss);

