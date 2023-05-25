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

#include "model.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <glm/gtc/type_ptr.hpp>

namespace Models {
    Model::Model()
    {
    }

    Model::Model(float _textureMultiplier) :
        textureMultiplier(_textureMultiplier)
    {
    }

    Model::Model(std::string filename, float _textureMultiplier) :
        textureMultiplier(_textureMultiplier)
    {
        initOBJ(filename);
    }

    void Model::drawWire(bool smooth) {
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		drawSolid(smooth);

		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}

    void Model::drawSolid(ShaderProgram* sp, GLuint texture) {

        for (unsigned int i = 0; i < meshesNumber; i++)
        {
            std::vector<glm::vec4> vertices = internalVertices[i];
            std::vector<glm::vec4> normals = internalNormals[i];
            std::vector<glm::vec2> texCoords = internalTexCoords[i];


            glEnableVertexAttribArray(sp->a("vertex"));
            glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, vertices.data());

            glEnableVertexAttribArray(sp->a("normal"));
            glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, normals.data());

            /*glEnableVertexAttribArray(sp->a("texCoord"));
            glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, texCoords.data());*/

            glDrawArrays(GL_TRIANGLES, 0, vertices.size());

            glDisableVertexAttribArray(sp->a("vertex"));
            glDisableVertexAttribArray(sp->a("normal"));
            //glDisableVertexAttribArray(sp->a("texCoord"));
            glDisableVertexAttribArray(sp->a("color"));
        }
    }

    void Model::drawTextured(ShaderProgram* sp, GLuint texture)
    {
        for (unsigned int i = 0; i < meshesNumber; i++)
        {
            std::vector<glm::vec4> vertices = internalVertices[i];
            std::vector<glm::vec4> normals = internalNormals[i];
            std::vector<glm::vec2> texCoords = internalTexCoords[i];

            sp->use();
            glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
            glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));
            glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

            glEnableVertexAttribArray(sp->a("vertex"));
            glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, vertices.data());

            glEnableVertexAttribArray(sp->a("normal"));
            glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, normals.data());

            glEnableVertexAttribArray(sp->a("texCoord"));
            glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, texCoords.data());

            //glUniform1f(sp->a("textureScale"), 1.0);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            glUniform1i(sp->u("tex"), 0);

            glDrawArrays(GL_TRIANGLES, 0, vertices.size());

            glDisableVertexAttribArray(sp->a("vertex"));
            glDisableVertexAttribArray(sp->a("normal"));
            glDisableVertexAttribArray(sp->a("texCoord"));

            glDisableVertexAttribArray(sp->a("color"));
        }
    }

    void Model::drawAllInOneMesh(ShaderProgram * sp, GLuint texture)
    {
        glEnableVertexAttribArray(sp->a("vertex"));
        glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, oneMeshInternalVertices.data());

        glEnableVertexAttribArray(sp->a("normal"));
        glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, oneMeshInternalNormals.data());

        glEnableVertexAttribArray(sp->a("texCoord"));
        glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, oneMeshInternalTexCoords.data());

        glDrawArrays(GL_TRIANGLES, 0, oneMeshInternalVertices.size());

        glDisableVertexAttribArray(sp->a("vertex"));
        glDisableVertexAttribArray(sp->a("normal"));
        glDisableVertexAttribArray(sp->a("texCoord"));
    }

    void Model::initOBJ(std::string filename)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            fprintf(stderr, "Nie można wczytać pliku OBJ.\n");
            exit(EXIT_FAILURE);
        }

        meshesNumber = scene->mNumMeshes;

        for (unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[i];

            std::vector<glm::vec4> vertices;
            std::vector<glm::vec4> normals;
            std::vector<glm::vec2> texCoords;

            for (unsigned int j = 0; j < mesh->mNumVertices; j++)
            {
                aiVector3D pos = mesh->mVertices[j];
                glm::vec4 vertex(pos.x, pos.y, pos.z, 1.0f);
                vertices.push_back(vertex);

                if (mesh->HasNormals())
                {
                    aiVector3D normal = mesh->mNormals[j];
                    glm::vec4 normalVec(normal.x, normal.y, normal.z, 0.0f);
                    normals.push_back(normalVec);
                }

                if (mesh->HasTextureCoords(0))
                {
                    aiVector3D texCoord = mesh->mTextureCoords[0][j];
                    glm::vec2 texCoordVec(texCoord.x * textureMultiplier, texCoord.y * textureMultiplier);
                    texCoords.push_back(texCoordVec);
                }
            }

            internalVertices.push_back(vertices);
            internalNormals.push_back(normals);
            internalTexCoords.push_back(texCoords);

            oneMeshInternalVertices.insert(oneMeshInternalVertices.end(), vertices.begin(), vertices.end());
            oneMeshInternalNormals.insert(oneMeshInternalNormals.end(), normals.begin(), normals.end());
            oneMeshInternalTexCoords.insert(oneMeshInternalTexCoords.end(), texCoords.begin(), texCoords.end());
        }

        printf("Read %d internalVertices\n", internalVertices.size());
        printf("Read %d internalNormals\n", internalNormals.size());
        printf("Read %d internalTexCoords\n", internalTexCoords.size());
    }
}
