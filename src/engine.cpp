#include "engine.hpp"


// ============================================================
// TEXTURES
// ============================================================

std::vector<GLuint> createTextureObjects(glimac::FilePath binPath) {
    std::vector<GLuint> textureObjects;
    std::string dir = "assets/textures/";
    std::vector<std::string> textureImages = {
        "sun.jpg", "mercury.jpg", "venus.jpg", "earth.jpg", "mars.jpg", "jupiter.jpg",
        "saturn.jpg", "uranus.jpg", "neptune.jpg", "pluto.jpg", "moon.jpg", "phobos.jpg",
        "deimos.jpg", "calisto.jpg", "ganymede.jpg", "europa.jpg", "io.jpg", "mimas.jpg",
        "enceladus.jpg", "tethys.jpg", "dione.jpg", "rhea.jpg", "titan.jpg", "hyperion.jpg",
        "iapetus.jpg", "ariel.jpg", "umbriel.jpg", "titania.jpg", "oberon.jpg", "miranda.jpg",
        "triton.jpg", "nereid.jpg", "charon.jpg", "earthcloud.jpg", "saturnring.jpg",
        "uranusring.jpg", "skybox.jpg", "white.jpg"};
    for(size_t i=0; i<textureImages.size(); i++) {
        auto image = glimac::loadImage(binPath + dir + textureImages[i]);
        if(image == NULL) {
            std::cerr << "Texture loading " << textureImages[i] << " fail !" << std::endl;
            continue; }
        GLuint texo;
        glGenTextures(1, &texo);
        glBindTexture(GL_TEXTURE_2D, texo);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.get()->getWidth(), image.get()->getHeight(), 0, GL_RGBA, GL_FLOAT, image.get()->getPixels());
        glBindTexture(GL_TEXTURE_2D, 0);
        textureObjects.push_back(texo);
    }
    return textureObjects;
}


// ============================================================
// 3D OBJECTS
// ============================================================

/* load vbo and vao of an object */
void loadModel(GLsizei vertexCount, const glimac::ShapeVertex* dataPointer, GLuint* vbo, GLuint* vao) {
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXTURE = 2;

    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexCount*sizeof(glimac::ShapeVertex), dataPointer, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


std::vector<Model> createModels() {
    std::vector<Model> models;

    glimac::Sphere sphere(1, 64, 64);
    GLuint vbo0; GLuint vao0;
    loadModel(sphere.getVertexCount(), sphere.getDataPointer(), &vbo0, &vao0);
    Model model0 = Model(vbo0, vao0, sphere.getVertexCount());
    models.push_back(model0);

    glimac::Circle circle(1, 60, 0);
    GLuint vbo1; GLuint vao1;
    loadModel(circle.getVertexCount(), circle.getDataPointer(), &vbo1, &vao1);
    Model model1 = Model(vbo1, vao1, circle.getVertexCount());
    models.push_back(model1);

    return models;
}


GLuint* getDataOfModels(std::vector<Model> models, int type) {
    std::vector<GLuint> temp;
    for(size_t i=0; i<models.size(); i++) {
        GLuint t;
        if(type == 0) t = models[i].vbo;
        else t = models[i].vao;
        temp.push_back(t);
    }
    return temp.data();
}


// ============================================================
// OPENGL DRAW FUNCTIONS
// ============================================================

// Fill the given uniform variables (without light if lightDir < 0)
void fillUniforms(UniformVariables u, glm::mat4 objectMVMatrix, std::vector<glm::mat4> matrix, float lightDir) {
    if(lightDir > 0) {
        glUniform3fv(u.uKd, 1, glm::value_ptr(glm::vec3(0.8, 0.7, 0.7)));
        glUniform3fv(u.uKs, 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.4)));
        glUniform1f(u.uShininess, 3.0f);
        glUniform3fv(u.uLightDir_vs, 1, glm::value_ptr(
            glm::mat3(glm::rotate( glm::rotate(glm::mat4(1.0), glm::radians(180.0f), glm::vec3(0,1,0)), lightDir, glm::vec3(0,1,0) ))
            * glm::mat3(matrix[2]) ));
        glUniform3fv(u.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.9, 0.9, 0.88)));
    }
    glUniformMatrix4fv(u.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(matrix[0] * objectMVMatrix));
    glUniformMatrix4fv(u.uMVMatrix, 1, GL_FALSE, glm::value_ptr(objectMVMatrix));
    glUniformMatrix4fv(u.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(objectMVMatrix))));
}

