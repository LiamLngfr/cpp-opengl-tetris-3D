#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "renderer.h"
#include "camera.h"
#include "navigationcontrols.h"
#include "cube.h"
#include "tetromino.h"



using namespace std;

int main()
{
    string path = "../..";
/////////////////////////Initialisation de GLFW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if(!glfwInit()){
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }


    glfwWindowHint(GLFW_SAMPLES, 4); //antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //version core

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);


/////////////////////////Ouverture de la fenêtre/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //définition de la taille de la fenêtre
    int width=600;
    int height=600;

    //On récupère les dimensions de l'écran pour créer la fenètre
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    glfwGetMonitorWorkarea(primary,nullptr,nullptr, &width, &height);

    //Enfin on crée la fenêtre
    GLFWwindow* window = glfwCreateWindow(width,height,"OpenGL_API",NULL,NULL);
    glfwSwapInterval(1);
    //On vérifie que l'initialisation a bien marché
    if (window==NULL){
        fprintf(stderr, "Erreur lors de la création de la fénêtre\n");
        glfwTerminate();
        return -1;
    }

    //Enfin on définit la fenêtre créée comme la fenêtre sur laquelle on va dessiner
    glfwMakeContextCurrent(window);



/////////////////////////Initialisation de GLEW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Initialisation de GLEW
    glewExperimental=true;
    if (glewInit() != GLEW_OK){
        fprintf(stderr, "Erreur lors de l'initialisation de GLEW\n");
        return -1;
    }

/////////////////////////On crée un Renderer/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Renderer renderer;


/////////////////////////On crée un Shader/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Shader shader(path+"/shaders/SimpleVertexShader.vertexshader", path+"/shaders/SimpleFragmentShader.fragmentshader");
    shader.Bind();

    Shader shaderCube(path + "/shaders/CubeVertexShader.vertexshader", path+"/shaders/CubeFragmentShader.fragmentshader");
    shaderCube.Bind();

/////////////////////////On crée un vertex array/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    VertexArray va;
    va.Bind();

/////////////////////////On crée la camera et les contrôles/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Camera cam(width, height);
    NavigationControls controls(window, &cam);

/////////////////////////Création des formes à afficher/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    glm::vec3 coords(0,0,0);
    glm::vec3 color(0.3,0.7,0.5);

    Cube c(coords, color);


/////////////////////////Création de la matrice MVP/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    cam.computeMatrices(width, height);
    glm::mat4 mCube = c.getModelMatrix ();
    glm::mat4 v = cam.getViewMatrix();
    glm::mat4 p = cam.getProjectionMatrix();




    //glm::mat4 mvp = p*v*mCube;
    //shaderCube.setUniformMat4f("MVP",mvp);
    //shaderCube.setUniform3fv("cubeColor", c.getColor());

/////////////////////////Création du U qui sert de frontière pour les pièces//////////////////////////////////////////////////////////////////////////
    int hauteurJeu = 13;


    std::vector<Cube*> walls;

    glm::vec3 colorWalls(0.3f, 0.3f, 0.3f);

    // Colonnes verticales
    for (int y = -1; y < hauteurJeu; y++) {
        walls.push_back(new Cube(glm::vec3(-1, y, 0), colorWalls));   // colonne gauche
        walls.push_back(new Cube(glm::vec3(9, y, 0), colorWalls));  // colonne droite

    }

    // Barre horizontale du bas
    for (int x = 0; x < 10; x++) {
        walls.push_back(new Cube(glm::vec3(x, -1, 0), colorWalls));
    }

    /////////Initialisation tetromino/////

    Tetromino movingTetro = Tetromino("I");

    /////////////Matrice de localisation des éléments//////////////
    std::vector<std::vector<bool>> gameMatrix(
        15,                  // nombre de lignes (hauteur)
        std::vector<bool>(9, false)  // chaque ligne : largeurJeu colonnes, initialisées à false
    );



    ////Liste des pièces immobiles/////////
    std::vector<Tetromino> staticTetro;

/////////////////////////Boucle de rendu/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    double lastDropTime = glfwGetTime();
    const double dropInterval = 1.0; // 1 seconde

    // Assure que l'on peut capturer les touche de clavier
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //On indique la couleur de fond
    glClearColor(0.9f, 0.9f, 0.9f, 0.0f);

    //On autorise les tests de profondeur

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    float lastTime = glfwGetTime();
    float currentTime, deltaTime;

    double lastInputTime = 0.0;
    const double inputInterval = 0.30;


