#include "engine.hpp"


int window_width = 1000;
int window_height = 1000;
int CAMERA_TYPE = 0; // 0=trackball, 1=freefly

glimac::TrackballCamera trackballCamera;
glimac::FreeflyCamera freeflyCamera;

/* Main fonction of the engine */
void visusyssol(GLFWwindow* window, glimac::FilePath applicationPath);


// ============================================================
// CALLBACKS (user inputs)
// ============================================================

static void key_callback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/) {
    if(action == GLFW_PRESS) {
        float moveSpeed = 0.5;
        switch(key) {
            case GLFW_KEY_P: glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); break;
            case GLFW_KEY_L: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
            case GLFW_KEY_F: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
            case GLFW_KEY_W: if(CAMERA_TYPE == 1) freeflyCamera.moveFront(-1.0 * moveSpeed); break;
            case GLFW_KEY_A: if(CAMERA_TYPE == 1) freeflyCamera.moveLeft(moveSpeed); break;
            case GLFW_KEY_S: if(CAMERA_TYPE == 1) freeflyCamera.moveFront(moveSpeed); break;
            case GLFW_KEY_D: if(CAMERA_TYPE == 1) freeflyCamera.moveLeft(-1.0 * moveSpeed); break;
            case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, 1); break;
            default: break;
        }
    }
}

static void mouse_button_callback(GLFWwindow* /*window*/, int /*button*/, int /*action*/, int /*mods*/) {}

static void scroll_callback(GLFWwindow* /*window*/, double /*xoffset*/, double yoffset) {
    if(CAMERA_TYPE == 0) {
        float moveSpeed = 1.0;
        trackballCamera.moveFront(moveSpeed * yoffset);
    }
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        float rotationRadius = 2.0;
        if(CAMERA_TYPE == 0) {
            trackballCamera.rotateLeft(((xpos - (window_width/2) ) / (window_width/2)) * rotationRadius);
            trackballCamera.rotateUp((((window_height/2) - ypos) / (window_height/2)) * rotationRadius);
        }
        else {
            freeflyCamera.rotateLeft(((xpos - (window_width/2) ) / (window_width/2)) * rotationRadius);
            freeflyCamera.rotateUp((((window_height/2) - ypos) / (window_height/2)) * rotationRadius);
        }
    }
}

static void size_callback(GLFWwindow* /*window*/, int width, int height) {
    window_width  = width;
    window_height = height;
}


// ============================================================


int main(int argc, char** argv) {
    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    /* Create a window and its OpenGL context */
#ifdef __APPLE__
    /* We need to explicitly ask for a 3.3 context on Mac */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "VisuSysSol", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    /* Intialize glad (loads the OpenGL functions) */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    /* Hook input callbacks */
    glfwSetKeyCallback(window, &key_callback);
    glfwSetMouseButtonCallback(window, &mouse_button_callback);
    glfwSetScrollCallback(window, &scroll_callback);
    glfwSetCursorPosCallback(window, &cursor_position_callback);
    glfwSetWindowSizeCallback(window, &size_callback);

    std::srand(time(0));
    glEnable(GL_DEPTH_TEST);
    std::cout << "Launching... " << argc << " " << argv << std::endl;
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;

    /* Launch engine */
    glimac::FilePath applicationPath(argv[0]);
    visusyssol(window, applicationPath);
    
    glfwTerminate();
    return 0;
}


