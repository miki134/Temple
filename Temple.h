#pragma once

#include "model.h"
#include "shaderprogram.h"

namespace Models {

    class Temple {

    public:
        Temple();
        Temple(float R, float r, float mainDivs, float tubeDivs);
        virtual ~Temple();
        virtual void drawSolid(ShaderProgram* sp, GLuint texture);
        virtual void drawTextured(ShaderProgram* sp, GLuint texture);
        virtual void testDraw(ShaderProgram* sp, GLuint texture);

    private:

        unsigned int meshesNumber;

        std::vector<std::vector<glm::vec4>> internalVertices;
        std::vector<std::vector<glm::vec4>> internalNormals;
        std::vector<std::vector<glm::vec2>> internalTexCoords;

        std::vector<glm::vec4> tempinternalVertices;
        std::vector<glm::vec4> tempinternalNormals;
        std::vector<glm::vec2> tempinternalTexCoords;
    };

    extern Temple temple;
}
