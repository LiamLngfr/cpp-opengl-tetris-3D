#include "tetromino.h"
#include <stdio.h>

// ---------- TETROMINO I ----------
static const std::vector<std::array<std::array<bool,4>,4>> possibleCompositions_I = {
    {{
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    }},
    {{
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0}
    }}
};

// ---------- TETROMINO O ----------
static const std::vector<std::array<std::array<bool,4>,4>> possibleCompositions_O = {
    {{
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    }}
};

// ---------- TETROMINO T ----------
static const std::vector<std::array<std::array<bool,4>,4>> possibleCompositions_T = {
    {{
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    }},
    {{
        {0,1,0,0},
        {0,1,1,0},
        {0,1,0,0},
        {0,0,0,0}
    }},
    {{
        {0,0,0,0},
        {1,1,1,0},
        {0,1,0,0},
        {0,0,0,0}
    }},
    {{
        {0,1,0,0},
        {1,1,0,0},
        {0,1,0,0},
        {0,0,0,0}
    }}
};

// ---------- TETROMINO L ----------
static const std::vector<std::array<std::array<bool,4>,4>> possibleCompositions_L = {
    {{
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    }},
    {{
        {0,1,0,0},
        {0,1,0,0},
        {0,1,1,0},
        {0,0,0,0}
    }},
    {{
        {0,0,0,0},
        {1,1,1,0},
        {1,0,0,0},
        {0,0,0,0}
    }},
    {{
        {1,1,0,0},
        {0,1,0,0},
        {0,1,0,0},
        {0,0,0,0}
    }}
};

// ---------- TETROMINO J ----------
static const std::vector<std::array<std::array<bool,4>,4>> possibleCompositions_J = {
    {{
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    }},
    {{
        {0,1,1,0},
        {0,1,0,0},
        {0,1,0,0},
        {0,0,0,0}
    }},
    {{
        {0,0,0,0},
        {1,1,1,0},
        {0,0,1,0},
        {0,0,0,0}
    }},
    {{
        {0,1,0,0},
        {0,1,0,0},
        {1,1,0,0},
        {0,0,0,0}
    }}
};

// ---------- TETROMINO S ----------
static const std::vector<std::array<std::array<bool,4>,4>> possibleCompositions_S = {
    {{
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    }},
    {{
        {0,1,0,0},
        {0,1,1,0},
        {0,0,1,0},
        {0,0,0,0}
    }}
};

// ---------- TETROMINO Z ----------
static const std::vector<std::array<std::array<bool,4>,4>> possibleCompositions_Z = {
    {{
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    }},
    {{
        {0,0,1,0},
        {0,1,1,0},
        {0,1,0,0},
        {0,0,0,0}
    }}
};




Tetromino::Tetromino(std::string forme): position(3,13), compositionIndex(0), isMoving(true)
{
    glm::vec3 color;
    if (forme == "I") {
        possibleComposition = possibleCompositions_I;
        color = glm::vec3(0.6f,0.6f,1.0f);
    }
    else if (forme == "O") {
        possibleComposition = possibleCompositions_O;
        color = glm::vec3(1.0f,1.0f,0.4f);
    }
    else if (forme == "T") {
        possibleComposition = possibleCompositions_T;
        color = glm::vec3(0.8f,0.4f,1.0f);
    }
    else if (forme == "L") {
        possibleComposition = possibleCompositions_L;
        color = glm::vec3(1.0f,0.6f,0.3f);
    }
    else if (forme == "J") {
        possibleComposition = possibleCompositions_J;
        color = glm::vec3(0.3f,0.6f,1.0f);
    }
    else if (forme == "S") {
        possibleComposition = possibleCompositions_S;
        color = glm::vec3(0.4f,1.0f,0.4f);
    }
    else if (forme == "Z") {
        possibleComposition = possibleCompositions_Z;
        color = glm::vec3(1.0f,0.3f,0.3f);
    }





    currentComposition = possibleComposition[compositionIndex];
    auto localPositions = getPositions();
    //m_tetrominos.reserve(localPositions.size());  // réserve la capacité
    for (auto & lp : localPositions) {
        Cube* c = new Cube(
            glm::vec3(position.x + lp.x, position.y + lp.y, 0.0f),
            color
            );
        m_tetrominos.push_back(c);
    }
    setCoords();
}



Tetromino::~Tetromino() {
    }



void Tetromino::Draw (VertexArray va, Shader shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, Renderer renderer){
    for (auto& cube : m_tetrominos){
        glm::mat4 m = cube->getModelMatrix ();
        glm::mat4 mvp = projectionMatrix * viewMatrix * m;
        shader.setUniformMat4f ("MVP", mvp);
        shader.setUniform3fv ("cubeColor", cube->getColor());
        renderer.Draw(va, *cube, shader);
    }

}


void Tetromino::setCoords() {
    auto localPositions = getPositions();
    for (size_t i = 0; i < localPositions.size(); i++) {
        int localX = localPositions[i].x;
        int localY = localPositions[i].y;
        Cube* cube = m_tetrominos[i];
        float z = cube->position.z;
        cube->position = glm::vec3(position.x + localX, position.y + localY, z);
    }
}


std::vector<glm::ivec2> Tetromino::getPositions() const{
    std::vector<glm::ivec2> positions;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (currentComposition[y][x]) {
                positions.emplace_back(x, y);
            }
        }
    }
    return positions;
}





