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
