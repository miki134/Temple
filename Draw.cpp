#include "Draw.h"

#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Draw::rotatingTwoToruses(float angle)
{
	glm::mat4 V = glm::lookAt(
		glm::vec3(0.0f, 0.0f, -5.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f);

	glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V));

	glm::mat4 M = glm::mat4(1.0f);
	glm::mat4 M1;
	glm::mat4 M2;

	M1 = glm::translate(M, glm::vec3(1.0f, 0.0f, 0.0f));
	M2 = glm::translate(M, glm::vec3(-1.0f, 0.0f, 0.0f));

	M1 = glm::rotate(M1, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	M2 = glm::rotate(M2, -angle, glm::vec3(0.0f, 1.0f, 0.0f));

	//glUniform4f(spConstant->u("color"), 1, 0, 0, 1);
	glUniform4f(spLambert->u("color"), 0, 1, 0, 1);
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M1));
	Models::torus.drawSolid();

	glUniform4f(spLambert->u("color"), 1, 0, 0, 1);
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M2));
	Models::torus.drawSolid();
}

void Draw::rotatingSolarSystem(float angle)
{
	glm::mat4 V = glm::lookAt(
		glm::vec3(0.0f, 0.0f, -5.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f);

	glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V));

	glm::mat4 M = glm::mat4(1.0f);
	glm::mat4 Msun = M;
	glm::mat4 Mplanet = M;
	glm::mat4 Moon = M;
	glm::mat4 Mplanet2 = M;

	Msun = glm::translate(Msun, glm::vec3(0.0f, 0.0f, 0.0f));
	Msun = glm::rotate(Msun, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	//Msun = glm::scale(Msun, glm::vec3(0.7f, 0.7f, 0.7f));

	glUniform4f(spLambert->u("color"), 1, 1, 0, 1);
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Msun));
    static Models::Sphere sun(0.5, 36, 36);
    sun.drawSolid();
    //Models::sphere.drawSolid();

	Mplanet = glm::rotate(Mplanet, -angle, glm::vec3(0.0f, 1.0f, 0.0f));
	Mplanet = glm::translate(Mplanet, glm::vec3(1.5f, 0.0f, 0.0f));
	//Mplanet = glm::scale(Mplanet, glm::vec3(0.3f, 0.3f, 0.3f));

	glUniform4f(spLambert->u("color"), 0, 1, 0, 1);
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mplanet));
	//Models::sphere.drawSolid();
    static Models::Sphere planet1(0.2, 36, 36);
    planet1.drawSolid();

    Moon = glm::rotate(Mplanet, angle, glm::vec3(0.0f, -1.0f, 0.0f));
    Moon = glm::translate(Moon, glm::vec3(0.5f, 0.0f, 0.0f));
	//M3 = glm::scale(M3, glm::vec3(0.5f, 0.5f, 0.5f));

	glUniform4f(spLambert->u("color"), 1, 1, 1, 1);
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Moon));
	//Models::sphere.drawSolid();
    static Models::Sphere moon1(0.1, 36, 36);
    moon1.drawSolid();

    Mplanet2 = glm::rotate(Mplanet2, -angle, glm::vec3(1.0f, 0.0f, 1.0f));
    Mplanet2 = glm::translate(Mplanet2, glm::vec3(0.0f, 1.5f, 0.0f));
    //Mplanet2 = glm::rotate(Mplanet2, angle, glm::vec3(0.0f, 1.0f, 0.0f));
    //Mplanet = glm::scale(Mplanet, glm::vec3(0.3f, 0.3f, 0.3f));

    glUniform4f(spLambert->u("color"), 0, 0, 1, 1);
    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mplanet2));
    //Models::sphere.drawSolid();
    static Models::Sphere planet2(0.2, 36, 36);
    planet2.drawSolid();

}

