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
        Model("./model/temple_one_mesh_2.obj"),
        stairs("./model/schody.obj"),
        bunny("./model/bunny2.obj")
    {
    }

    Temple::~Temple()
    {
    }
    void Temple::drawTextured(ShaderProgram * sp, GLuint texture)
    {
        //M = glm::mat4(1.0f);
        Model::drawTextured(sp, texture);
        stairs.M = M;
        stairs.V = V;
        stairs.P = P;

        //M = glm::rotate(M, angle, glm::vec3(0.0f, 1.0f, 0.0f));


        drawStairs(sp, texture);
        drawBunny(sp, texture);
    }
    void Temple::drawStairs(ShaderProgram * sp, GLuint texture)
    {
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
        bunny.drawTextured(sp, texture);
    }
}