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

    private:
        Model stairs;
        Model bunny;

        void drawStairs(ShaderProgram* sp, GLuint texture);
        void drawBunny(ShaderProgram* sp, GLuint texture);
    };

    extern Temple temple;
}
