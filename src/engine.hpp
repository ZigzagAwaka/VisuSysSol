#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/geometric.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "camera.hpp"
#include "planets.hpp"


/** Load every textures. The returned vector contains all textures is the global
 * order (see planets.hpp for the order) */
std::vector<GLuint> createTextureObjects(glimac::FilePath binPath);

/** Load and return a sphere vertex object
 * Fill the vbo and vao pointers parameters */
glimac::Sphere createSphere(GLuint* vbo, GLuint* vao, int radius, int discLat, int discLong);

/** Draw every objects of the solar system (function for the MAIN LOOP)
 * @param star program structure of the sun
 * @param planet program structure of planets
 * @param info PlanetInfo structure containing every planet data
 * @param textures vector containing every pre-loaded textures
 * @param matrix vector containing the ProjMatrix, globalMVMatrix and viewMatrix
 * @param sphere a full constructed glimac::Sphere
*/
void drawEverything(StarProgram* star, PlanetProgram* planet, PlanetInfo info, std::vector<GLuint> textures, std::vector<glm::mat4> matrix, glimac::Sphere sphere);

// test
// void drawObjects(PlanetProgram* earth, GLuint texoEarth, GLuint texoCloud, float r, glm::mat4 globalMVMatrix, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glimac::Sphere ss);

