#pragma once

#include "model.h"


namespace Models {

    using namespace std;
    using namespace glm;

    class Temple : public Model {

    public:
        Temple();
        Temple(float R, float r, float mainDivs, float tubeDivs);
        virtual ~Temple();
        virtual void drawSolid(bool smooth = true);

    private:

        std::vector<float> internalVertices;
        std::vector<unsigned int> internalFaceNormals;
        std::vector<float> internalVertexNormals;

        void buildTemple(float R, float r, float mainDivs, float tubeDivs);

    };

    extern Temple temple;
}