void Draw::rotatingTwoTorusesWithSquares(float angle)
{
    glm::mat4 V = glm::lookAt(
        glm::vec3(0.0f, 0.0f, -5.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f);

    glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P));
    glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V));

    glm::mat4 M = glm::mat4(1.0f);
    glm::mat4 M1 = M;
    glm::mat4 M2 = M;

    M1 = glm::translate(M, glm::vec3(1.0f, 0.0f, 0.0f));
    M2 = glm::translate(M, glm::vec3(-1.0f, 0.0f, 0.0f));
    
    for (int i = 0; i < 12; i++)
    {
        glm::mat4 Mx = M1;
        //Mx = glm::translate(Mx, glm::vec3(1.0f, 0.0f, 0.0f));
        Mx = glm::rotate(Mx, (i+1)*(PI/6)+angle, glm::vec3(0.0f, 0.0f, 1.0f));
        Mx = glm::translate(Mx, glm::vec3(1.0f, 0.0f, 0.0f));
        
        Mx = glm::rotate(Mx, angle, glm::vec3(1.0f, 1.0f, 1.0f));
        
        Mx = glm::scale(Mx, glm::vec3(0.1f, 0.1f, 0.1f));

        glUniform4f(spLambert->u("color"), 0, 1, 0, 1);
        glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mx));
        Models::cube.drawSolid();
    }

    for (int i = 0; i < 12; i++)
    {
        glm::mat4 Mx = M2;

        //Mx = glm::translate(Mx, glm::vec3(-1.0f, 0.0f, 0.0f));
        Mx = glm::rotate(Mx, (i + 1)*(PI / 6) + angle + PI/12, glm::vec3(0.0f, 0.0f, -1.0f));
        Mx = glm::translate(Mx, glm::vec3(1.0f, 0.0f, 0.0f));
        
        Mx = glm::rotate(Mx, angle, glm::vec3(1.0f, 1.0f, 1.0f));

        Mx = glm::scale(Mx, glm::vec3(0.1f, 0.1f, 0.1f));
        //Mx = glm::rotate(Mx, /*i*(PI/6)**/angle, glm::vec3(0.0f, 0.0f, 0.0f));
        glUniform4f(spLambert->u("color"), 1, 0, 0, 1);
        glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mx));
        Models::cube.drawSolid();
    }

    //glUniform4f(spConstant->u("color"), 1, 0, 0, 1);
    glUniform4f(spLambert->u("color"), 0, 1, 0, 1);
    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M1));
    Models::torus.drawSolid();

    glUniform4f(spLambert->u("color"), 1, 0, 0, 1);
    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M2));
    Models::torus.drawSolid();
}

void Draw::rotatingTwoTorusesWithSquaresScaled(float angle)
{

    glm::mat4 V = glm::lookAt(
        glm::vec3(0.0f, 0.0f, -5.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f);

    glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P));
    glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V));

    glm::mat4 M = glm::mat4(1.0f);
    glm::mat4 M1 = M;
    glm::mat4 M2 = M;

    //M1 = glm::translate(M, glm::vec3(1.0f, 0.0f, 0.0f));
    //M2 = glm::translate(M, glm::vec3(-1.0f, 0.0f, 0.0f));
    //M2 = glm::scale(M, glm::vec3(-1.0f, 0.0f, 0.0f));
    M2 = glm::scale(M, glm::vec3(0.5f, 0.5f, 0.5f));

    for (int i = 0; i < 12; i++)
    {
        glm::mat4 Mx = M1;
        //Mx = glm::translate(Mx, glm::vec3(1.0f, 0.0f, 0.0f));
        Mx = glm::rotate(Mx, (i + 1)*(PI / 6) + angle, glm::vec3(0.0f, 0.0f, 1.0f));
        Mx = glm::translate(Mx, glm::vec3(1.0f, 0.0f, 0.0f));

        Mx = glm::rotate(Mx, angle, glm::vec3(1.0f, 1.0f, 1.0f));

        Mx = glm::scale(Mx, glm::vec3(0.1f, 0.1f, 0.1f));

        glUniform4f(spLambert->u("color"), 0, 1, 0, 1);
        glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mx));
        Models::cube.drawSolid();
    }

    for (int i = 0; i < 12; i++)
    {
        glm::mat4 Mx = M2;

        //Mx = glm::translate(Mx, glm::vec3(-1.0f, 0.0f, 0.0f));
        Mx = glm::rotate(Mx, (i + 1)*(PI / 6) + angle + PI / 12, glm::vec3(0.0f, 0.0f, -1.0f));
        Mx = glm::translate(Mx, glm::vec3(1.0f, 0.0f, 0.0f));

        Mx = glm::rotate(Mx, angle, glm::vec3(1.0f, 1.0f, 1.0f));

        Mx = glm::scale(Mx, glm::vec3(0.1f, 0.1f, 0.1f));
        //Mx = glm::rotate(Mx, /*i*(PI/6)**/angle, glm::vec3(0.0f, 0.0f, 0.0f));
        glUniform4f(spLambert->u("color"), 1, 0, 0, 1);
        glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mx));
        Models::cube.drawSolid();
    }

    //glUniform4f(spConstant->u("color"), 1, 0, 0, 1);
    glUniform4f(spLambert->u("color"), 0, 1, 0, 1);
    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M1));
    Models::torus.drawSolid();

    glUniform4f(spLambert->u("color"), 1, 0, 0, 1);
    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M2));
    Models::torus.drawSolid();
}