// Activate and bind asked textures (one, or many)
void prepareTextures(int i, UniformVariables u, std::vector<GLuint> textures, bool multiple) {
    glUniform1i(u.uTexture0, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[i]);
    if(multiple) {
        glUniform1i(u.uTexture1, 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[33]); // only earthclouds, for now
    }
}

// Deactivate and debind multiple layers asked textures
void cleanMultTextures(bool multiple) {
    if(multiple) {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}


void drawSkybox(ClassicProgram* skybox, std::vector<GLuint> textures, std::vector<Model> models, std::vector<glm::mat4> matrix) {
    float s = 25000.0f;
    glm::mat4 sbMVMatrix = glm::scale(matrix[1], glm::vec3(s, s, s));
    prepareTextures(36, skybox->u, textures, false);
    fillUniforms(skybox->u, sbMVMatrix, matrix, 0);
    glDrawArrays(GL_TRIANGLES, 0, models[0].vertexCount);
}


void drawOrbit(int i, ClassicProgram* orbit, PlanetInfo info, std::vector<GLuint> textures, std::vector<Model> models, std::vector<glm::mat4> matrix) {
    float d = info.distance(i);
    float orb_inc = info.orbital_inclination(i);
    glm::mat4 orbMVMatrix = glm::rotate(matrix[1], glm::radians(orb_inc), glm::vec3(1, 0, 0));
    orbMVMatrix = glm::scale(orbMVMatrix, glm::vec3(d, d, d));
    prepareTextures(37, orbit->u, textures, false);
    fillUniforms(orbit->u, orbMVMatrix, matrix, 0);
    glDrawArrays(GL_TRIANGLES, 0, models[1].vertexCount);
}


void drawSun(StarProgram* star, PlanetInfo info, std::vector<GLuint> textures, std::vector<Model> models, std::vector<glm::mat4> matrix) {
    float s = info.size(0);
    float rot_speed = info.rotation_speed(0);
    double time = info.getTime();
    glm::mat4 sunMVMatrix = glm::rotate(matrix[1], float(time * rot_speed), glm::vec3(0, 1, 0));
    sunMVMatrix = glm::scale(sunMVMatrix, glm::vec3(s, s, s));
    prepareTextures(0, star->u, textures, false);
    fillUniforms(star->u, sunMVMatrix, matrix, 0);
    glDrawArrays(GL_TRIANGLES, 0, models[0].vertexCount);
}


void drawPlanets(int i, PlanetProgram* planet, PlanetInfo info, std::vector<GLuint> textures, std::vector<Model> models, std::vector<glm::mat4> matrix) {
    float d = info.distance(i);
    float s = info.size(i);
    float orb_speed = info.orbital_speed(i);
    float rot_speed = info.rotation_speed(i);
    glm::vec3 axis = info.inclination(i);
    double time = info.getTime();
    bool mult = info.hasMultipleTex(i);
    glm::mat4 planetMVMatrix = glm::rotate(matrix[1], float(time * orb_speed), axis);
    planetMVMatrix = glm::translate(planetMVMatrix, glm::vec3(d, 0, 0));
    // planetMVMatrix = glm::rotate(planetMVMatrix, float(time * -1.0 * orb_speed), axis);
    planetMVMatrix = glm::rotate(planetMVMatrix, float(time * rot_speed), axis);
    planetMVMatrix = glm::scale(planetMVMatrix, glm::vec3(s, s, s));
    prepareTextures(i, planet->u, textures, mult);
    fillUniforms(planet->u, planetMVMatrix, matrix, time * orb_speed);
    glDrawArrays(GL_TRIANGLES, 0, models[0].vertexCount);
    cleanMultTextures(mult);
}


void drawEverything(StarProgram* star, PlanetProgram* planet, ClassicProgram* classicObj, PlanetInfo info, std::vector<GLuint> textures, std::vector<Model> models, std::vector<glm::mat4> matrix) {
    classicObj->m_Program.use();
    if(info.drawOrbit()) {
        glBindVertexArray(models[1].vao); // bind circle
        for(int i=1; i<10; i++) {
            drawOrbit(i, classicObj, info, textures, models, matrix);
        }
        glBindVertexArray(0);
    }
    glBindVertexArray(models[0].vao); // bind sphere
    drawSkybox(classicObj, textures, models, matrix);
    star->m_Program.use();
    drawSun(star, info, textures, models, matrix);
    planet->m_Program.use();
    //for(int i=1; i<info.nbOfPlanets(); i++) {}
    for(int i=1; i<10; i++) {
        drawPlanets(i, planet, info, textures, models, matrix);
    }
    glBindVertexArray(0);
}
