#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "Draw.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>
#include <assimp/scene.h>
float speed = 0;
float turn = 0;

float cameraX = 10;
float cameraY = 10;
float cameraZ = 10;

void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_A) {
            turn = PI / 6;
            printf("A \n");
        }
        if (key == GLFW_KEY_D) {
            turn = -PI / 6;
            printf("D \n");
        }
		if (key == GLFW_KEY_LEFT) {
			speed -= PI;
			printf("LEFT \n");
		}
		if (key == GLFW_KEY_RIGHT) {
			speed += PI;
			printf("RIGHT \n");
		}
		if (key == GLFW_KEY_W && (mods & GLFW_MOD_ALT) != 0)
			printf("ALT+W\n");

        if (key == GLFW_KEY_Z) {
            cameraX+=10;
            printf("Z \n");
        }

        if (key == GLFW_KEY_X) {
            cameraY+=10;
            printf("X \n");
        }

        if (key == GLFW_KEY_C) {
            cameraZ+=10;
            printf("C \n");
        }

        if (key == GLFW_KEY_V) {
            cameraX -= 10;
            printf("V \n");
        }

        if (key == GLFW_KEY_B) {
            cameraY -= 10;
            printf("B \n");
        }

        if (key == GLFW_KEY_N) {
            cameraZ -= 10;
            printf("N \n");
        }
	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_W) printf("puszczone W\n");
        if (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT) speed = 0;
        if (key == GLFW_KEY_A || key == GLFW_KEY_D) turn = 0;
		speed = 0;
	}
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	initShaders();
	glClearColor(0, 0, 0, 1);

	//glEnable(GL_DEPTH_TEST);
	glfwSetKeyCallback(window, key_callback);
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
	freeShaders();
}

std::vector<glm::vec4> vertices;
std::vector<glm::vec4> normals;
std::vector<glm::vec4> texCoords;

//void LoadModel(const std::string& filePath)
//{
//    Assimp::Importer importer;
//    const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);
//
//    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
//    {
//        // Obsłuż błąd wczytywania pliku .obj
//        return;
//    }
//
//    aiMesh* mesh = scene->mMeshes[0];
//
//    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
//    {
//        aiVector3D pos = mesh->mVertices[i];
//        glm::vec4 vertex(pos.x, pos.y, pos.z, 1.0f);
//        vertices.push_back(vertex);
//
//        if (mesh->HasNormals())
//        {
//            aiVector3D normal = mesh->mNormals[i];
//            glm::vec4 normalVec(normal.x, normal.y, normal.z, 0.0f);
//            normals.push_back(normalVec);
//        }
//
//        if (mesh->HasTextureCoords(0))
//        {
//            aiVector3D texCoord = mesh->mTextureCoords[0][i];
//            glm::vec4 texCoordVec(texCoord.x, texCoord.y, texCoord.z, 0.0f);
//            texCoords.push_back(texCoordVec);
//        }
//    }
//}

Assimp::Importer importer;
const aiScene* scene;// = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

void LoadModel()
{

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        // Obsłuż błąd wczytywania pliku .obj
        return;
    }

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

        // Renderowanie meshu
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

