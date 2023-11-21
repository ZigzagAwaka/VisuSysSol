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


/** Global order for any functions returning multiple planets data :
 * sun, mercury, venus, earth, mars, jupiter, saturn, uranus, neptune, pluto,
 * moon, phobos, deimos, calisto, ganymede, europa, io, mimas, enceladus,
 * tethys, dione, rhea, titan, hyperion, iapetus, ariel, umbriel, titania,
 * oberon, miranda, triton, nereid, charon, earthcloud, saturnring, uranusring
*/


/* Parameters of planets */
struct PlanetParams {
    float perihelion;
    float aphelion;
    float diameter;
    float orbital_period;
    float length_of_days;
    float orbital_inclination;
};

/* Global structure to get every parameters of the planets */
struct PlanetInfo {
    private:
    std::vector<PlanetParams> p;

    public:
    PlanetInfo() {
        p = {
            PlanetParams{0.0, 0.0, 1391400.0, 0.0, 25.0, 0.0}, // sun
            PlanetParams{46.0, 69.8, 4879.0, 88.0, 4222.6, 7.0}, // mercury
            PlanetParams{107.5, 108.9, 12104.0, 224.7, -2802.0, 3.4}, // venus
            PlanetParams{147.1, 152.1, 12756.0, 365.2, 24.0, 0.0}, // earth
            PlanetParams{206.7, 249.3, 6792.0, 687.0, 24.7, 1.8}, // mars
            PlanetParams{740.6, 816.4, 142984.0, 4331.0, 9.9, 1.3}, // jupiter
            PlanetParams{1357.6, 1506.5, 120536.0, 10747.0, 10.7, 2.5}, // saturn
            PlanetParams{2732.7, 3001.4, 51118.0, 30589.0, -17.2, 0.8}, // uranus
            PlanetParams{4471.1, 4558.9, 49528.0, 59800.0, 16.1, 1.8}, // neptune
            PlanetParams{4436.8, 7375.9, 2376.0, 90560.0, 153.3, 17.2}, // pluto
            PlanetParams{0.3, 0.3, 3476.2, 27.3, 27.3, 5.1}, // moon
            PlanetParams{0.009, 0.009, 11.0, 0.3, 0.3, 1.0}, // phobos
            PlanetParams{0.02, 0.023, 6.0, 1.2, 1.2, 1.7}, // deimos
            PlanetParams{1.8, 1.8, 4820.6, 16.6, 16.6, 0.1}, // calisto
            PlanetParams{1.0, 1.0, 5262.4, 7.1, 7.1, 0.1}, // ganymede
            PlanetParams{0.6, 0.6, 3121.6, 3.5, 3.5, 0.4}, // europa
            PlanetParams{0.4, 0.4, 3643.0, 1.7, 1.7, 0.0}, // io
            PlanetParams{0.1, 0.1, 416.0, 0.9, 0.9, 1.5}, // mimas
            PlanetParams{0.2, 0.2, 514.0, 1.3, 1.3, 0.0}, // enceladus
            PlanetParams{0.2, 0.2, 1076.0, 1.8, 1.8, 1.8}, // tethys
            PlanetParams{0.3, 0.3, 1126.0, 2.7, 2.7, 0.0}, // dione
            PlanetParams{0.5, 0.5, 1530.0, 4.5, 4.5, 0.3}, // rhea
            PlanetParams{1.2, 1.2, 5150.0, 15.9, 15.9, 0.3}, // titan
            PlanetParams{1.5, 1.5, 360.0, 21.2, 21.2, 0.4}, // hyperion
            PlanetParams{3.5, 3.5, 1492.0, 79.3, 79.3, 14.7}, // iapetus
            PlanetParams{0.1, 0.1, 1162.2, 2.5, 2.5, 0.0}, // ariel
            PlanetParams{0.2, 0.2, 1169.4, 4.1, 4.1, 0.1}, // umbriel
            PlanetParams{0.4, 0.4, 1577.8, 8.7, 8.7, 0.0}, // titania
            PlanetParams{0.5, 0.5, 1522.8, 13.4, 13.4, 0.0}, // oberon
            PlanetParams{0.1, 0.1, 480.0, 1.4, 1.4, 4.3}, // miranda
            PlanetParams{0.3, 0.3, 2706.8, 5.8, 5.8, 157.3}, // triton
            PlanetParams{5.5, 5.5, 340.0, 360.1, 360.1, 7.2}, // nereid
            PlanetParams{0.01, 0.01, 1212.0, 6.3, 6.3, 0.0} // charon
        };
    }