/////////////////Boucle//////////////
    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)){

        double now = glfwGetTime();
        double waitingTime = now - lastDropTime;


        currentTime = glfwGetTime();
        deltaTime = currentTime-lastTime;
        lastTime = currentTime;

        controls.update(deltaTime, &shader);

        cam.computeMatrices(width, height);



        mCube = c.getModelMatrix ();
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();
        mCube = c.getModelMatrix ();

        //mvp = p*v*mCube;
        //shaderCube.setUniformMat4f("MVP", mvp);

        /////////On teste les input////////



        ////////////////On commence par vider les buffers///////////////
        renderer.Clear();



        ////////////////On affiche les objets///////////////
        renderer.Draw(va, c, shaderCube);

        //Rendu des limites
        for (auto& w : walls) {
            glm::mat4 mvpWall = p * v * w->getModelMatrix();
            shaderCube.setUniformMat4f("MVP", mvpWall);
            shaderCube.setUniform3fv("cubeColor", w->getColor());
            renderer.Draw(va, *w, shaderCube);
        }

        //Tétrominos
        auto m_tetrominos = movingTetro.m_tetrominos;
        for (auto& cube : m_tetrominos){
            glm::mat4 mvp = p * v * cube->getModelMatrix();
            shaderCube.setUniformMat4f ("MVP", mvp);
            shaderCube.setUniform3fv("cubeColor", cube->getColor());
            renderer.Draw(va, *cube, shaderCube);
        }

        for (auto& tetro : staticTetro) {
            for (auto& cube : tetro.m_tetrominos) {
                glm::mat4 mvp = p * v * cube->getModelMatrix();
                shaderCube.setUniformMat4f("MVP", mvp);
                shaderCube.setUniform3fv("cubeColor", cube->getColor());
                renderer.Draw(va, *cube, shaderCube);
            }
        }


        ////////////////Partie rafraichissement de l'image et des évènements///////////////
        //Swap buffers : frame refresh
        glfwSwapBuffers(window);
        //get the events
        glfwPollEvents();


        if (now - lastInputTime >= inputInterval) {
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                gameMatrix = movingTetro.moveDown(gameMatrix);
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                movingTetro.moveRight(gameMatrix);
            }
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                movingTetro.moveLeft(gameMatrix);
            }

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                movingTetro.rotate(gameMatrix);
            }

            if (waitingTime >= dropInterval) {
                gameMatrix = movingTetro.moveDown(gameMatrix);
                lastDropTime = now;
            }
            lastInputTime = now;
        }




        // Si la pièce ne bouge plus, on la “verrouille” et on en crée une nouvelle
        if (!movingTetro.isMoving) {

            if (movingTetro.position.y >= 13) {
                std::cout << "Game Over !\n";
                glfwSetWindowShouldClose(window, GL_TRUE); // demande à GLFW de fermer la fenêtre
                break; // quitte immédiatement la boucle principale
            }

            // Ajouter la pièce finie à la liste des statiques
            staticTetro.push_back(movingTetro);


            /////Suppression de lignes/////

            int width = gameMatrix[0].size();
            int height = gameMatrix.size();

            // On parcourt du haut (y = height-1) vers le bas (y = 0)
            for (int y = height - 1; y >= 0; --y) {
                bool fullLine = true;

                // Vérifie chaque colonne de la ligne
                for (int x = 0; x < width; ++x) {
                    if (!gameMatrix[y][x]) {
                        fullLine = false;
                        break;
                    }
                }

                if (fullLine) {
                    // Supprime la ligne de tous les Tetrominos statiques
                    for (auto& tetro : staticTetro) {
                        tetro.lineSuppressed(y);
                    }

                    // Supprime la ligne de la matrice de jeu
                    gameMatrix.erase(gameMatrix.begin() + y);
                    // Ajoute une ligne vide en haut
                    gameMatrix.push_back(std::vector<bool>(width, false));

                    // On doit re-vérifier la même ligne car tout a descendu
                    ++y;
                }
            }
            for (auto& tetro : staticTetro) {
                tetro.setCoords();
            }

            std::srand(static_cast<unsigned int>(std::time(nullptr)));

            const std::string types[7] = { "I", "O", "T", "L", "J", "S", "Z" };
            std::string lettre = types[ std::rand() % 7 ];


            // Créer une nouvelle pièce “bougeante”
            movingTetro = Tetromino(lettre);
            // (réinitialise aussi son état, sa position, etc.)
        }


    }
    glfwTerminate();




    return 0;
}


