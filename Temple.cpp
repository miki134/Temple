#include "Temple.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>
#include <assimp/scene.h>

#include<vector>

namespace Models {

    Temple temple;

    Temple::Temple()
    {
        std::string filename = "./model/temple.obj";

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
        }
    }

    Temple::Temple(float R, float r, float mainDivs, float tubeDivs)
    {
    }

    Temple::~Temple()
    {
    }

    void Temple::drawSolid(bool smooth) {

        for (unsigned int i = 0; i < meshesNumber; i++)
        {
            std::vector<glm::vec4> vertices = internalVertices[i];
            std::vector<glm::vec4> normals = internalNormals[i];
            std::vector<glm::vec4> texCoords = internalTexCoords[i];

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);

            glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, vertices.data());
            glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, normals.data());
            glVertexAttribPointer(2, 4, GL_FLOAT, false, 0, texCoords.data());

            glDrawArrays(GL_TRIANGLES, 0, vertices.size());

            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(2);
        }
    }
}