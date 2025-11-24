#ifndef OBJECT_H
#define OBJECT_H

#include <string>

#include <glm/glm.hpp>

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "texture.h"
#include "uvbuffer.h"

class Object
{
public:
    Object(std::vector< glm::vec3 > vertices, std::vector< glm::vec2 > uvs, std::string texturePath);
    ~Object();
    void Bind() const;
    void Unbind() const;
    void Draw() const;
    glm::vec3 position;
    glm::vec3 rotationAngles;
    glm::mat4 getModelMatrix();

private:
    VertexBuffer *m_vb;
    UVBuffer *m_uvsb;
    Texture *m_texture;


};

#endif // OBJECT_H
