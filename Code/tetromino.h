#ifndef TETROMINO_H
#define TETROMINO_H
#include <string>
#include <vector>
#include <array>
#include <glm/glm.hpp>
#include "cube.h"
#include "vertexarray.h"
#include "shader.h"
#include "renderer.h"

class Tetromino
{
public:
    Tetromino(std::string);
    ~Tetromino();

    void moveLeft(const std::vector<std::vector<bool>>& gameMatrix);
    void moveRight(const std::vector<std::vector<bool>>& gameMatrix);
    std::vector<std::vector<bool>> moveDown(std::vector<std::vector<bool>>);
    void rotate(const std::vector<std::vector<bool>>& gameMatrix);
    void lineSuppressed(std::vector<std::vector<bool>>, int);
    void Draw(VertexArray, Shader, glm::mat4, glm::mat4, Renderer);
    std::vector<glm::ivec2> getPositions() const;
    void setCoords();
    std::vector<Cube*> m_tetrominos;
    bool isMoving;
    std::vector<std::array<std::array<bool,4>,4>> possibleComposition;
    void lineSuppressed(int gameLineY);
    glm::vec2 position;

protected :
    std::array<std::array<bool, 4>, 4> currentComposition;
    unsigned int compositionIndex;


};

#endif // TETROMINO_H