void visusyssol(GLFWwindow* window, glimac::FilePath applicationPath) {
    // EarthProgram earth(applicationPath);
    MoonProgram moon(applicationPath);
    auto textureObjects = createTextureObjects(applicationPath.dirPath());
    GLuint texoEarth = textureObjects[3], texoMoon = textureObjects[10], texoCloud = textureObjects[33];
    // const GLuint VERTEX_ATTR_POSITION = 0;
    // const GLuint VERTEX_ATTR_NORMAL = 1;
    // const GLuint VERTEX_ATTR_TEXTURE = 2;

    // GLuint vbo;
    // glGenBuffers(1, &vbo);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glimac::Sphere sphere(1, 64, 64);
    // glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount()*sizeof(glimac::ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    // GLuint vao;
    // glGenVertexArrays(1, &vao);
    // glBindVertexArray(vao);
    // glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    // glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    // glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, position));
    // glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, normal));
    // glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, texCoords));
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);

    GLuint vbo; GLuint vao;
    glimac::Sphere sphere = createSphere(&vbo, &vao, 1, 64, 64);

    int NB_MOONS = 30;
    float MOON_DISTANCE = 5.0;
    float ROTATION_SPEED = 0.8;
    std::vector<glm::vec3> moonTranslation; // original position of the moon compared to the planet
    std::vector<glm::vec3> rotationAxis; // rotation axis of the moon around the planet
    for(int i=0; i<NB_MOONS; i++) {
        moonTranslation.push_back(glm::sphericalRand(MOON_DISTANCE));
        float x = 1.0, z = 1.0, y = ((moonTranslation[i].x * x) + (moonTranslation[i].z * z)) / (-1.0*moonTranslation[i].y);
        rotationAxis.push_back(glm::vec3(x,y,z));
    }

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);

        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.0f), float(window_width/window_height), 0.1f, 100.0f);
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
        glm::mat4 globalMVMatrix;
        glm::mat4 viewMatrix;
        if(CAMERA_TYPE == 0) {
            viewMatrix = trackballCamera.getViewMatrix();
            globalMVMatrix = modelMatrix * viewMatrix;
        }
        else {
            viewMatrix = freeflyCamera.getViewMatrix();
            globalMVMatrix = viewMatrix * modelMatrix;
        }

        // EARTH
        drawObjects(applicationPath, texoEarth, texoCloud, ROTATION_SPEED, globalMVMatrix, viewMatrix, ProjMatrix, sphere);
        // earth.m_Program.use();
        // glUniform1i(earth.uTexture, 0);
        // glUniform1i(earth.uTexture2, 1);
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, texoEarth);
        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, texoCloud);
        // glUniform3fv(earth.uKd, 1, glm::value_ptr(glm::vec3(0.8, 0.7, 0.7)));
        // glUniform3fv(earth.uKs, 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.4)));
        // glUniform1f(earth.uShininess, 4.0f);
        // glUniform3fv(earth.uLightDir_vs, 1, glm::value_ptr(glm::mat3(glm::rotate( glm::mat4(1.0), float(glfwGetTime() * ROTATION_SPEED * 0.5), glm::vec3(0, 1, 0))) * glm::mat3(viewMatrix)));
        // glUniform3fv(earth.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.9, 0.9, 0.88)));
        // glm::mat4 earthMVMatrix = glm::rotate(globalMVMatrix, float(glfwGetTime() * ROTATION_SPEED), glm::vec3(0, 1, 0));
        // glUniformMatrix4fv(earth.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * earthMVMatrix));
        // glUniformMatrix4fv(earth.uMVMatrix, 1, GL_FALSE, glm::value_ptr(earthMVMatrix));
        // glUniformMatrix4fv(earth.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(earthMVMatrix))));
        // glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

        // MOONS
        moon.m_Program.use();
        glUniform1i(moon.uTexture, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texoMoon);
        glUniform3fv(moon.uKd, 1, glm::value_ptr(glm::vec3(0.8, 0.7, 0.7)));
        glUniform3fv(moon.uKs, 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.4)));
        glUniform1f(moon.uShininess, 4.0f);
        glUniform3fv(moon.uLightDir_vs, 1, glm::value_ptr(glm::mat3(glm::rotate(glm::mat4(1.0), float(glfwGetTime() * ROTATION_SPEED * 0.5), glm::vec3(0, 1, 0))) * glm::mat3(viewMatrix)));
        glUniform3fv(moon.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.9, 0.9, 0.88)));
        for(int n=0; n<NB_MOONS; n++) {
            glm::mat4 moonMVMatrix = glm::rotate(globalMVMatrix, float(glfwGetTime() * ROTATION_SPEED), rotationAxis[n]);
            moonMVMatrix = glm::translate(moonMVMatrix, moonTranslation[n]);
            moonMVMatrix = glm::rotate(moonMVMatrix, float(glfwGetTime() * ROTATION_SPEED * -1.0), rotationAxis[n]);
            moonMVMatrix = glm::scale(moonMVMatrix, glm::vec3(0.2, 0.2, 0.2));
            glUniformMatrix4fv(moon.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * moonMVMatrix));
            glUniformMatrix4fv(moon.uMVMatrix, 1, GL_FALSE, glm::value_ptr(moonMVMatrix));
            glUniformMatrix4fv(moon.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(moonMVMatrix))));
            glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
        }
        
        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);
        glfwSwapBuffers(window); // Update the display
        glfwPollEvents(); // Poll for and process events
    }

    glDeleteTextures(textureObjects.size(), textureObjects.data());
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}