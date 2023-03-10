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

#define GLM_FORCE_RADIANS

float speed = 0; //Prędkość kątowa obrotu obiektu

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <cstdio>
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key,
    int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_A) printf("A \n");
        if (key == GLFW_KEY_D) printf("D \n");
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

        speed = 0; //Jeżeli puszczono klawisz ustaw prędkość obrotu na zero
    }
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
    initShaders();
    //************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
    glClearColor(0, 0, 0, 1);//Ustaw czarny kolor czyszczenia ekranu
    glEnable(GL_DEPTH_TEST); //Włącz test głębokości pikseli
    glfwSetKeyCallback(window, key_callback); //Zarejestruj procedurę obsługi klawiatury
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    freeShaders();
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************
}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window, float angle) {
	//************Tutaj umieszczaj kod rysujący obraz******************l
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    spLambert->use();

    glm::mat4 M = glm::mat4(1.0f);
    glm::mat4 M1;
    glm::mat4 M2;

    M1 = glm::rotate(M, angle, glm::vec3(1.0f, 0.0f, 0.0f));
    M2 = glm::rotate(M, -angle, glm::vec3(1.0f, 0.0f, 0.0f));

    M1 = glm::translate(M1, glm::vec3(1.0f, 0.0f, 0.0f));
    M2 = glm::translate(M2, glm::vec3(-1.0f, 0.0f, 0.0f));

    glm::mat4 V = glm::lookAt(
        glm::vec3(0.0f, 0.0f, -5.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f);

    //glUniform4f(spConstant->u("color"), 1, 0, 0, 1);
    glUniform4f(spLambert->u("color"), 0, 1, 0, 1);
    glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P));
    glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V));
    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M1));
    Models::torus.drawSolid();

    glUniform4f(spLambert->u("color"), 1, 0, 0, 1);
    glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P));
    glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V));
    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M2));
    Models::torus.drawSolid();

    glfwSwapBuffers(window);
}

int main(void)
{
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno
    
    glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące
    float angle = 0;
    glfwSetTime(0);
	//Główna pętla
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
        angle += speed * glfwGetTime();
        
		drawScene(window, angle); //Wykonaj procedurę rysującą
        glfwSetTime(0);
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
