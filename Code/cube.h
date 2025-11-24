#ifndef CUBE_H
#define CUBE_H

#include <string>

#include <glm/glm.hpp>

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "texture.h"
#include "uvbuffer.h"


class Cube {
public:
    Cube(glm::vec3 _coord, glm::vec3 color);
    ~Cube();
    void Bind() const;
    void Unbind() const;
    void Draw() const;
    glm::vec3 position;
    glm::vec3 rotationAngles;
    glm::mat4 getModelMatrix();
    std::vector<glm::vec3> vertices;
    glm::vec3 getColor() const;



private:
    VertexBuffer *m_vb;
    UVBuffer *m_uvsb;
    glm::vec3 m_color;
    std::vector<glm::vec3> createVertice();
};

#endif // CUBE_H
