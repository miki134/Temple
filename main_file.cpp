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
#include "myTeapot.h"
#include "myCube.h"
#include <iostream>

bool freeCamera = false;

float speed = 1;
float turn = 0;

float fov = 45.0f; // Pole widzenia (FOV)
float aspectRatio = 0; // Proporcje ekranu
float nearClip = 0.1f; // Bliska płaszczyzna odcięcia
float farClip = 100.0f; // Daleka

bool moveForward = false;
bool moveBackward = false;
bool moveLeft = false;
bool moveRight = false;
bool moveUp = false;
bool moveDown = false;

bool rotateLeft = false;
bool rotateRight = false;
bool rotateUp = false;
bool rotateDown = false;

float cameraSpeed = 0.10f;
float rotateSpeed = 2.50f;

float cameraYaw = 0.0f;
float cameraPitch = 0.0f;

glm::vec3 cameraPosition = glm::vec3(0.0f, 2.0f, -20.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

double lastMouseX = 0.0;
double lastMouseY = 0.0;

float sensitivity = 0.1f;

void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (key == GLFW_KEY_W)
    {
        if (action == GLFW_PRESS)
            moveForward = true;
        else if (action == GLFW_RELEASE)
            moveForward = false;
    }
    else if (key == GLFW_KEY_S)
    {
        if (action == GLFW_PRESS)
            moveBackward = true;
        else if (action == GLFW_RELEASE)
            moveBackward = false;
    }
    else if (key == GLFW_KEY_A)
    {
        if (action == GLFW_PRESS)
            moveLeft = true;
        else if (action == GLFW_RELEASE)
            moveLeft = false;
    }
    else if (key == GLFW_KEY_D)
    {
        if (action == GLFW_PRESS)
            moveRight = true;
        else if (action == GLFW_RELEASE)
            moveRight = false;
    }
    else if (key == GLFW_KEY_SPACE)
    {
        if (action == GLFW_PRESS)
            moveUp = true;
        else if (action == GLFW_RELEASE)
            moveUp = false;
    }
    else if (key == GLFW_KEY_LEFT_SHIFT)
    {
        if (action == GLFW_PRESS)
            moveDown = true;
        else if (action == GLFW_RELEASE)
            moveDown = false;
    }
    else if (key == GLFW_KEY_LEFT)
    {
        if (action == GLFW_PRESS)
            rotateLeft = true;
        else if (action == GLFW_RELEASE)
            rotateLeft = false;
    }
    else if (key == GLFW_KEY_RIGHT)
    {
        if (action == GLFW_PRESS)
            rotateRight = true;
        else if (action == GLFW_RELEASE)
            rotateRight = false;
    }
    else if (key == GLFW_KEY_UP)
    {
        if (action == GLFW_PRESS)
            rotateUp = true;
        else if (action == GLFW_RELEASE)
            rotateUp = false;
    }
    else if (key == GLFW_KEY_DOWN)
    {
        if (action == GLFW_PRESS)
            rotateDown = true;
        else if (action == GLFW_RELEASE)
            rotateDown = false;
    }
    else if (key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }


    printf("cameraPos: %f, %f, %f\n", cameraPosition.x, cameraPosition.y, cameraPosition.z);
}

// Callback dla ruchu myszy
void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    double deltaX = xpos - lastMouseX;
    double deltaY = ypos - lastMouseY;

    cameraYaw += deltaX * sensitivity;
    cameraPitch -= deltaY * sensitivity;

    lastMouseX = xpos;
    lastMouseY = ypos;
}

GLuint tex;
GLuint tex1;
GLuint tex2;
GLuint tex3;

GLuint readTexture(const char* filename) {
    GLuint tex;
    glActiveTexture(GL_TEXTURE0);

    //Wczytanie do pamięci komputera
    std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
    unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
    //Wczytaj obrazek
    unsigned error = lodepng::decode(image, width, height, filename);

    //Import do pamięci karty graficznej
    glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
    glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
    //Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return tex;
}
std::vector<glm::vec3>objectPositions;

void initCollision()
{
    objectPositions.push_back(glm::vec3(11.0f, 2.0f, 0.0f));
    objectPositions.push_back(glm::vec3(11.0f, 2.0f, -2.0f));
    objectPositions.push_back(glm::vec3(9.0f, 2.0f, -2.0f));
    objectPositions.push_back(glm::vec3(9.0f, 2.0f, 0.0f));
    objectPositions.push_back(glm::vec3(3.0f, 2.0f, -2.0f));
    objectPositions.push_back(glm::vec3(-1.0f, 2.0f, -2.0f));
    objectPositions.push_back(glm::vec3(-5.0f, 2.0f, -2.0f));
    objectPositions.push_back(glm::vec3(-5.0f, 2.0f, -6.0f));
    objectPositions.push_back(glm::vec3(-5.0f, 2.0f, -10.0f));
    objectPositions.push_back(glm::vec3(-5.0f, 2.0f, -14.0f));
    objectPositions.push_back(glm::vec3(-5.0f, 2.0f, -17.5f));
    objectPositions.push_back(glm::vec3(-3.0f, 2.0f, -17.0f));
    objectPositions.push_back(glm::vec3(1.0f, 2.0f, -17.0f));
    objectPositions.push_back(glm::vec3(4.0f, 2.0f, -17.0f));
    objectPositions.push_back(glm::vec3(8.0f, 2.0f, -17.0f));
    objectPositions.push_back(glm::vec3(10.5f, 2.0f, -17.3f));
    objectPositions.push_back(glm::vec3(10.5f, 2.0f, -13.5f));
    objectPositions.push_back(glm::vec3(10.5f, 2.0f, -10.0f));
    objectPositions.push_back(glm::vec3(10.5f, 2.0f, -6.5f));

    std::vector < glm::vec3>temp;
    for (auto it : objectPositions)
    {
        temp.push_back(glm::vec3(std::abs(it.x - 16.0f) + 16.0f, it.y, it.z));
    }

    objectPositions.insert(objectPositions.end(), temp.begin(), temp.end());
}
//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	initShaders();
	glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
	//glEnable(GL_DEPTH_TEST);
	glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouseCallback);
    tex = readTexture("dirt.png");
    tex1 = readTexture("fur.png");
    tex2 = readTexture("clay.png");
    tex3 = readTexture("grass.png");
    initCollision();
}

