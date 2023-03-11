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
	glm::mat4 M3 = M;

	Msun = glm::translate(Msun, glm::vec3(0.0f, 0.0f, 0.0f));
	Msun = glm::rotate(Msun, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	Msun = glm::scale(Msun, glm::vec3(0.7f, 0.7f, 0.7f));

	glUniform4f(spLambert->u("color"), 1, 1, 0, 1);
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Msun));
	Models::sphere.drawSolid();

	Mplanet = glm::rotate(Mplanet, -angle, glm::vec3(0.0f, 1.0f, 0.0f));
	Mplanet = glm::translate(Mplanet, glm::vec3(-1.5f, 0.0f, 0.0f));
	Mplanet = glm::scale(Mplanet, glm::vec3(0.3f, 0.3f, 0.3f));

	glUniform4f(spLambert->u("color"), 0, 0, 1, 1);
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mplanet));
	Models::sphere.drawSolid();

	M3 = glm::rotate(Mplanet, angle, glm::vec3(0.0f, -1.0f, 0.0f));
	M3 = glm::translate(M3, glm::vec3(1.5f, 0.0f, 0.0f));
	M3 = glm::scale(M3, glm::vec3(0.5f, 0.5f, 0.5f));

	glUniform4f(spLambert->u("color"), 1, 1, 1, 1);
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M3));
	Models::sphere.drawSolid();
}