void Draw::rotatingSixToruses(float angle)
{
    glm::mat4 V = glm::lookAt(
        glm::vec3(0.0f, 0.0f, -10.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f);

    glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P));
    glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V));

    glm::mat4 M = glm::mat4(1.0f);
    glm::mat4 M1 = M;

    std::vector<glm::vec3> tab = {
        glm::vec3(2.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 2.0f, 0.0f),
        glm::vec3(-1.0f, 2.0f, 0.0f),
        glm::vec3(-2.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, -2.0f, 0.0f),
        glm::vec3(-1.0f, -2.0f, 0.0f), };

    for (int y = 0; y < 6; y++)
    {
        M1 = glm::translate(M, tab[y]);

        for (int i = 0; i < 12; i++)
        {
            glm::mat4 Mx = M1;

            Mx = glm::rotate(Mx, (i + 1)*(PI / 6) + angle +  (y%2==0 ? PI / 12 : 0), glm::vec3(0.0f, 0.0f, y%2==0 ? -1.0f : 1.0f));
            Mx = glm::translate(Mx, glm::vec3(1.0f, 0.0f, 0.0f));

            Mx = glm::rotate(Mx, angle, glm::vec3(1.0f, 1.0f, 1.0f));

            Mx = glm::scale(Mx, glm::vec3(0.1f, 0.1f, 0.1f));

            glUniform4f(spLambert->u("color"), 1, 0, 0, 1);
            glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mx));
            Models::cube.drawSolid();
        }

        glUniform4f(spLambert->u("color"), 0, 1, 0, 1);
        glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M1));
        Models::torus.drawSolid();
    }
}

void Draw::rotatingSixTorusesVertical(float angle)
{
    auto drawCog = [](glm::mat4 Mt, float angleDelta) {
        //Za³aduj macierz modelu i narysuj torus
        glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mt));
        glUniform4f(spLambert->u("color"), 0, 1, 0, 1);
        Models::torus.drawSolid();

        //W pêtli narysuj 12 kostek.
        for (int k = 0; k < 12; k++) {
            //Macierz kostki to obrót, ¿eby wybraæ kierunek wokó³ torusa...
            glm::mat4 Mk = glm::rotate(Mt, glm::radians(k * 30.0f + angleDelta), glm::vec3(0.0f, 0.0f, 1.0f));
            //...przesuniêcie ¿eby dotrzeæ na obrze¿e torusa...
            Mk = glm::translate(Mk, glm::vec3(1.0f, 0.0f, 0.0f));
            //...i skalowanie ¿eby pomniejszyæ kostkê do porz¹danych rozmiarów
            Mk = glm::scale(Mk, glm::vec3(0.1f, 0.1f, 0.1f));
            glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mk));
            glUniform4f(spLambert->u("color"), 0, 1, 0, 1);
            Models::cube.drawSolid();
        }
    };

    glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f); //Wyliczenie macierzy rzutowania
    glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 2.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Wyliczenie macierzy widoku

    spLambert->use();//Aktywacja programu cieniuj¹cego
    glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P)); //Za³adowanie macierzy rzutowania do programu cieniuj¹cego
    glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V)); //Za³adowanie macierzy widoku do programu cieniuj¹cego



    for (int k = 0; k < 6; k++) {
        glm::mat4 Mt1 = glm::mat4(1.0f);
        Mt1 = glm::rotate(Mt1, glm::radians(k * 60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        Mt1 = glm::translate(Mt1, glm::vec3(0.0f, 0.0f, 1.8f));
        Mt1 = glm::rotate(Mt1, ((k % 2 == 0) ? 1 : -1) * angle, glm::vec3(0.0f, 0.0f, 1.0f));
        drawCog(Mt1, (k % 2) * 11);
    }

}

void Draw::car(float angle)
{
    Models::Torus carWheel(0.3, 0.1, 12, 12);

    glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f); //Wyliczenie macierzy rzutowania
    glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 2.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Wyliczenie macierzy widoku

    spLambert->use();//Aktywacja programu cieniuj¹cego
    glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P)); //Za³adowanie macierzy rzutowania do programu cieniuj¹cego
    glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V)); //Za³adowanie macierzy widoku do programu cieniuj¹cego



    glm::mat4 Ms = glm::mat4(1.0f);
    Ms = glm::rotate(Ms, angle, glm::vec3(0.0f, 1.0f, 0.0f));

    //Podwozie
    glm::mat4 Mp = glm::scale(Ms, glm::vec3(1.5f, 0.125f, 1.0f));
    glUniform4f(spLambert->u("color"), 1, 1, 1, 1);
    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mp));  //Za³adowanie macierzy modelu do programu cieniuj¹cego
    Models::cube.drawSolid(); //Narysowanie obiektu


    //Ko³o1
    glm::mat4 Mk1 = Ms;
    Mk1 = glm::translate(Mk1, glm::vec3(1.5f, 0.0f, 1.0f));
    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mk1));  //Za³adowanie macierzy modelu do programu cieniuj¹cego	
    carWheel.drawWire();

    //Ko³o2
    glm::mat4 Mk2 = Ms;
    Mk2 = glm::translate(Mk2, glm::vec3(1.5f, 0.0f, -1.0f));
    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mk2));  //Za³adowanie macierzy modelu do programu cieniuj¹cego
    carWheel.drawWire();

    //Ko³o3
    glm::mat4 Mk3 = Ms;
    Mk3 = glm::translate(Mk3, glm::vec3(-1.5f, 0.0f, 1.0f));
    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mk3));  //Za³adowanie macierzy modelu do programu cieniuj¹cego
    carWheel.drawWire();

    //Ko³o4
    glm::mat4 Mk4 = Ms;
    Mk4 = glm::translate(Mk4, glm::vec3(-1.5f, 0.0f, -1.0f));
    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mk4));  //Za³adowanie macierzy modelu do programu cieniuj¹cego
    carWheel.drawWire();

}

