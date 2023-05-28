#pragma once

#include "model.h"
#include "shaderprogram.h"

namespace Models {

    class Temple : public Model {

    public:
        Temple();
        virtual ~Temple();

        virtual void drawTextured(ShaderProgram* sp, GLuint texture);
        GLuint bunnyTexture;
        GLuint clayTexture;
        GLuint grassTexture;

    private:
        Model stairs;
        Model bunny;
        Model templeFloor;
        Model floor;

        void drawTempleFloor(ShaderProgram* sp, GLuint texture);
        void drawFloor(ShaderProgram* sp, GLuint texture);
        void drawStairs(ShaderProgram* sp, GLuint texture);
        void drawBunny(ShaderProgram* sp, GLuint texture);
    };

    extern Temple temple;
}
