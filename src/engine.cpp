#include "engine.hpp"


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
        "uranusring.jpg"};
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


glimac::Sphere createSphere(GLuint* vbo, GLuint* vao, int radius, int discLat, int discLong) {
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXTURE = 2;

    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glimac::Sphere sphere(radius, discLat, discLong);
    glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount()*sizeof(glimac::ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);
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

    return sphere;
}


// ============================================================
// DRAW FUNCTIONS
// ============================================================

void drawSun(StarProgram* star, PlanetInfo info, std::vector<GLuint> textures, std::vector<glm::mat4> matrix, glimac::Sphere sphere) {
    glUniform1i(star->u.uTexture0, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glm::mat4 sunMVMatrix = glm::rotate(matrix[1], float(glfwGetTime() * 1.0), glm::vec3(0, 1, 0));
    sunMVMatrix = glm::scale(sunMVMatrix, glm::vec3(10, 10, 10));
    glUniformMatrix4fv(star->u.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(matrix[0] * sunMVMatrix));
    glUniformMatrix4fv(star->u.uMVMatrix, 1, GL_FALSE, glm::value_ptr(sunMVMatrix));
    glUniformMatrix4fv(star->u.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(sunMVMatrix))));
    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
}


void drawPlanets(int i, PlanetProgram* planet, PlanetInfo info, std::vector<GLuint> textures, std::vector<glm::mat4> matrix, glimac::Sphere sphere) {
    glUniform1i(planet->u.uTexture0, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[i]);
    glUniform1i(planet->u.uTexture1, 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures[33]);
    glUniform3fv(planet->u.uKd, 1, glm::value_ptr(glm::vec3(0.8, 0.7, 0.7)));
    glUniform3fv(planet->u.uKs, 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.4)));
    glUniform1f(planet->u.uShininess, 4.0f);
    glUniform3fv(planet->u.uLightDir_vs, 1, glm::value_ptr(glm::mat3(glm::rotate( glm::mat4(1.0), float(glfwGetTime() * 1.0 * 0.5), glm::vec3(0, 1, 0))) * glm::mat3(matrix[2])));
    glUniform3fv(planet->u.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.9, 0.9, 0.88)));
    glm::mat4 planetMVMatrix = glm::rotate(matrix[1], float(glfwGetTime() * 1.0), glm::vec3(0, 1, 0));
    planetMVMatrix = glm::translate(planetMVMatrix, glm::vec3(15.0, 0, 0));
    glUniformMatrix4fv(planet->u.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(matrix[0] * planetMVMatrix));
    glUniformMatrix4fv(planet->u.uMVMatrix, 1, GL_FALSE, glm::value_ptr(planetMVMatrix));
    glUniformMatrix4fv(planet->u.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(planetMVMatrix))));
    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
}


void drawEverything(StarProgram* star, PlanetProgram* planet, PlanetInfo info, std::vector<GLuint> textures, std::vector<glm::mat4> matrix, glimac::Sphere sphere) {
    star->m_Program.use();
    drawSun(star, info, textures, matrix, sphere);
    planet->m_Program.use();
    //for(int i=1; i<info.nbOfPlanets(); i++) {}
    for(int i=3; i<4; i++) {
        drawPlanets(i, planet, info, textures, matrix, sphere);
    }
}




void drawObjects(PlanetProgram* earth, GLuint texoEarth, GLuint texoCloud, float r, glm::mat4 globalMVMatrix, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glimac::Sphere ss) {
    //PlanetProgram earth(applicationPath);
    earth->m_Program.use();
    glUniform1i(earth->u.uTexture0, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texoEarth);
    glUniform1i(earth->u.uTexture1, 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texoCloud);
    glUniform3fv(earth->u.uKd, 1, glm::value_ptr(glm::vec3(0.8, 0.7, 0.7)));
    glUniform3fv(earth->u.uKs, 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.4)));
    glUniform1f(earth->u.uShininess, 4.0f);
    glUniform3fv(earth->u.uLightDir_vs, 1, glm::value_ptr(glm::mat3(glm::rotate( glm::mat4(1.0), float(glfwGetTime() * r * 0.5), glm::vec3(0, 1, 0))) * glm::mat3(viewMatrix)));
    glUniform3fv(earth->u.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.9, 0.9, 0.88)));
    glm::mat4 earthMVMatrix = glm::rotate(globalMVMatrix, float(glfwGetTime() * r), glm::vec3(0, 1, 0));
    glUniformMatrix4fv(earth->u.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * earthMVMatrix));
    glUniformMatrix4fv(earth->u.uMVMatrix, 1, GL_FALSE, glm::value_ptr(earthMVMatrix));
    glUniformMatrix4fv(earth->u.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(earthMVMatrix))));
    glDrawArrays(GL_TRIANGLES, 0, ss.getVertexCount());
}
