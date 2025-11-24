#include "cube.h"
#include <iostream>
#include "renderer.h"
#include "glm/gtx/transform.hpp"

#include <exception>



Cube::Cube(glm::vec3 _coord, glm::vec3 color):m_vb(0), m_uvsb(0), rotationAngles(0,0,0)
{
    m_color = color;
    position = _coord;
    vertices = createVertice();
    m_vb = new VertexBuffer(vertices);



}


Cube::~Cube()
{
    delete m_vb;
    if (m_uvsb) delete m_uvsb;
}


void Cube::Bind() const
{
    m_vb->Bind(0);
}

void Cube::Unbind() const
{
    m_vb->Unbind();
}



void Cube::Draw() const
{
    GLCall(glDrawArrays(GL_TRIANGLES,0, m_vb->getSize()));
}

std::vector<glm::vec3> Cube::createVertice(){
    std::vector<glm::vec3> verts;

    float s = 0.5f;

    // Coins du cube
    glm::vec3 p0 = glm::vec3(-s,-s,-s);
    glm::vec3 p1 = glm::vec3( s,-s,-s);
    glm::vec3 p2 = glm::vec3( s, s,-s);
    glm::vec3 p3 = glm::vec3(-s, s,-s);
    glm::vec3 p4 = glm::vec3(-s,-s, s);
    glm::vec3 p5 = glm::vec3( s,-s, s);
    glm::vec3 p6 = glm::vec3( s, s, s);
    glm::vec3 p7 = glm::vec3(-s, s, s);

    // Face arrière (-Z)
    verts.push_back(p0); verts.push_back(p1); verts.push_back(p2);
    verts.push_back(p0); verts.push_back(p2); verts.push_back(p3);

    // Face avant (+Z)
    verts.push_back(p4); verts.push_back(p6); verts.push_back(p5);
    verts.push_back(p4); verts.push_back(p7); verts.push_back(p6);

    // Face gauche (-X)
    verts.push_back(p0); verts.push_back(p3); verts.push_back(p7);
    verts.push_back(p0); verts.push_back(p7); verts.push_back(p4);

    // Face droite (+X)
    verts.push_back(p1); verts.push_back(p5); verts.push_back(p6);
    verts.push_back(p1); verts.push_back(p6); verts.push_back(p2);

    // Face bas (-Y)
    verts.push_back(p0); verts.push_back(p4); verts.push_back(p5);
    verts.push_back(p0); verts.push_back(p5); verts.push_back(p1);

    // Face haut (+Y)
    verts.push_back(p3); verts.push_back(p2); verts.push_back(p6);
    verts.push_back(p3); verts.push_back(p6); verts.push_back(p7);

    return verts;
}


glm::mat4 Cube::getModelMatrix()
{
    glm::mat4 m = glm::rotate(glm::translate(glm::mat4(1), position), rotationAngles.x, glm::vec3(1,0,0));
    m=glm::rotate(m, rotationAngles.y, glm::vec3(0,1,0));
    m=glm::rotate(m, rotationAngles.z, glm::vec3(0,0,1));
    return m;
}


glm::vec3 Cube::getColor() const {
    return m_color;
}