std::vector<std::vector<bool>> Tetromino::moveDown(std::vector<std::vector<bool>> gameMatrix) {
    auto localPositions = getPositions();  // positions relatives des cubes
    glm::vec2 newPos = position + glm::vec2(0, -1);

    // Vérifie chaque cube
    for (auto & lp : localPositions) {
        int globalX = static_cast<int>(newPos.x) + lp.x;
        int globalY = static_cast<int>(newPos.y) + lp.y;

        // Si en dessous (nouvelle Y) est hors matrice ou déjà occupé → stop
        if (globalY < 0 ) {
            isMoving = false;
            break;
        }
        if (gameMatrix[globalY][globalX]) {
            isMoving = false;
            break;
        }
    }

    if (isMoving) {
        // Tous les cubes peuvent descendre
        position = newPos;
    } else {
        // On ne peut pas descendre → on “verrouille” ce tetromino dans la matrice
        for (auto & lp : localPositions) {
            int globalX = static_cast<int>(position.x) + lp.x;
            int globalY = static_cast<int>(position.y) + lp.y;
            if (globalY >= 0 && globalY < (int)gameMatrix.size() &&
                globalX >= 0 && globalX < (int)gameMatrix[0].size()) {
                gameMatrix[globalY][globalX] = true;
            }
        }
    }

    setCoords ();
    return gameMatrix;
}



void Tetromino::moveLeft(const std::vector<std::vector<bool>>& gameMatrix) {
    auto localPositions = getPositions();
    glm::vec2 newPos = position + glm::vec2(-1, 0);

    for (auto & lp : localPositions) {
        int globalX = static_cast<int>(newPos.x) + lp.x;
        int globalY = static_cast<int>(newPos.y) + lp.y;

        // Vérifie les bornes horizontales
        if (globalX < 0) {
            return;
        }
        // Collision avec la matrice
        if (gameMatrix[globalY][globalX]) {
            return;
        }
    }

    // Déplacement possible
    position = newPos;
    setCoords();
    return;
}

void Tetromino::moveRight(const std::vector<std::vector<bool>>& gameMatrix) {
    auto localPositions = getPositions();
    glm::vec2 newPos = position + glm::vec2(1, 0);

    for (auto & lp : localPositions) {
        int globalX = static_cast<int>(newPos.x) + lp.x;
        int globalY = static_cast<int>(newPos.y) + lp.y;

        // Vérifie les bornes horizontales
        if (globalX >= static_cast<int>(gameMatrix[0].size())) {
            return;
        }
        // Collision avec la matrice
        if (gameMatrix[globalY][globalX]) {
            return;
        }
    }

    // Déplacement possible
    position = newPos;
    setCoords();
}

void Tetromino::rotate(const std::vector<std::vector<bool>>& gameMatrix) {
    // Sauvegarde l’ancienne composition
    int oldIndex = compositionIndex;
    auto oldComposition = currentComposition;

    // Passe à la prochaine rotation
    compositionIndex = (compositionIndex + 1) % possibleComposition.size();
    currentComposition = possibleComposition[compositionIndex];

    // Vérifie si la nouvelle rotation est valide
    auto newPositions = getPositions();
    for (auto & lp : newPositions) {
        int globalX = static_cast<int>(position.x) + lp.x;
        int globalY = static_cast<int>(position.y) + lp.y;

        // Hors limites → rotation annulée
        if (globalX < 0 || globalX >= (int)gameMatrix[0].size()) {
            compositionIndex = oldIndex;
            currentComposition = oldComposition;
            return;
        }
        if (globalY < 0 || globalY >= (int)gameMatrix.size()) {
            compositionIndex = oldIndex;
            currentComposition = oldComposition;
            return;
        }

        // Collision → rotation annulée
        if (gameMatrix[globalY][globalX]) {
            compositionIndex = oldIndex;
            currentComposition = oldComposition;
            return;
        }
    }

    // Mise à jour des coordonnées réelles
    setCoords();
}



void Tetromino::lineSuppressed(int gameLineY) {
    // Si la ligne est en dessous du tetromino entier
    if (gameLineY < position.y) {
        position.y -= 1.0f;
        setCoords();
        return;
    }

    // Sinon on applique l'algorithme habituel
    auto localPositions = getPositions();
    std::vector<Cube*> newCubes;

    for (size_t i = 0; i < localPositions.size(); i++) {
        glm::ivec2 lp = localPositions[i];
        int globalY = static_cast<int>(position.y) + lp.y;
        if (globalY == gameLineY) {
            delete m_tetrominos[i];
        } else if (globalY > gameLineY) {
            newCubes.push_back(m_tetrominos[i]);
        } else {
            m_tetrominos[i]->position.y -= 1.0f;
            newCubes.push_back(m_tetrominos[i]);
        }
    }

    m_tetrominos = std::move(newCubes);

    // Mettre à jour currentComposition
    int deltaY = gameLineY - static_cast<int>(position.y);
    if (deltaY >= 0 && deltaY < 4) {
        for (int y = deltaY; y < 3; y++) {
            for (int x = 0; x < 4; x++) {
                currentComposition[y][x] = currentComposition[y + 1][x];
            }
        }
        for (int x = 0; x < 4; x++) currentComposition[3][x] = false;
    }

    setCoords();
}
