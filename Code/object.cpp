#include "object.h"

#include <iostream>
#include "renderer.h"
#include "glm/gtx/transform.hpp"

#include <exception>




Object::Object(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::string texturePath):m_vb(0), m_uvsb(0), m_texture(0), position(0,0,0), rotationAngles(0,0,0)
{

     m_vb = new VertexBuffer(vertices);
     m_uvsb = new UVBuffer(uvs);

     m_texture = new Texture(texturePath);

}


Object::~Object()
{
    delete m_vb;
    if (m_uvsb) delete m_uvsb;
    if (m_texture) delete m_texture;
}

void Object::Bind() const
{
    m_vb->Bind(0);
    if (m_uvsb) m_uvsb->Bind(1);
    if (m_texture) m_texture->Bind(0);
}

void Object::Unbind() const
{
    m_vb->Unbind();
    if (m_uvsb) m_uvsb->Unbind();
    if (m_texture) m_texture->Unbind();
}



void Object::Draw() const
{
    GLCall(glDrawArrays(GL_TRIANGLES,0, m_vb->getSize()));
}

glm::mat4 Object::getModelMatrix()
{
    glm::mat4 m = glm::rotate(glm::translate(glm::mat4(1), position), rotationAngles.x, glm::vec3(1,0,0));
    m=glm::rotate(m, rotationAngles.y, glm::vec3(0,1,0));
    m=glm::rotate(m, rotationAngles.z, glm::vec3(0,0,1));
    return m;
}
