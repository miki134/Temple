#include "Temple.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>
#include <assimp/scene.h>


namespace Models {

    Temple temple;

    Temple::Temple()
    {
        std::string filename = "./model/kostka2.obj";

        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(filename, aiProcessPreset_TargetRealtime_Fast);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            printf("Blad podczas wczytywania pliku\n");
        }

        aiMesh* mesh = scene->mMeshes[0];
        printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);

        // Pobierz wierzcho³ki
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            aiVector3D vertex = mesh->mVertices[i];
            internalVertices.push_back(vertex.x);
            internalVertices.push_back(vertex.y);
            internalVertices.push_back(vertex.z);
        }

        // Pobierz indeksy
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                internalFaceNormals.push_back(face.mIndices[j]);
            }
        }

        // Pobierz normalne
        if (mesh->HasNormals()) {
            for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
                aiVector3D normal = mesh->mNormals[i];
                internalVertexNormals.push_back(normal.x);
                internalVertexNormals.push_back(normal.y);
                internalVertexNormals.push_back(normal.z);
            }
        }

        printf("internalVertices size: %d\n", internalVertices.size());
        printf("internalFaceNormals size: %d\n", internalFaceNormals.size());
        printf("internalVertexNormals size: %d\n", internalVertexNormals.size());

        buildTemple(0, 0, 0, 0);
    }

    Temple::Temple(float R, float r, float mainDivs, float tubeDivs)
    {
    }

    Temple::~Temple()
    {
    }

    void Temple::drawSolid(bool smooth) {

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        //glEnableVertexAttribArray(3);


        glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, vertices);
        if (!smooth) glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, normals);
        else glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, vertexNormals);
        glVertexAttribPointer(2, 4, GL_FLOAT, false, 0, texCoords);
        //glVertexAttribPointer(3,4,GL_FLOAT,false,0,CubeInternal::colors);

        glDrawArrays(GL_TRIANGLES, 0, vertexCount);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        //glDisableVertexAttribArray(3);
    }

    void Temple::buildTemple(float R, float r, float mainDivs, float tubeDivs)
    {
        vertices = (float*)internalVertices.data();
        normals = (float*)internalFaceNormals.data();
        vertexNormals = (float*)internalVertexNormals.data();
        texCoords = vertexNormals;
        vertexCount = internalVertices.size();
    }

}