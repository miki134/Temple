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

float speed = 0;
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

glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, -20.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

double lastMouseX = 0.0;
double lastMouseY = 0.0;

float sensitivity = 0.1f;

void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	/*if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_W) {
            cameraPosition += cameraSpeed * cameraFront;
            printf("W \n");
        }
        if (key == GLFW_KEY_A) {
            cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            printf("A \n");
        }
        if (key == GLFW_KEY_S) {
            cameraPosition -= cameraSpeed * cameraFront;
            printf("S \n");
        }
        if (key == GLFW_KEY_D) {
            cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
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

	}

	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_W) printf("puszczone W\n");
        if (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT) speed = 0;
        if (key == GLFW_KEY_A || key == GLFW_KEY_D) turn = 0;
		speed = 0;
	}*/



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

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	initShaders();
	glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
	//glEnable(GL_DEPTH_TEST);
	glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouseCallback);
}

//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
	freeShaders();
}
float* vertices = myCubeVertices;
float* texCoords = myCubeTexCoords;
float* colors = myCubeColors;
float* normals = myCubeVertexNormals;
int vertexCount = myCubeVertexCount;

void drawScene(GLFWwindow* window, float angle, float wheelAngle) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
    /*if (cameraPitch > 89.0f)
        cameraPitch = 89.0f;
    if (cameraPitch < -89.0f)
        cameraPitch = -89.0f;*/

    // Aktualizacja wektora kierunku kamery
    glm::vec3 front;
    front.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
    front.y = sin(glm::radians(cameraPitch));
    front.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
    cameraFront = glm::normalize(front);


    glm::mat4 M = glm::mat4(1.0f);
    M = glm::rotate(M, angle, glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 V = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
    /*glm::mat4 V = glm::lookAt(
        glm::vec3(0.0f, 0.0f, -3.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));*/

    //glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f);
    //glm::mat4 P = glm::perspective(50.0f*PI / 180.0f, 1.0f, 1.0f, 50.0f);
    glm::mat4 P = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);

    spLambert->use();//Aktywacja programu cieniującego
    glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P));
    glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V));
    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M));


    //glEnableVertexAttribArray(spSimplest->a("vertex")); //Enable sending data to the attribute vertex
    //glVertexAttribPointer(spSimplest->a("vertex"), 4, GL_FLOAT, false, 0, vertices); //Specify source of the data for the attribute vertex

    //glEnableVertexAttribArray(spSimplest->a("color")); //Enable sending data to the attribute color
    //glVertexAttribPointer(spSimplest->a("color"), 4, GL_FLOAT, false, 0, colors); //Specify source of the data for the attribute color

    //glEnableVertexAttribArray(spSimplest->a("normal")); //Enable sending data to the attribute color
    //glVertexAttribPointer(spSimplest->a("normal"), 4, GL_FLOAT, false, 0, normals); //Specify source of the data for the attribute normal

    //glDrawArrays(GL_TRIANGLES, 0, vertexCount); //Draw the object

    //glDisableVertexAttribArray(spSimplest->a("vertex")); //Disable sending data to the attribute vertex
    //glDisableVertexAttribArray(spSimplest->a("color")); //Disable sending data to the attribute color
    //glDisableVertexAttribArray(spSimplest->a("normal")); //Disable sending data to the attribute normal

    Models::temple.drawSolid();

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
    float wheelAngle = 0;

	glfwSetTime(0);
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		angle += speed * glfwGetTime();
        wheelAngle += -PI / 6 * glfwGetTime();
		glfwSetTime(0);
        
        int frameBufferWidth, frameBufferHeight;
        glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
        aspectRatio = static_cast<float>(frameBufferWidth) / frameBufferHeight;

        drawScene(window, angle, wheelAngle);

		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