    /*closest distance to the sun/planet*/
    float perihelion(int i) {
        return p[i].perihelion;
    }

    /*furthest distance to the sun/planet*/
    float aphelion(int i) {
        return p[i].aphelion;
    }

    /*average distance to the sun/planet*/
    float distance(int i) {
        return (perihelion(i) + aphelion(i)) / 2.0;
    }
    
    /*diameter of the planet*/
    float diameter(int i) {
        return p[i].diameter;
    }

    /*ratio size of the planet compared to earth*/
    float size(int i) {
        return diameter(i) / diameter(3);
    }
    
    /*number of days for an orbit around the sun/planet*/
    float orbital_period(int i) {
        return p[i].orbital_period;
    }
    
    /*time for the planet to have a proper orbit*/
    float length_of_days(int i) {
        return p[i].length_of_days;
    }
    
    /*inclination of the orbit*/
    float orbital_inclination(int i) {
        return p[i].orbital_inclination;
    }

    /*number of planets, or celestial body, in this structure*/
    int nbOfPlanets() {
        return p.size();
    }

    /*return true if the asked planet has multiple texture layers*/
    bool hasMultipleTex(int i) {
        return i == 3; // only the Earth, for now
    }
};



/* Uniform variables (in shaders) */
struct UniformVariables {
    GLint uMVPMatrix; // model view proj
    GLint uMVMatrix; // model view
    GLint uNormalMatrix; // norm
    GLint uTexture0;
    GLint uTexture1;
    GLint uKd; // material diffuse reflection
    GLint uKs; // material glossy reflection
    GLint uShininess; // material shine factor
    GLint uLightDir_vs; // light direction
    GLint uLightIntensity;
};

/* Program of a classic planet, or celestial body */
struct PlanetProgram {
    glimac::Program m_Program;
    UniformVariables u;

    PlanetProgram(const glimac::FilePath& applicationPath):
        m_Program {loadProgram(applicationPath.dirPath() + "src/shaders/position3D.vs.glsl",
                                applicationPath.dirPath() + "src/shaders/multiTex3D_light.fs.glsl")} {
        u.uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        u.uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        u.uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        u.uTexture0 = glGetUniformLocation(m_Program.getGLId(), "uTexture0");
        u.uTexture1 = glGetUniformLocation(m_Program.getGLId(), "uTexture1");
        u.uKd = glGetUniformLocation(m_Program.getGLId(), "uKd");
        u.uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
        u.uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");
        u.uLightDir_vs = glGetUniformLocation(m_Program.getGLId(), "uLightDir_vs");
        u.uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
    };
};

/* Program of the sun */
struct StarProgram {
    glimac::Program m_Program;
    UniformVariables u;

    StarProgram(const glimac::FilePath& applicationPath):
        m_Program {loadProgram(applicationPath.dirPath() + "src/shaders/position3D.vs.glsl",
                                applicationPath.dirPath() + "src/shaders/tex3D.fs.glsl")} {
        u.uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        u.uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        u.uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        u.uTexture0 = glGetUniformLocation(m_Program.getGLId(), "uTexture0");
        // u.uTexture1 = glGetUniformLocation(m_Program.getGLId(), "uTexture1");
        // u.uKd = glGetUniformLocation(m_Program.getGLId(), "uKd");
        // u.uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
        // u.uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");
        // u.uLightDir_vs = glGetUniformLocation(m_Program.getGLId(), "uLightDir_vs");
        // u.uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
    };
};



// will be removed
struct MoonProgram {
    glimac::Program m_Program;
    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture0;
    GLint uKd;
    GLint uKs;
    GLint uShininess;
    GLint uLightDir_vs;
    GLint uLightIntensity;

    MoonProgram(const glimac::FilePath& applicationPath):
        m_Program {loadProgram(applicationPath.dirPath() + "src/shaders/position3D.vs.glsl",
                                applicationPath.dirPath() + "src/shaders/tex3D_light.fs.glsl")} {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture0 = glGetUniformLocation(m_Program.getGLId(), "uTexture0");
        uKd = glGetUniformLocation(m_Program.getGLId(), "uKd");
        uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
        uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");
        uLightDir_vs = glGetUniformLocation(m_Program.getGLId(), "uLightDir_vs");
        uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
    }
};