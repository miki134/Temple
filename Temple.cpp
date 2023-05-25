#include "Temple.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

namespace Models {

    Temple temple;

    Temple::Temple() 
        :
        Model("./model/temple_final2.obj"),
        stairs("./model/schody.obj"),
        bunny("./model/bunny2.obj"),
        templeFloor("./model/podloga_2.obj"),
        floor("./model/floor_final2.obj", 10.f)
    {
    }

    Temple::~Temple()
    {
    }
    void Temple::drawTextured(ShaderProgram * sp, GLuint texture)
    {
        Model::drawTextured(sp, texture);

        drawStairs(sp, texture);
        drawBunny(sp, texture);
        drawFloor(sp, texture);
        drawTempleFloor(sp, texture);
    }
    void Temple::drawTempleFloor(ShaderProgram * sp, GLuint texture)
    {
        templeFloor.M = M;
        templeFloor.V = V;
        templeFloor.P = P;
        templeFloor.drawTextured(sp, clayTexture);
    }
    void Temple::drawFloor(ShaderProgram * sp, GLuint texture)
    {
        floor.M = M;
        floor.V = V;
        floor.P = P;

        floor.M = glm::translate(floor.M, glm::vec3(0.f, 0.01f, 0.0f));
        floor.drawTextured(sp, grassTexture);
    }
    void Temple::drawStairs(ShaderProgram * sp, GLuint texture)
    {
        stairs.M = M;
        stairs.V = V;
        stairs.P = P;
        stairs.drawTextured(sp, texture);
    }
    void Temple::drawBunny(ShaderProgram * sp, GLuint texture)
    {
        bunny.M = M;
        bunny.V = V;
        bunny.P = P;
        bunny.angle = angle;

        bunny.M = glm::translate(bunny.M, glm::vec3(5.0f, -0.1f, -3.0f));
        bunny.M = glm::rotate(bunny.M, angle, glm::vec3(0.0f, 2.0f, 0.0f));
        bunny.M = glm::scale(bunny.M, glm::vec3(2.0f, 2.0f, 2.0f));
        //M = glm::rotate(M, angle, glm::vec3(0.0f, 1.0f, 0.0f));
        bunny.drawTextured(sp, bunnyTexture);
    }
}