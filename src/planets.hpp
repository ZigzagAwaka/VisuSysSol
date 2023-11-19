#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


struct PlanetParams {
    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture; // earth
    GLint uTexture2; // clouds
    GLint uKd;
    GLint uKs;
    GLint uShininess;
    GLint uLightDir_vs;
    GLint uLightIntensity;
};


struct EarthProgram {
    glimac::Program m_Program;
    PlanetParams p;

    EarthProgram(const glimac::FilePath& applicationPath):
        m_Program {loadProgram(applicationPath.dirPath() + "src/shaders/position3D.vs.glsl",
                                applicationPath.dirPath() + "src/shaders/directionallight_multiTex3D.fs.glsl")} {
        p.uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        p.uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        p.uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        p.uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
        p.uTexture2 = glGetUniformLocation(m_Program.getGLId(), "uTexture2");
        p.uKd = glGetUniformLocation(m_Program.getGLId(), "uKd");
        p.uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
        p.uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");
        p.uLightDir_vs = glGetUniformLocation(m_Program.getGLId(), "uLightDir_vs");
        p.uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
    };
};

struct MoonProgram {
    glimac::Program m_Program;
    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;
    GLint uKd;
    GLint uKs;
    GLint uShininess;
    GLint uLightDir_vs;
    GLint uLightIntensity;

    MoonProgram(const glimac::FilePath& applicationPath):
        m_Program {loadProgram(applicationPath.dirPath() + "src/shaders/position3D.vs.glsl",
                                applicationPath.dirPath() + "src/shaders/directionallight.fs.glsl")} {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
        uKd = glGetUniformLocation(m_Program.getGLId(), "uKd");
        uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
        uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");
        uLightDir_vs = glGetUniformLocation(m_Program.getGLId(), "uLightDir_vs");
        uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
    }
};