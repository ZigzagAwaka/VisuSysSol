#include "engine.hpp"


std::vector<GLuint> createTextureObjects(glimac::FilePath binPath) {
    std::vector<GLuint> textureObjects;
    std::vector<std::unique_ptr<glimac::Image>> textureImages;
    textureImages.push_back(glimac::loadImage(binPath + "assets/textures/earth.jpg"));
    if(textureImages[0] == NULL) printf("Texture loading 'earth.jpg' fail !");
    textureImages.push_back(glimac::loadImage(binPath + "assets/textures/moon.jpg"));
    if(textureImages[1] == NULL) printf("Texture loading 'moon.jpg' fail !");
    textureImages.push_back(glimac::loadImage(binPath + "assets/textures/earthcloud.jpg"));
    if(textureImages[2] == NULL) printf("Texture loading 'earthcloud.jpg' fail !");
    for(size_t i=0; i<textureImages.size(); i++) {
        GLuint texo;
        glGenTextures(1, &texo);
        glBindTexture(GL_TEXTURE_2D, texo);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImages[i].get()->getWidth(), textureImages[i].get()->getHeight(), 0, GL_RGBA, GL_FLOAT, textureImages[i].get()->getPixels());
        glBindTexture(GL_TEXTURE_2D, 0);
        textureObjects.push_back(texo);
    }
    return textureObjects;
}


void drawObjects(glimac::FilePath applicationPath, GLuint texoEarth, GLuint texoCloud, float r, glm::mat4 globalMVMatrix, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glimac::Sphere ss) {
    EarthProgram earth(applicationPath);
    earth.m_Program.use();
    glUniform1i(earth.p.uTexture, 0);
    glUniform1i(earth.p.uTexture2, 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texoEarth);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texoCloud);
    glUniform3fv(earth.p.uKd, 1, glm::value_ptr(glm::vec3(0.8, 0.7, 0.7)));
    glUniform3fv(earth.p.uKs, 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.4)));
    glUniform1f(earth.p.uShininess, 4.0f);
    glUniform3fv(earth.p.uLightDir_vs, 1, glm::value_ptr(glm::mat3(glm::rotate( glm::mat4(1.0), float(glfwGetTime() * r * 0.5), glm::vec3(0, 1, 0))) * glm::mat3(viewMatrix)));
    glUniform3fv(earth.p.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.9, 0.9, 0.88)));
    glm::mat4 earthMVMatrix = glm::rotate(globalMVMatrix, float(glfwGetTime() * r), glm::vec3(0, 1, 0));
    glUniformMatrix4fv(earth.p.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * earthMVMatrix));
    glUniformMatrix4fv(earth.p.uMVMatrix, 1, GL_FALSE, glm::value_ptr(earthMVMatrix));
    glUniformMatrix4fv(earth.p.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(earthMVMatrix))));
    glDrawArrays(GL_TRIANGLES, 0, ss.getVertexCount());
}
