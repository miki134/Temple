#include "Temple.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>
#include <assimp/scene.h>

#include <vector>

namespace Models {

    Temple temple;

    Temple::Temple() 
        :
        Model("./model/temple_one_mesh_2.obj"),
        stairs("./model/schody.obj"),
        bunny("./model/bunny_moved.obj")
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
    }
    void Temple::drawStairs(ShaderProgram * sp, GLuint texture)
    {
        stairs.drawTextured(sp, texture);
    }
    void Temple::drawBunny(ShaderProgram * sp, GLuint texture)
    {
        bunny.drawTextured(sp, texture);
    }
}