void drawScene(GLFWwindow* window, float angle, float wheelAngle) {

    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 M = glm::mat4(1.0f);
    M = glm::rotate(M, angle, glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 V = glm::lookAt(
        glm::vec3(0.0f, 0.0f, -20.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 P = glm::perspective(
        glm::radians(50.0f), 1.0f, 1.0f, 50.0f);

    spConstant->use();//Aktywacja programu cieniującego
    glUniformMatrix4fv(spConstant->u("P"), 1, false, glm::value_ptr(P));
    glUniformMatrix4fv(spConstant->u("V"), 1, false, glm::value_ptr(V));
    glUniformMatrix4fv(spConstant->u("M"), 1, false, glm::value_ptr(M));
    LoadModel();

    glfwSwapBuffers(window);


    /*glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, vertices.data());
    glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, normals.data());
    glVertexAttribPointer(2, 4, GL_FLOAT, false, 0, texCoords.data());

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);*/
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f); //Wyliczenie macierzy rzutowania
    //glm::mat4 V = glm::lookAt(glm::vec3(0.0f, -60.0f, 10.0f), glm::vec3(0.0f, -10.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Wyliczenie macierzy 
    ////spLambert->use();
    //
    //glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P)); //Załadowanie macierzy rzutowania do programu cieniującego
    //glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V)); //Załadowanie macierzy widoku do programu cieniującego

    //// Utwórz bufor wierzchołków
    //GLuint vertexBuffer;
    //glGenBuffers(1, &vertexBuffer);
    //glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    //glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    //// Utwórz bufor indeksów
    //GLuint indexBuffer;
    //glGenBuffers(1, &indexBuffer);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    //// Utwórz bufor normalnych (jeśli istnieją)
    //GLuint normalBuffer;
    //if (!normals.empty()) {
    //    glGenBuffers(1, &normalBuffer);
    //    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    //    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), &normals[0], GL_STATIC_DRAW);
    //}

    //// Skonfiguruj atrybuty wierzchołków
    //GLuint positionAttrib = glGetAttribLocation(spLambert->shaderProgram, "position");
    //glEnableVertexAttribArray(positionAttrib);
    //glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    //glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //// Skonfiguruj normalne (jeśli istnieją)
    //GLuint normalAttrib = glGetAttribLocation(spLambert->shaderProgram, "normal");
    //if (!normals.empty()) {
    //    glEnableVertexAttribArray(normalAttrib);
    //    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    //    glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //}

    //// Ustaw aktywny program shaderów
    ////glUseProgram(spLambert->shaderProgram);
    //spLambert->use();

    //// Narysuj model
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    //// Wyłącz atrybuty wierzchołków
    //glDisableVertexAttribArray(positionAttrib);
    //if (!normals.empty()) {
    //    glDisableVertexAttribArray(normalAttrib);
    //}

    //Models::torus.drawSolid();
    //Models::temple.drawSolid();

    //glfwSwapBuffers(window);
}

int main(void)
{
    
    scene = importer.ReadFile("./model/kostka2.obj", aiProcess_Triangulate | aiProcess_FlipUVs);

    //LoadModel("./model/kostka2.obj");

    /*aiMesh *mesh = scene->mMeshes[0];

    numVerts = mesh->mNumFaces * 3;

    vertexArray = new float[mesh->mNumFaces * 3 * 3];
    normalArray = new float[mesh->mNumFaces * 3 * 3];
    uvArray = new float[mesh->mNumFaces * 3 * 2];

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace& face = mesh->mFaces[i];

        for (int j = 0; j < 3; j++)
        {
            aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[j]];
            memcpy(uvArray, &uv, sizeof(float) * 2);
            uvArray += 2;

            aiVector3D normal = mesh->mNormals[face.mIndices[j]];
            memcpy(normalArray, &normal, sizeof(float) * 3);
            normalArray += 3;

            aiVector3D pos = mesh->mVertices[face.mIndices[j]];
            memcpy(vertexArray, &pos, sizeof(float) * 3);
            vertexArray += 3;
        }
    }

    uvArray -= mesh->mNumFaces * 3 * 2;
    normalArray -= mesh->mNumFaces * 3 * 3;
    vertexArray -= mesh->mNumFaces * 3 * 3;
*/

	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);

	if (!window)
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window);


	float angle = 0;
    float wheelAngle = 0;

	glfwSetTime(0);
	//Główna pętla
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		angle += speed * glfwGetTime();
        wheelAngle += -PI / 6 * glfwGetTime();
		glfwSetTime(0);
        //Draw::carWithTurningWeels(window, angle, turn, wheelAngle);
        drawScene(window, angle, wheelAngle);

		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