//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
	freeShaders();
    glDeleteTextures(1, &tex);
    glDeleteTextures(1, &tex1);
    glDeleteTextures(1, &tex2);
    glDeleteTextures(1, &tex3);
}

void checkError()
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        // Obsłuż błąd OpenGL
        std::string errorMessage;
        switch (error) {
        case GL_INVALID_ENUM:
            errorMessage = "GL_INVALID_ENUM: Nieprawidłowa wartość enum";
            break;
        case GL_INVALID_VALUE:
            errorMessage = "GL_INVALID_VALUE: Nieprawidłowa wartość parametru";
            break;
        case GL_INVALID_OPERATION:
            errorMessage = "GL_INVALID_OPERATION: Nieprawidłowa operacja";
            break;
        case GL_OUT_OF_MEMORY:
            errorMessage = "GL_OUT_OF_MEMORY: Brak pamięci";
            break;
        default:
            errorMessage = "Nieznany błąd OpenGL";
            break;
        }
        std::cout << "Błąd OpenGL: " << errorMessage << std::endl;
    }
}



bool checkCollision(const glm::vec3& position)
{
    for (auto objectPosition : objectPositions)
    {
        float objectSize = 1.0f;

        if (position.x >= objectPosition.x - objectSize && position.x <= objectPosition.x + objectSize &&
            position.y >= objectPosition.y - objectSize && position.y <= objectPosition.y + objectSize &&
            position.z >= objectPosition.z - objectSize && position.z <= objectPosition.z + objectSize)
        {
            // Kolizja
            return true;
        }

    }
    return false;

}

void drawScene(GLFWwindow* window, float angle) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto oldcameraPosition = cameraPosition;

    if (moveForward)
        cameraPosition += cameraSpeed * cameraFront;
    if (moveBackward)
        cameraPosition -= cameraSpeed * cameraFront;
    if (moveLeft)
        cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (moveRight)
        cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (moveUp)
        cameraPosition += cameraSpeed * cameraUp;
    if (moveDown)
        cameraPosition -= cameraSpeed * cameraUp;

    
    if (rotateLeft)
        cameraYaw -= rotateSpeed;
    if (rotateRight)
        cameraYaw += rotateSpeed;
    if (rotateUp)
        cameraPitch += rotateSpeed;
    if (rotateDown)
        cameraPitch -= rotateSpeed;

    // Ograniczenie zakresu kątów
    if (cameraPitch > 89.0f)
        cameraPitch = 89.0f;
    if (cameraPitch < -89.0f)
        cameraPitch = -89.0f;

    // Aktualizacja wektora kierunku kamery
    glm::vec3 front;
    front.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
    front.y = sin(glm::radians(cameraPitch));
    front.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
    cameraFront = glm::normalize(front);

    ShaderProgram *sp = spSimplest;

    sp->use();
    Models::temple.M = glm::mat4(1.0f);
    Models::temple.M = glm::scale(Models::temple.M, glm::vec3(3.0f, 3.0f, 3.0f));


    if (!freeCamera)
    {
        if (checkCollision(cameraPosition))
            cameraPosition = oldcameraPosition;
        cameraPosition = glm::vec3(cameraPosition.x, 2.0f, cameraPosition.z);
    }

    Models::temple.V = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
    Models::temple.P = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
    Models::temple.angle = angle;
    Models::temple.bunnyTexture = tex1;
    Models::temple.clayTexture = tex2;
    Models::temple.grassTexture = tex3;
    Models::temple.drawTextured(sp, tex);

    glfwSwapBuffers(window);
}

int main(void)
{
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    int screenWidth = mode->width;
    int screenHeight = mode->height;

	//window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);
	window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL", NULL, NULL);

    glfwSetWindowMonitor(window, monitor, 0, 0, screenWidth, screenHeight, mode->refreshRate);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

	glfwSetTime(0);
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		angle += speed * glfwGetTime();
		glfwSetTime(0);
        
        int frameBufferWidth, frameBufferHeight;
        glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
        aspectRatio = static_cast<float>(frameBufferWidth) / frameBufferHeight;

        drawScene(window, angle);

		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
