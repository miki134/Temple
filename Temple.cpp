#include "Temple.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>
#include <assimp/scene.h>

#include <vector>

namespace Models {

    Temple temple;

    Temple::Temple()
    {
        std::string filename = "./model/temple6.obj";

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            fprintf(stderr, "Nie mo¿na wczytaæ pliku OBJ.\n");
            exit(EXIT_FAILURE);
        }

        meshesNumber = scene->mNumMeshes;
        
        for (unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[i];

            std::vector<glm::vec4> vertices;
            std::vector<glm::vec4> normals;
            std::vector<glm::vec4> texCoords;

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
                    glm::vec4 texCoordVec(texCoord.x, texCoord.y, texCoord.z, 0.0f);
                    texCoords.push_back(texCoordVec);
                }
            }

            internalVertices.push_back(vertices);
            internalNormals.push_back(normals);
            internalTexCoords.push_back(texCoords);

            tempinternalVertices.insert(tempinternalVertices.end(), vertices.begin(), vertices.end());
            tempinternalNormals.insert(tempinternalNormals.end(), normals.begin(), normals.end());
            tempinternalTexCoords.insert(tempinternalTexCoords.end(), texCoords.begin(), texCoords.end());


            printf("Read %d vertices\n", vertices.size());
            printf("Read %d normals\n", normals.size());
            printf("Read %d texCoords\n", texCoords.size());
        }

        printf("Read %d internalVertices\n", internalVertices.size());
        printf("Read %d internalNormals\n", internalNormals.size());
        printf("Read %d internalTexCoords\n", internalTexCoords.size());
    }

    Temple::Temple(float R, float r, float mainDivs, float tubeDivs)
    {
    }

    Temple::~Temple()
    {
    }

    void Temple::drawSolid(ShaderProgram* sp, GLuint texture) {

        for (unsigned int i = 0; i < meshesNumber; i++)
        {
            std::vector<glm::vec4> vertices = internalVertices[i];
            std::vector<glm::vec4> normals = internalNormals[i];
            std::vector<glm::vec4> texCoords = internalTexCoords[i];


            glEnableVertexAttribArray(sp->a("vertex"));
            glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, vertices.data());

            glEnableVertexAttribArray(sp->a("normal"));
            glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, normals.data());

            glEnableVertexAttribArray(sp->a("texCoord"));
            glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, texCoords.data());

            glDrawArrays(GL_QUADS, 0, vertices.size());

            glDisableVertexAttribArray(sp->a("vertex"));
            glDisableVertexAttribArray(sp->a("normal"));
            glDisableVertexAttribArray(sp->a("texCoord"));
        }
    }

    void Temple::drawTextured(ShaderProgram* sp, GLuint texture)
    {
        for (unsigned int i = 0; i < meshesNumber; i++)
        {
            std::vector<glm::vec4> vertices = internalVertices[i];
            std::vector<glm::vec4> normals = internalNormals[i];
            std::vector<glm::vec4> texCoords = internalTexCoords[i];

            glEnableVertexAttribArray(sp->a("vertex"));
            glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, vertices.data());

            glEnableVertexAttribArray(sp->a("texCoord"));
            glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, texCoords.data());

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            glUniform1i(sp->u("tex"), 0);

            glDrawArrays(GL_QUADS, 0, vertices.size());

            glDisableVertexAttribArray(sp->a("vertex"));
            glDisableVertexAttribArray(sp->a("color"));
        }
    }

    void Temple::testDraw(ShaderProgram * sp, GLuint texture)
    {
        glEnableVertexAttribArray(sp->a("vertex"));
        glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, tempinternalVertices.data());

        glEnableVertexAttribArray(sp->a("normal"));
        glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, tempinternalNormals.data());

        glEnableVertexAttribArray(sp->a("texCoord"));
        glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, tempinternalTexCoords.data());

        glDrawArrays(GL_TRIANGLES, 0, tempinternalVertices.size());

        glDisableVertexAttribArray(sp->a("vertex"));
        glDisableVertexAttribArray(sp->a("normal"));
        glDisableVertexAttribArray(sp->a("texCoord"));
    }
}