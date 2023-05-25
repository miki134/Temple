/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#ifndef MODEL_H
#define MODEL_H


#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "constants.h"
#include "shaderprogram.h"

namespace Models {

	class Model {
		public:
            Model();
            Model(std::string filename);
            virtual ~Model() = default;

			int vertexCount;
			float *vertices;
			float *normals;
			float *vertexNormals;
			float *texCoords;
			float *colors;

            unsigned int meshesNumber;
            std::vector<std::vector<glm::vec4>> internalVertices;
            std::vector<std::vector<glm::vec4>> internalNormals;
            std::vector<std::vector<glm::vec2>> internalTexCoords;

            std::vector<glm::vec4> oneMeshInternalVertices;
            std::vector<glm::vec4> oneMeshInternalNormals;
            std::vector<glm::vec2> oneMeshInternalTexCoords;

            virtual void drawSolid(bool smooth = false) {};
			virtual void drawWire(bool smooth=false);

            virtual void drawSolid(ShaderProgram* sp, GLuint texture);
            virtual void drawTextured(ShaderProgram* sp, GLuint texture);
            virtual void drawAllInOneMesh(ShaderProgram* sp, GLuint texture);

            glm::mat4 M;
            glm::mat4 V;
            glm::mat4 P;

            float angle;

    protected:
            virtual void initOBJ(std::string filename);
	};
}

#endif
