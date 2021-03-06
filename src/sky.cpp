#include "sky.h"

Sky::Sky() {

    faces.push_back( "./textures/sky/right.tga");
    faces.push_back("./textures/sky/left.tga");
    faces.push_back("./textures/sky/up.tga");
    faces.push_back("./textures/sky/down.tga");
    faces.push_back("./textures/sky/front.tga");
    faces.push_back("./textures/sky/back.tga");

    textureID = 0;
    float skyboxSize = 50.0f;
    
    skyboxVertices = {
        // positions
        -skyboxSize,  skyboxSize, -skyboxSize,
        -skyboxSize, -skyboxSize, -skyboxSize,
        skyboxSize, -skyboxSize, -skyboxSize,
        skyboxSize, -skyboxSize, -skyboxSize,
        skyboxSize,  skyboxSize, -skyboxSize,
        -skyboxSize,  skyboxSize, -skyboxSize,
        
        -skyboxSize, -skyboxSize,  skyboxSize,
        -skyboxSize, -skyboxSize, -skyboxSize,
        -skyboxSize,  skyboxSize, -skyboxSize,
        -skyboxSize,  skyboxSize, -skyboxSize,
        -skyboxSize,  skyboxSize,  skyboxSize,
        -skyboxSize, -skyboxSize,  skyboxSize,
        
        skyboxSize, -skyboxSize, -skyboxSize,
        skyboxSize, -skyboxSize,  skyboxSize,
        skyboxSize,  skyboxSize,  skyboxSize,
        skyboxSize,  skyboxSize,  skyboxSize,
        skyboxSize,  skyboxSize, -skyboxSize,
        skyboxSize, -skyboxSize, -skyboxSize,
        
        -skyboxSize, -skyboxSize,  skyboxSize,
        -skyboxSize,  skyboxSize,  skyboxSize,
        skyboxSize,  skyboxSize,  skyboxSize,
        skyboxSize,  skyboxSize,  skyboxSize,
        skyboxSize, -skyboxSize,  skyboxSize,
        -skyboxSize, -skyboxSize,  skyboxSize,
        
        -skyboxSize,  skyboxSize, -skyboxSize,
        skyboxSize,  skyboxSize, -skyboxSize,
        skyboxSize,  skyboxSize,  skyboxSize,
        skyboxSize,  skyboxSize,  skyboxSize,
        -skyboxSize,  skyboxSize,  skyboxSize,
        -skyboxSize,  skyboxSize, -skyboxSize,
        
        -skyboxSize, -skyboxSize, -skyboxSize,
        -skyboxSize, -skyboxSize,  skyboxSize,
        skyboxSize, -skyboxSize, -skyboxSize,
        skyboxSize, -skyboxSize, -skyboxSize,
        -skyboxSize, -skyboxSize,  skyboxSize,
        skyboxSize, -skyboxSize,  skyboxSize
    };
    
}

Sky::Sky(float skyboxSize) {
    faces.push_back( "./textures/sky/right.tga");
    faces.push_back("./textures/sky/left.tga");
    faces.push_back("./textures/sky/up.tga");
    faces.push_back("./textures/sky/down.tga");
    faces.push_back("./textures/sky/front.tga");
    faces.push_back("./textures/sky/back.tga");

    textureID = 0;
    
    skyboxVertices = {
        // positions
        -skyboxSize,  skyboxSize, -skyboxSize,
        -skyboxSize, -skyboxSize, -skyboxSize,
        skyboxSize, -skyboxSize, -skyboxSize,
        skyboxSize, -skyboxSize, -skyboxSize,
        skyboxSize,  skyboxSize, -skyboxSize,
        -skyboxSize,  skyboxSize, -skyboxSize,
        
        -skyboxSize, -skyboxSize,  skyboxSize,
        -skyboxSize, -skyboxSize, -skyboxSize,
        -skyboxSize,  skyboxSize, -skyboxSize,
        -skyboxSize,  skyboxSize, -skyboxSize,
        -skyboxSize,  skyboxSize,  skyboxSize,
        -skyboxSize, -skyboxSize,  skyboxSize,
        
        skyboxSize, -skyboxSize, -skyboxSize,
        skyboxSize, -skyboxSize,  skyboxSize,
        skyboxSize,  skyboxSize,  skyboxSize,
        skyboxSize,  skyboxSize,  skyboxSize,
        skyboxSize,  skyboxSize, -skyboxSize,
        skyboxSize, -skyboxSize, -skyboxSize,
        
        -skyboxSize, -skyboxSize,  skyboxSize,
        -skyboxSize,  skyboxSize,  skyboxSize,
        skyboxSize,  skyboxSize,  skyboxSize,
        skyboxSize,  skyboxSize,  skyboxSize,
        skyboxSize, -skyboxSize,  skyboxSize,
        -skyboxSize, -skyboxSize,  skyboxSize,
        
        -skyboxSize,  skyboxSize, -skyboxSize,
        skyboxSize,  skyboxSize, -skyboxSize,
        skyboxSize,  skyboxSize,  skyboxSize,
        skyboxSize,  skyboxSize,  skyboxSize,
        -skyboxSize,  skyboxSize,  skyboxSize,
        -skyboxSize,  skyboxSize, -skyboxSize,
        
        -skyboxSize, -skyboxSize, -skyboxSize,
        -skyboxSize, -skyboxSize,  skyboxSize,
        skyboxSize, -skyboxSize, -skyboxSize,
        skyboxSize, -skyboxSize, -skyboxSize,
        -skyboxSize, -skyboxSize,  skyboxSize,
        skyboxSize, -skyboxSize,  skyboxSize
    };
}

void Sky::buildSky(){
    // skybox VAO, VBO
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(getVertices()) * 108, getVertices(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void Sky::renderSky(){
    // skybox cube
    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS); // set depth function back to default
}

GLuint Sky::getTexID(){
    return textureID;
}

GLfloat* Sky::getVertices(){
    return skyboxVertices.data();
}

bool Sky::loadCubemap() {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    
    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                         );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
            return false;
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    return true;
}

Sky::~Sky() {
    glDeleteTextures(1, &textureID);
    textureID = 0;
}
