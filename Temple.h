#pragma once

#include "model.h"


namespace Models {

    class Temple {

    public:
        Temple();
        Temple(float R, float r, float mainDivs, float tubeDivs);
        virtual ~Temple();
        virtual void drawSolid(bool smooth = true);

    private:

        unsigned int meshesNumber;

        std::vector<std::vector<glm::vec4>> internalVertices;
        std::vector<std::vector<glm::vec4>> internalNormals;
        std::vector<std::vector<glm::vec4>> internalTexCoords;
    };

    extern Temple temple;
}