void Draw::carWithTurningWeels(GLFWwindow* window, float angle, float turn, float wheelAngle)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    spLambert->use();

    Models::Torus carWheel(0.3, 0.1, 12, 12);

    glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f); //Wyliczenie macierzy rzutowania
    glm::mat4 V = glm::lookAt(glm::vec3(0.0f, -12.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Wyliczenie macierzy widoku

    spLambert->use();//Aktywacja programu cieniuj¹cego
    glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P)); //Za³adowanie macierzy rzutowania do programu cieniuj¹cego
    glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V)); //Za³adowanie macierzy widoku do programu cieniuj¹cego



    glm::mat4 Ms = glm::mat4(1.0f);
    Ms = glm::rotate(Ms, angle, glm::vec3(0.0f, 1.0f, 0.0f));

    //Podwozie
    glm::mat4 Mp = glm::scale(Ms, glm::vec3(1.5f, 0.125f, 1.0f));
    glUniform4f(spLambert->u("color"), 1, 1, 1, 1);
    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mp));  //Za³adowanie macierzy modelu do programu cieniuj¹cego
    Models::cube.drawSolid(); //Narysowanie obiektu


    //Ko³o1
    glm::mat4 Mk1 = Ms;
    Mk1 = glm::translate(Mk1, glm::vec3(1.5f, 0.0f, 1.0f));
    Mk1 = glm::rotate(Mk1, turn, glm::vec3(0.0f, 1.0f, 0.0f));
    Mk1 = glm::rotate(Mk1, wheelAngle, glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mk1));  //Za³adowanie macierzy modelu do programu cieniuj¹cego
    carWheel.drawWire();

    //Ko³o2
    glm::mat4 Mk2 = Ms;
    Mk2 = glm::translate(Mk2, glm::vec3(1.5f, 0.0f, -1.0f));
    Mk2 = glm::rotate(Mk2, turn, glm::vec3(0.0f, 1.0f, 0.0f));
    Mk2 = glm::rotate(Mk2, wheelAngle, glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mk2));  //Za³adowanie macierzy modelu do programu cieniuj¹cego
    carWheel.drawWire();

    //Ko³o3
    glm::mat4 Mk3 = Ms;
    Mk3 = glm::translate(Mk3, glm::vec3(-1.5f, 0.0f, 1.0f));
    Mk3 = glm::rotate(Mk3, wheelAngle, glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mk3));  //Za³adowanie macierzy modelu do programu cieniuj¹cego
    carWheel.drawWire();

    //Ko³o4
    glm::mat4 Mk4 = Ms;
    Mk4 = glm::translate(Mk4, glm::vec3(-1.5f, 0.0f, -1.0f));
    Mk4 = glm::rotate(Mk4, wheelAngle, glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mk4));  //Za³adowanie macierzy modelu do programu cieniuj¹cego
    carWheel.drawWire();

    glfwSwapBuffers(window);
}
